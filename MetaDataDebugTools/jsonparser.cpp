#include "jsonparser.h"
#include "ui_jsonparser.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRandomGenerator>
#include <QLineEdit>
#include <QComboBox>
#include <QDir>
#include <QFile>
#define DBG(x) ui->debugPlainTextEdit->appendPlainText(x);
#include "QStringModifier.h"


JsonParser::JsonParser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::JsonParser)
{
    ui->setupUi(this);

    signalList.append("Asul/Signal_Base.cfg");
    signalMap["Asul/Signal_Base.cfg"]=QStringList{"asul.base.Slot1","asul.base.playerSlotChanged.slot1"};
    signalArgu["asul.base.Slot1"]="AliasBase1;AliasBase2;";
    signalArgu["asul.base.playerSlotChanged.slot1"]="slot1;slot2;";

    connect(ui->signalTreeWidget, &QTreeWidget::itemClicked, this, &JsonParser::onSignalItemClicked);
    updateSignalTreeWidget();
}

JsonParser::~JsonParser()
{
    delete ui;
}

void JsonParser::on_p_GeneratedPushButton_clicked()
{


    clearLayout(ui->uiGeneratedVLayout);
    ui->p_providePlainTextEdit->clear();
    ui->p_CFGsPlainTextEdit->clear();
    ui->p_SubScriptionPlainTextEdit->clear();
    sumContents.clear();
    int sector=0;

    //collect i18n list
    QString localesDirPath="locales";
    QDir localesDir(localesDirPath);
    QStringModifier *zh_cnModifier=new QStringModifier(this);
    QStringModifier *en_usModifier=new QStringModifier(this);
    if(localesDir.exists()){
        DBG("[Dir] Locales Dir Exist! Collecting Map for i18n...");
        //collect zh_cn.json
        QFile zh_cnJson("locales/zh_cn.json");
        if(zh_cnJson.open(QIODevice::ReadOnly)){
            DBG("[File] zh_cn.json Found! generating Map for i18n -> zh_cn");
            auto rootObj= QJsonDocument::fromJson(QString(zh_cnJson.readAll()).toUtf8()).array();
            QMap<QString,QString>modifier;
            for(const auto& i18nMap: rootObj){
                auto i18n=i18nMap.toObject();
                modifier[i18n["original"].toString()]=i18n["translation"].toString();
            }
            zh_cnModifier->installModifier(modifier);
            zh_cnJson.close();
        }else{ DBG("[File] zh_cn.json Not Exist! : " +zh_cnJson.errorString()); }

        QFile en_usJson("locales/en_us.json");
        if(en_usJson.open(QIODevice::ReadOnly)){
            DBG("[File] en_us.json Found! generating Map for i18n -> en_us");
            auto rootObj= QJsonDocument::fromJson(QString(en_usJson.readAll()).toUtf8()).array();
            QMap<QString,QString>modifier;
            for(const auto& i18nMap: rootObj){
                auto i18n=i18nMap.toObject();
                modifier[i18n["original"].toString()]=i18n["translation"].toString();
            }
            en_usModifier->installModifier(modifier);
            en_usJson.close();
        }else{ DBG("[File] en_us.json Not Exist! : "+en_usJson.errorString()); }
    }else{ DBG("[Dir] Locales Dir Not Exist!"); }

    QStringModifier * selectModifier;
    if(ui->languageChooseComboBox->currentIndex()==0){
        selectModifier=new QStringModifier(this);
        DBG("Do not enable i18n Func");
    }else if(ui->languageChooseComboBox->currentIndex()==1){
        selectModifier=zh_cnModifier;
        DBG("Use zh_cn i18n Func");
    }else if(ui->languageChooseComboBox->currentIndex()==2){
        selectModifier=en_usModifier;
        DBG("Use zh_cn i18n Func");
    }



    QString originContent=ui->p_JsonInputPlainTextEdit->toPlainText();

    auto rootObject= QJsonDocument::fromJson(originContent.toUtf8()).object();
    auto packageData=rootObject["packageData"].toObject();
    auto provides=rootObject["provides"].toObject();
    auto subscriptions=rootObject["subscriptions"].toArray();
    auto configurations=rootObject["configurations"].toArray();



    //packageData
    QString labelInfo=" Name: "+packageData["name"].toString()
                        +"       Version: "+packageData["version"].toString()
                        +"       Detail: "+packageData["description"].toString()
                        +"       Icon: "+packageData["icon"].toString()
                        +"       Author: "+packageData["author"].toString()
                        +"       license: "+packageData["license"].toString()
                        +"\n dependencies: ";
    QString dependenciesName;
    for(const auto& dependenciesValue: packageData["dependencies"].toArray()){
        dependenciesName+=dependenciesValue.toString()+"   ";
    }
    labelInfo+=dependenciesName;
    ui->l_packageInfoDisplay->setText(labelInfo);


    //provides

    auto exports=provides["exports"].toArray();
    auto _signals=provides["signals"].toArray();

    for(const auto& exportsValue: exports){
        auto exportsObj=exportsValue.toObject();
        QString name=selectModifier->get(exportsObj["name"].toString());
        QString description=selectModifier->get(exportsObj["description"].toString());
        bool continuous=exportsObj["continuous"].toBool();
        QString command=exportsObj["command"].toString();

        QString content="Name: "+name
                        +"Description: "+description
                        +"continues: "+QString(continuous?"True":"False")
                        +"command: "+command;
        ui->p_providePlainTextEdit->appendPlainText("[Exports] "+content);
    }
    for(const auto& signalValue: _signals){
        auto signalObj=signalValue.toObject();
        auto entriesArray=signalObj["entries"].toArray();
        QString targetFileLocation=signalObj["targetFileLocation"].toString();
        QString signalRegisterName=packageData["id"].toString()+"/"+targetFileLocation;
        if(!signalList.contains(signalRegisterName))
            signalList.append(signalRegisterName);

        DBG("Registered List: "+signalRegisterName);
        for(const auto& entry:entriesArray){
            QString content="@"+targetFileLocation+"_"+entry.toString();
            ui->p_providePlainTextEdit->appendPlainText("[Signals] "+content);
            if(!signalMap[signalRegisterName].contains(entry.toString()))
                signalMap[signalRegisterName].append(QStringList{entry.toString()});
            if(!signalArgu.contains(entry.toString()))
                signalArgu[entry.toString()]="";
            DBG("Registered Map: "+signalRegisterName+" : "+entry.toString());
        }

    }
    //subscription
    for(const auto& subscriptionValue:subscriptions){
        auto subscriptionObj=subscriptionValue.toObject();
        QJsonObject args;
        if(!subscriptionObj["args"].isUndefined()){
            args=subscriptionObj["args"].toObject();
            if(!args["interval"].isUndefined()){

            }
        }
        QString signal=subscriptionObj["signal"].toString();
        QStringList commands;
        auto commandsArray=subscriptionObj["commands"].toArray();
        for(const auto& command:commandsArray){
            commands.append(command.toString());
        }
        if(signalArgu.contains(signal)){
            QString cmds=commands.join(";")+";";
            if(!signalArgu[signal].contains(cmds))
                signalArgu[signal].append(cmds);
            ui->p_SubScriptionPlainTextEdit->appendPlainText(signal+" => "+commands.join(";")+";");
            ui->p_SubScriptionPlainTextEdit->appendPlainText("Now is: "+signalArgu[signal]);
        }else{
            DBG("Cannot Find Signal Name:"+signal);
        }

    }

    //configurations

    for (const auto& configValue : configurations){

        auto configObj = configValue.toObject();
        QString targetFile=configObj["targetFileLocation"].toString();
        QString version=configObj["version"].toString();
        auto entries= configObj["entries"].toArray();



        for(const auto& entryValue : entries){
            auto entryObj=entryValue.toObject();
            QString name=selectModifier->get(entryObj["name"].toString());
            QString description=selectModifier->get(entryObj["description"].toString());
            QString type=entryObj["type"].toString();
            QString _default=entryObj["default"].toString();
            auto options=entryObj["options"].toArray();

            QString Id=getRandomId();
            QStringList names,values;
            for(const auto& optionValue : options){
                auto optObj=optionValue.toObject();
                QString optName=selectModifier->get(optObj["name"].toString());
                QString optValue=selectModifier->get(optObj["value"].toString());
                names.append(optName);
                values.append(optValue);
            }
            if(type=="option"){
                QWidget *container=new QWidget(this);
                QHBoxLayout * HLayout=new QHBoxLayout(container);
                QVBoxLayout * textVLayout=new QVBoxLayout();
                textVLayout->addWidget(new QLabel(name,container));
                textVLayout->addWidget(new QLineEdit(description,this));
                QComboBox * selectBox=new QComboBox(container);
                selectBox->addItems(names);
                selectBox->setCurrentIndex(values.indexOf(_default));
                selectBox->setProperty("values",values);
                int mynum=sector;
                sector++;
                sumContents[mynum]=("//File to"+targetFile+"["+version+"]\n"+_default);

                connect(selectBox,&QComboBox::currentIndexChanged,[=](int index){
                    sumContents[mynum]=("//File to"+targetFile+"["+version+"]\n"+values[index]);
                    QString res;
                    foreach(QString val,sumContents){
                        res.append(val+"\n");
                    }
                    ui->p_CFGsPlainTextEdit->setPlainText(res);
                });

                HLayout->addLayout(textVLayout,7);
                HLayout->addWidget(selectBox);
                ui->uiGeneratedVLayout->addWidget(container);
                QString res;
                foreach(QString val,sumContents){
                    res.append(val+"\n");
                }
                ui->p_CFGsPlainTextEdit->setPlainText(res);
                // ui->uiGeneratedVLayout->addWidget(generateArea(name,description,names,values));
            }else {}
        }
    }
    ui->uiGeneratedVLayout->addStretch();
    updateSignalTreeWidget();
}

