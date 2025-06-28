#ifndef ASULSIGNAL_H
#define ASULSIGNAL_H

#include <QFile>
#include <QString>
#include <QVector>

#include "asulPackage.h"

class asulSubscription;

class asulSignal {
    asulPackage* host;
    QString id;
    QFile targetFile;
    QVector<asulSubscription*> subscriberList;

public:
    explicit asulSignal(asulPackage* H, const QString& I, const QString& T);

    void addSubscriber(asulSubscription* S);

    asulPackage* getHost() const { return this->host; }
    QString getID() const { return this->id; }
    QString getFullID() const { return this->host->getName() + "." + this->id; }
    const auto& getTargetFile() const { return this->targetFile; }
    const auto& getSubscriberList() const { return this->subscriberList; }
};

#endif // ASULSIGNAL_H
