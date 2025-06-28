#include "PackageManager.h"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQueue>

#include "ui_PackageManager.h"
#define i18n(x) x
#define DBG(x) ui->debugPlainText->appendPlainText(x)
#define ASULBASE "Asul/Base.cfg"
#define ASULBASEPACKAGE "asul.base.package@1.0.0"
#define DEBUGENV "DebugENV"
PackageManager::PackageManager(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::PackageManager) {
    ui->setupUi(this);
    addBaseSignals();
    connect(ui->signalSlotTreeWidget, &QTreeWidget::itemClicked, this, &PackageManager::onSignalItemClicked);
    updateSignalTreeWidget();

    foreach (const QString& pkgId, PackageList) {
        packageEnabledMap[pkgId] = true; // 默认启用
    }
    updateSignals();

    // Debug Area
    QList<PackageManager::packageData> List = findSubsequentNodes(packageData("asul.package1@1.0.0"));
    foreach (PackageManager::packageData data, List) {
        qDebug() << data.toString();
    }
    // foreach(packageData data,list){
    //     qDebug()<<data.toString();
    // }
}

PackageManager::~PackageManager() {
    delete ui;
}

void PackageManager::registerSignal(QString sHost, QString sName, QString sArgu) {
    if (!signalList.contains(sHost)) {
        signalList.append(sHost);
    }
    if (!signalMap[sHost].contains(sName))
        signalMap[sHost].append(QStringList{sName});
    else
        DBG(sName + " Already Exist! Check MetaData !!!");
    if (!signalArgu[sName].contains(QString(sArgu)))
        signalArgu[sName].append(QString(sArgu));
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

void PackageManager::clearSignals() {
    signalList.clear();
    signalMap.clear();
    signalArgu.clear();
    PackageList.clear();
    Packages.clear();
    id_dir_map.clear();
    nodeMap.clear();
    cleanupTopology();
    addBaseSignals();
}

void PackageManager::addBaseSignals() {
    // JUST DEBUG USE, IF YOU ARE MOVE IT TO DEBUGENV: YOU CAN ANNOTATE IT !!!
    // JUST DEBUG USE, IF YOU ARE MOVE IT TO DEBUGENV: YOU CAN ANNOTATE IT !!!
    // JUST DEBUG USE, IF YOU ARE MOVE IT TO DEBUGENV: YOU CAN ANNOTATE IT !!!

    // registerSignal(ASULBASE,"Asul.Base.Signal1","alias1;alias2;");
    // registerSignal(ASULBASE,"Asul.Base.PlayerSlot.W","+forward;");
    // registerSignal(ASULBASE,"Asul.Base.PlayerSlot.D","+moveright;");
}

void PackageManager::onSignalItemClicked(QTreeWidgetItem* item, int column) {
    Q_UNUSED(column);
    if (item->childCount() == 0) { // 子节点
        QString signalName = item->data(0, Qt::UserRole).toString();
        if (signalArgu.contains(signalName)) {
            ui->sArguLine->setText("alias " + signalName + " \"" + signalArgu[signalName] + "\"");
            QMap<QString, QStringList>::const_iterator iter;
            QString signalHost = "Homeless...";
            for (iter = signalMap.constBegin(); iter != signalMap.constEnd(); ++iter) {
                if (iter.value().contains(signalName)) {
                    signalHost = iter.key();
                }
            }
            ui->sHostLine->setText(signalHost);
        }
    }
}

void PackageManager::updateSignalTreeWidget() {
    ui->signalSlotTreeWidget->clear();
    QMap<QString, QStringList>::const_iterator iter;
    for (iter = signalMap.constBegin(); iter != signalMap.constEnd(); ++iter) {
        QTreeWidgetItem* parentItem = new QTreeWidgetItem(ui->signalSlotTreeWidget);
        parentItem->setText(0, iter.key());

        foreach (const QString& signal, iter.value()) {
            QTreeWidgetItem* childItem = new QTreeWidgetItem(parentItem);
            childItem->setText(0, signal);
            childItem->setData(0, Qt::UserRole, signal);
        }
    }
    ui->signalSlotTreeWidget->expandAll();
}

void PackageManager::updateSignals(QList<packageData> WithOutPackageList) {
    // 清理之前的映射和数据
    clearSignals();
    // 清理左侧Layout
    clearLayout(ui->packageListVLayout);
    dataNode* base = new dataNode();
    base->data = packageData("asul.base.package@1.0.0");
    nodeMap.insert(packageData(ASULBASEPACKAGE), base);

    // 扫描应用目录中的包
    QDir PackageDir = QApplication::applicationDirPath().replace("\\", "/") + "/" + DEBUGENV;
    foreach (QFileInfo info, PackageDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QFile metaDataFile(PackageDir.path() + "/" + info.fileName() + "/data.json");
        if (!metaDataFile.exists() || !metaDataFile.open(QIODevice::ReadOnly)) {
            DBG("Cannot Read " + metaDataFile.fileName() + ": " + metaDataFile.errorString());
            continue;
        }

        QString originContent = metaDataFile.readAll();
        metaDataFile.close();

        QJsonObject pData = QJsonDocument::fromJson(originContent.toUtf8()).object()["packageData"].toObject();
        packageData currentPackage(pData["id"].toString(), pData["version"].toString());
        QWidget* packageArea = new QWidget(this);
        QHBoxLayout* packageLayout = new QHBoxLayout(packageArea);

        QLineEdit* packageIDLine = new QLineEdit(pData["id"].toString(), packageArea);
        packageIDLine->setReadOnly(true);
        QPushButton* packageManageBtn = new QPushButton(packageArea);

        packageManageBtn->setText(packageEnabledMap[packageData(pData["id"].toString(), pData["version"].toString())] ? "On" : "Off");
        connect(packageManageBtn, &QPushButton::clicked, [=]() {
            // 1. 切换状态
            bool isEnabled = (packageManageBtn->text() == "On");
            if (packageManageBtn->text() == "On")
                packageManageBtn->setText("Off");
            else
                packageManageBtn->setText("On");
            // 2. 记录状态到 map：用包 ID 作为 key
            packageEnabledMap[packageData(pData["id"].toString(), pData["version"].toString())] = !isEnabled; // 注意状态翻转逻辑

            // 3. 收集所有被标记为 Off 的包，作为 WithOutPackageList
            QList<packageData> withOutList;
            foreach (const packageData& id, packageEnabledMap.keys()) {
                if (!packageEnabledMap[id]) { // Off 的包需要排除
                    withOutList.append(findSubsequentNodes(id));
                    withOutList.append(id);
                }
            }
            qDebug() << "withOutList: ";
            foreach (const packageData& data, withOutList) {
                qDebug() << data.toString();
            }

            // 4. 重新加载拓扑
            updateSignals(withOutList);
        });
        packageLayout->addWidget(packageIDLine, 9);
        packageLayout->addWidget(packageManageBtn, 1);
        ui->packageListVLayout->addWidget(packageArea);

        // 检查是否需要排除此包
        if (WithOutPackageList.contains(currentPackage))
            continue;

        // 构建ID到目录的映射
        PackageList.append(currentPackage.Id);
        id_dir_map[currentPackage.Id] = info.fileName();

        // 创建或获取当前包节点
        if (!nodeMap.contains(currentPackage)) {
            dataNode* node = new dataNode();
            node->data = currentPackage;
            nodeMap.insert(currentPackage, node);
        }

        // 处理依赖关系
        foreach (QString dependencyId, pData["dependencies"].toVariant().toStringList()) {
            // 提取依赖的版本信息（如果有）
            QString version = "";
            QString depId = dependencyId;
            if (dependencyId.contains('@')) {
                QStringList parts = dependencyId.split('@');
                depId = parts[0];
                version = parts[1];
            }

            // 创建依赖包数据
            packageData dependency(depId, version);

            // 确保依赖节点存在
            if (!nodeMap.contains(dependency)) {
                dataNode* depNode = new dataNode();
                depNode->data = dependency;
                nodeMap.insert(dependency, depNode);
            }

            nodeMap.value(dependency)->childList.append(nodeMap.value(currentPackage));
        }
    }

    qDebug() << "PackageList {}:" << PackageList;

    // 收集所有有效包数据
    foreach (const QString packageId, PackageList) {
        QFile metaDataFile(PackageDir.path() + "/" + id_dir_map[packageId] + "/data.json");

        if (!metaDataFile.open(QIODevice::ReadOnly)) {
            DBG("Cannot Read " + metaDataFile.fileName() + ": " + metaDataFile.errorString());
            return;
        }

        QString originContent = metaDataFile.readAll();
        metaDataFile.close();
        QJsonObject pRoot = QJsonDocument::fromJson(originContent.toUtf8()).object();
        QJsonObject pData = pRoot["packageData"].toObject();
        Packages.append(packageData(pData["id"].toString(), pData["version"].toString()));
        packageEnabledMap[packageData(pData["id"].toString(), pData["version"].toString())] = true;

        auto provides = pRoot["provides"].toObject();
        auto subscriptions = pRoot["subscriptions"].toArray();
        auto exports = provides["exports"].toArray();
        auto _signals = provides["signals"].toArray();

        for (const auto& signalValue : _signals) {
            auto signalObj = signalValue.toObject();
            auto entriesArray = signalObj["entries"].toArray();
            QString targetFileLocation = signalObj["targetFileLocation"].toString();
            QString signalRegisterName = pData["id"].toString() + "/" + targetFileLocation;
            if (!signalList.contains(signalRegisterName))
                signalList.append(signalRegisterName);

            DBG("Registered List: " + signalRegisterName);
            for (const auto& entry : entriesArray) {
                QString content = "@" + targetFileLocation + "_" + entry.toString();
                DBG("[Signals] " + content);
                registerSignal(signalRegisterName, entry.toString());
                DBG("Registered Map: " + signalRegisterName + " : " + entry.toString());
            }
        }
        for (const auto& subscriptionValue : subscriptions) {
            auto subscriptionObj = subscriptionValue.toObject();
            QJsonObject args;
            if (!subscriptionObj["args"].isUndefined()) {
                args = subscriptionObj["args"].toObject();
                if (!args["interval"].isUndefined()) {
                }
            }
            QString signal = subscriptionObj["signal"].toString();
            QStringList commands;
            auto commandsArray = subscriptionObj["commands"].toArray();
            for (const auto& command : commandsArray) {
                commands.append(command.toString());
            }
            if (signalArgu.contains(signal)) {
                QString cmds = commands.join(";") + ";";
                if (!signalArgu[signal].contains(cmds))
                    signalArgu[signal].append(cmds);
                DBG(signal + " => " + commands.join(";") + ";");
                DBG("Now is: " + signalArgu[signal]);
            } else {
                DBG("Cannot Find Signal Name:" + signal);
            }
        }
    }
    ui->packageListVLayout->addStretch();
    updateSignalTreeWidget();
}

QList<PackageManager::packageData> PackageManager::findSubsequentNodes(const packageData& target) {
    QList<packageData> result;
    if (!nodeMap.contains(target))
        return result;
    QList<dataNode*> queue;
    QSet<dataNode*> visited;
    foreach (dataNode* child, nodeMap.value(target)->childList) {
        queue.append(child);
    }
    while (!queue.isEmpty()) {
        dataNode* current = queue.takeFirst();
        if (visited.contains(current))
            continue;
        visited.insert(current);
        result.append(current->data);
        foreach (dataNode* child, current->childList) {
            queue.append(child);
        }
    }

    return result;
}

void PackageManager::cleanupTopology() {
    foreach (dataNode* node, nodeMap.values()) {
        delete node;
    }
    nodeMap.clear();
}

PackageManager::AsulSignal PackageManager::getSignalByArgus(QString sArgu) {
    QMap<QString, QString>::const_iterator sArguIter;
    QString sName = "", sHost = "";
    for (sArguIter = signalArgu.constBegin(); sArguIter != signalArgu.constEnd(); ++sArguIter) {
        if (sArguIter.value() == sArgu)
            sName = sArguIter.key();
    }
    if (!sName.isEmpty()) {
        QMap<QString, QStringList>::const_iterator sHostIter;
        for (sHostIter = signalMap.constBegin(); sHostIter != signalMap.constEnd(); ++sHostIter) {
            if (sHostIter.value().contains(sName))
                sHost = sHostIter.key();
        }
    }
    return AsulSignal(sHost, sName, sArgu);
}

PackageManager::AsulSignal PackageManager::getSignalBySignalName(QString sName) {
    QString sArgu = signalArgu[sName];
    QString sHost = "";
    foreach (const auto& sHosts, signalList) {
        if (signalMap[sHosts].contains(sName))
            sHost = sHosts;
    }
    return AsulSignal(sHost, sName, sArgu);
}

QList<PackageManager::AsulSignal> PackageManager::getAllSignal() {
    QList<PackageManager::AsulSignal> container;
    foreach (const auto& sHost, signalList) {
        QStringList sMap = signalMap[sHost];
        foreach (const auto& sName, sMap) {
            QString sArgu = signalArgu[sName];
            container.append(AsulSignal(sHost, sName, sArgu));
        }
    }
    return container;
}

QList<PackageManager::AsulSignal> PackageManager::getSignalsBySignalHost(QString sHost) {
    QList<PackageManager::AsulSignal> container;
    QStringList sMap = signalMap[sHost];
    foreach (const auto& sName, sMap) {
        QString sArgu = signalArgu[sName];
        container.append(AsulSignal(sHost, sName, sArgu));
    }
    return container;
}

void PackageManager::on_DebugClearBtn_clicked() {
    ui->debugPlainText->clear();
}