QString JsonParser::getRandomId()
{
    const QString seed = "abcdefghijklmnopqrstuvwxyz1234567890";
    QString result;

    // 使用全局随机数生成器（无需手动设置种子）
    QRandomGenerator* generator = QRandomGenerator::global();

    for (int i = 0; i < 10; ++i) {
        int index = generator->bounded(seed.length());  // 生成 0 到 seed.length()-1 的随机数
        QChar nextChar = seed.at(index);
        result.append(nextChar);
    }

    return result;
}

QWidget *JsonParser::generateArea(QString name, QString detail, QStringList names, QStringList values)
{
    QWidget *container=new QWidget(this);
    QHBoxLayout * HLayout=new QHBoxLayout(container);
    QVBoxLayout * textVLayout=new QVBoxLayout();
    textVLayout->addWidget(new QLabel(name,container));
    textVLayout->addWidget(new QLineEdit(detail,this));
    QComboBox * selectBox=new QComboBox(container);
    selectBox->addItems(names);
    selectBox->setProperty("values",values);
    HLayout->addLayout(textVLayout,7);
    HLayout->addWidget(selectBox);
    return container;
}
void JsonParser::clearLayout(QLayout* layout) {
    if (!layout) return;

    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {  // 从布局中逐个移除控件
        if (QWidget* widget = item->widget()) {      // 如果是控件
            widget->deleteLater();                   // 安全删除控件
        }
        delete item;  // 删除 QLayoutItem
    }
}


