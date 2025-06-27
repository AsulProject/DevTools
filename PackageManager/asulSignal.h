#ifndef ASULSIGNAL_H
#define ASULSIGNAL_H

#include <QString>
#include <QVector>
#include <QFile>

class asulPackage;

class asulSignal
{
    asulPackage* host;
    QString id;
    QFile targetFile;
    QVector<QString> subscriberList;


public:
    asulSignal(asulPackage* H,const QString& I);

    asulPackage* getHost()const;
    QString getID()const;
    QString getFullID()const;
    const auto& getTargetFile()const;
    const auto& getSubscriberList()const;
};

#endif // ASULSIGNAL_H
