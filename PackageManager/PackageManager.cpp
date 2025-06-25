#include "PackageManager.h"
#include "ui_PackageManager.h"

PackageManager::PackageManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PackageManager)
{
    ui->setupUi(this);
}

PackageManager::~PackageManager()
{
    delete ui;
}

PackageManager::AsulSignal PackageManager::getSignalByArgus(QString sArgu)
{
    QMap<QString, QString>::const_iterator sArguIter;
    QString sName="",sHost="";
    for(sArguIter = signalArgu.constBegin(); sArguIter != signalArgu.constEnd(); ++sArguIter) {
        if(sArguIter.value() == sArgu) sName = sArguIter.key();
    }
    if(!sName.isEmpty()){
        QMap<QString,QStringList>::const_iterator sHostIter;
        for(sHostIter = signalMap.constBegin();sHostIter != signalMap.constEnd(); ++sHostIter){
            if(sHostIter.value().contains(sName)) sHost = sHostIter.key();
        }
    }
    return AsulSignal(sHost,sName,sArgu);
}

PackageManager::AsulSignal PackageManager::getSignalBySignalName(QString sName)
{
    QString sArgu=signalArgu[sName];
    QString sHost="";
    foreach(const auto& sHosts,signalList){
        if(signalMap[sHosts].contains(sName)) sHost=sHosts;
    }
    return AsulSignal(sHost,sName,sArgu);
}

QList<PackageManager::AsulSignal> PackageManager::getAllSignal()
{
    QList<PackageManager::AsulSignal>container;
    foreach(const auto& sHost,signalList){
        QStringList sMap=signalMap[sHost];
        foreach(const auto& sName,sMap){
            QString sArgu=signalArgu[sName];
            container.append(AsulSignal(sHost,sName,sArgu));
        }
    }
    return container;
}

QList<PackageManager::AsulSignal> PackageManager::getSignalsBySignalHost(QString sHost)
{
    QList<PackageManager::AsulSignal>container;
    QStringList sMap=signalMap[sHost];
    foreach(const auto& sName,sMap){
        QString sArgu=signalArgu[sName];
        container.append(AsulSignal(sHost,sName,sArgu));
    }
    return container;
}