void JsonParser::on_clearDebugMsgButton_clicked()
{
    ui->debugPlainTextEdit->clear();
}

void JsonParser::on_ReadJson_clicked()
{
    QFile data("data.json");
    if(data.open(QIODevice::ReadOnly)){
        ui->p_JsonInputPlainTextEdit->setPlainText(data.readAll());
        data.close();
    }else{ DBG("[File] data.json Not Exist! : " +data.errorString()); }
}

void JsonParser::updateSignalTreeWidget() {
    ui->signalTreeWidget->clear();
    QMap<QString, QStringList>::const_iterator iter;
    for(iter = signalMap.constBegin(); iter != signalMap.constEnd(); ++iter) {
        QTreeWidgetItem *parentItem = new QTreeWidgetItem(ui->signalTreeWidget);
        parentItem->setText(0, iter.key());
        
        foreach(const QString &signal, iter.value()) {
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            childItem->setText(0, signal);
            childItem->setData(0, Qt::UserRole, signal);
        }
    }
    ui->signalTreeWidget->expandAll();
}

void JsonParser::onSignalItemClicked(QTreeWidgetItem *item, int column) {
    if(item->childCount() == 0) { // 子节点
        QString signalName = item->data(0, Qt::UserRole).toString();
        if(signalArgu.contains(signalName)) {
            ui->signalDetailInfo->setText("alias "+signalName+" \""+signalArgu[signalName]+"\"");
            QMap<QString,QStringList>::const_iterator iter;
            QString signalHost="Not defined";
            for(iter = signalMap.constBegin();iter!=signalMap.constEnd();++iter){
                if(iter.value().contains(signalName)){
                    signalHost=iter.key();
                }
            }
            ui->signalHostInfo->setText(signalHost);
        }
    }
}

void JsonParser::on_FileSelectComboBox_currentTextChanged(const QString &arg1)
{
    if(arg1==ui->FileSelectComboBox->itemText(0)) return;
    DBG("Use "+arg1+" (Read In Updated)");
    QFile dataFile(":/data/"+arg1);
    dataFile.open(QIODevice::ReadOnly);
    ui->p_JsonInputPlainTextEdit->setPlainText(dataFile.readAll());
    dataFile.close();

    // delete &dataFile;
}

