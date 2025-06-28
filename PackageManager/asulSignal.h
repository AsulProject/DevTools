#ifndef ASULSIGNAL_H
#define ASULSIGNAL_H

#include <QString>
#include <QVector>
#include <QFile>

class asulPackage;
class asulSubscription;

class asulSignal
{
    asulPackage* host;
    QString id;
    QFile targetFile;
    QVector<asulSubscription*> subscriberList;


public:
    explicit asulSignal(asulPackage* H,const QString& I,const QString& T);

    void addSubscriber(asulSubscription* S);

    asulPackage* getHost()const;
    QString getID()const;
    QString getFullID()const;
    const auto& getTargetFile()const;
    const auto& getSubscriberList()const;
};

#endif // ASULSIGNAL_H
