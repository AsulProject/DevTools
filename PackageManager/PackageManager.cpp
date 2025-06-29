#include "PackageManager.h"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQueue>
#include <QTimer>

#include "asulException.h"
#include "asulSignal.h"
#include "ui_PackageManager.h"

#define i18n(x) x
#define DBG(x) ui->debugPlainText->appendPlainText(x)
#define ASULBASE "Asul/Base.cfg"
#define ASULBASEPACKAGE "asul.base.package@1.0.0"
#define DEBUGENV "DebugENV"

PackageManager::PackageManager(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::PackageManager) {
    //
    // constrcut begin
    //
    ui->setupUi(this);
    connect(ui->signalSlotTreeWidget, &QTreeWidget::itemClicked, this, &PackageManager::onSignalItemClicked);

    {
        // debug: disableAll
        QPushButton* disableAll = new QPushButton(this);
        connect(disableAll, &QPushButton::clicked, this, [=] {
            this->packageManager.setAllPackageStatus(asulPackageManager::PACKAGE_STATE::DISABLE);
        });
        disableAll->setText("[DEBUG] Disable All");
        ui->packageListVLayout->addWidget(disableAll);

        // debug: enableAll
        QPushButton* enableAll = new QPushButton(this);
        connect(enableAll, &QPushButton::clicked, this, [=] {
            this->packageManager.setAllPackageStatus(asulPackageManager::PACKAGE_STATE::ENABLE);
        });
        enableAll->setText("[DEBUG] enable All");
        ui->packageListVLayout->addWidget(enableAll);

        // debug: reloadPackage
        QPushButton* reloadPackage = new QPushButton(this);
        connect(reloadPackage, &QPushButton::clicked, this, [=] {
            int count = ui->packageListVLayout->count();
            for (int i = count - 1; i >= 0; --i) {
                QLayoutItem* item = ui->packageListVLayout->itemAt(i);
                if (QWidget* widget = item->widget()) {
                    if (qobject_cast<QPushButton*>(widget) == nullptr) {
                        // 移除布局项，删除控件
                        QLayoutItem* removedItem = ui->packageListVLayout->takeAt(i);
                        widget->deleteLater();
                        delete removedItem;
                    }
                    // 保留按钮给debug用
                }
            }
            this->packageManager.clear();
            // 重新收集包
            this->collectPackageFromDir(DEBUGENV);
        });
        reloadPackage->setText("[DEBUG] Reload package");
        ui->packageListVLayout->addWidget(reloadPackage);

        // debug: loadTreeView
        QPushButton* refreshTreeView = new QPushButton(this);
        connect(refreshTreeView, &QPushButton::clicked, this, [=] {
            this->updateSignalTreeWidget();
        });
        refreshTreeView->setText("[DEBUG] Refresh tree view");
        ui->packageListVLayout->addWidget(refreshTreeView);

        // debug: buildPackage
        QPushButton* buildPackage = new QPushButton(this);
        connect(buildPackage, &QPushButton::clicked, this, [=] {
            DBG("building packages...");
            try {
                this->packageManager.buildPackages();
                DBG("building successfully!");
            } catch (const asulException::unkownSignal& err) {
                DBG("[ERROR] " + QString(err.what()) + " " + err.getSubscription()->getSignal());
            } catch (const asulException::unkownDependency& err) {
                DBG("[ERROR] " + QString(err.what()) + " " + err.getDependency());
            } catch (const asulException::Exception& err) {
                DBG("[ERROR] " + QString(err.what()));
            }
        });
        buildPackage->setText("[DEBUG] build packages");
        ui->packageListVLayout->addWidget(buildPackage);
    }

    // collectPackage
    this->collectPackageFromDir(DEBUGENV);
}

PackageManager::~PackageManager() {
    delete ui;
}

void PackageManager::collectPackageFromJSON(const QString& path) {
    QFile metaDataFile(path);
    if (!metaDataFile.exists() || !metaDataFile.open(QIODevice::ReadOnly)) {
        DBG("Cannot Read " + metaDataFile.fileName() + ": " + metaDataFile.errorString());
        return;
    }
    QString originContent = metaDataFile.readAll();
    metaDataFile.close();

    // construct package object
    asulPackage* currentPackage = new asulPackage(&this->packageManager);

    // connect debug msg
    connect(currentPackage, &asulPackage::sendMsg, this, [=](const QString& msg) {
        DBG(msg);
    });

    // init form JSON
    try {
        currentPackage->initializeFromJSON(QJsonDocument::fromJson(originContent.toUtf8()).object());
    } catch (const asulException::Exception& err) {
        DBG("[ERROR] " + QString(err.what()));
        delete currentPackage;
        return;
    }

    // ui
    QWidget* packageArea = new QWidget(this);

    QHBoxLayout* packageLayout = new QHBoxLayout(packageArea);

    QLineEdit* packageIDLine = new QLineEdit(currentPackage->getName(), packageArea);
    packageIDLine->setReadOnly(true);

    QPushButton* packageManageBtn = new QPushButton(packageArea);

    // process status switch button
    connect(packageManageBtn, &QPushButton::clicked, currentPackage, [=]() {
        this->packageManager.togglePacakgeStatus(currentPackage->getName());
    });
    connect(&this->packageManager, &asulPackageManager::onPackageStatusChanged, currentPackage, [=](const QString& IaV, asulPackageManager::PACKAGE_STATE status) {
        if (IaV != currentPackage->getName())
            return;

        if (status == asulPackageManager::PACKAGE_STATE::ENABLE)
            packageManageBtn->setText("On");
        else
            packageManageBtn->setText("Off");
    });

    // add package to packageManager
    packageManager.addPackage(currentPackage, asulPackageManager::PACKAGE_STATE::DISABLE);

    // add to ui
    packageLayout->addWidget(packageIDLine, 9);
    packageLayout->addWidget(packageManageBtn, 1);
    ui->packageListVLayout->addWidget(packageArea);
}

void PackageManager::collectPackageFromDir(const QString& path) {
    QDir packageDir = QApplication::applicationDirPath().replace("\\", "/") + "/" + path;
    for (const auto& info : packageDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        this->collectPackageFromJSON(packageDir.path() + "/" + info.fileName() + "/data.json");
    }
}

void PackageManager::clearLayout(QLayout* layout) {
    if (!layout)
        return;

    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) { // 从布局中逐个移除控件
        if (QWidget* widget = item->widget()) {     // 如果是控件
            widget->deleteLater();                  // 安全删除控件
        }
        delete item; // 删除 QLayoutItem
    }
}

void PackageManager::onSignalItemClicked(QTreeWidgetItem* item, int column) {
    Q_UNUSED(column);
    qDebug() << "signal item clicked" << Qt::endl;

    ui->sArguLine->setText("");
    ui->sHostLine->setText("");

    const QVariant var = item->data(0, Qt::UserRole);

    if (var.metaType().id() == qMetaTypeId<asulSignal*>()) {
        asulSignal* signal = var.value<asulSignal*>();
        ui->sArguLine->setText(signal->getAliasCommand());
        ui->sHostLine->setText(signal->getHost());
    }
}

void PackageManager::updateSignalTreeWidget() {
    ui->signalSlotTreeWidget->clear();

    const auto& packages = this->packageManager.getPackageList().keys();

    for (const auto& IaV : packages) {
        // skip disabled package
        if (this->packageManager.getPackageStatus(IaV) == asulPackageManager::PACKAGE_STATE::DISABLE)
            continue;

        // create package item
        QTreeWidgetItem* pkgItem = new QTreeWidgetItem(ui->signalSlotTreeWidget);
        pkgItem->setText(0, IaV);

        // show dependencies
        QTreeWidgetItem* dependencyItem = new QTreeWidgetItem(pkgItem);
        dependencyItem->setText(0, "dependencies");

        for (const auto& dependency : this->packageManager.getPackage(IaV)->getDependencyList()) {
            QTreeWidgetItem* childItem = new QTreeWidgetItem(dependencyItem);
            childItem->setText(0, dependency);
        }

        // show signals
        QTreeWidgetItem* signalItem = new QTreeWidgetItem(pkgItem);
        signalItem->setText(0, "signals");

        for (const auto& signalManager : this->packageManager.getPackage(IaV)->getSigalManagerList()) {
            QTreeWidgetItem* signalManagerItem = new QTreeWidgetItem(signalItem);
            signalManagerItem->setText(0, signalManager->getTargetFile().fileName());

            for (const auto& signal : signalManager->getSignalList()) {
                QTreeWidgetItem* childItem = new QTreeWidgetItem(signalManagerItem);
                childItem->setText(0, signal->getID());
                childItem->setData(0, Qt::UserRole, QVariant::fromValue(signal));
            }
        }

        // show subscriptoins
        QTreeWidgetItem* subscriptionItem = new QTreeWidgetItem(pkgItem);
        subscriptionItem->setText(0, "subscriptions");

        for (const auto& subscription : this->packageManager.getPackage(IaV)->getSubcriptionList()) {
            QTreeWidgetItem* parentItem = new QTreeWidgetItem(subscriptionItem);
            parentItem->setText(0, subscription->getSignal());

            // show commands
            QTreeWidgetItem* commandItem = new QTreeWidgetItem(parentItem);
            commandItem->setText(0, "commands");

            for (const auto& command : subscription->getCommandList()) {
                QTreeWidgetItem* childItem = new QTreeWidgetItem(commandItem);
                childItem->setText(0, command);
            }

            // show args only when arglist is not empty
            const auto& args = subscription->getArgList();

            if (args.isEmpty() == false) {
                QTreeWidgetItem* argItem = new QTreeWidgetItem(parentItem);
                argItem->setText(0, "args");

                for (auto it = args.begin(); it != args.end(); it++) {
                    QTreeWidgetItem* childItem = new QTreeWidgetItem(argItem);
                    childItem->setText(0, it.key() + " : " + it.value().toString());
                }
            }
        }
    }
    // ui->signalSlotTreeWidget->expandAll();
    for (int i = 0; i < ui->signalSlotTreeWidget->topLevelItemCount(); i++)
        ui->signalSlotTreeWidget->topLevelItem(i)->setExpanded(true);
}

void PackageManager::on_DebugClearBtn_clicked() {
    ui->debugPlainText->clear();
}
