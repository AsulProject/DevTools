#ifndef ASULSIGNAL_H
#define ASULSIGNAL_H

#include <QFile>
#include <QList>
#include <QObject>
#include <QString>

class asulSubscription;

#include "asulSignalManager.h"

class asulSignal : public QObject {
    Q_OBJECT

    asulSignalManager* host;
    QString id; // package.signal
    QList<asulSubscription*> subscriberList;

public:
    explicit asulSignal(asulSignalManager* H, const QString& I, QObject* parent = nullptr);

    void addSubscriber(asulSubscription* S);
    void clearSubscriber();

    auto getHostSignalManager() const { return this->host; }
    auto getHostPackage() const { return this->host->getHostPackage(); }
    auto getID() const { return this->id; }
    QString getAliasCommand() const;
    const auto& getSubscriberList() const { return this->subscriberList; }

};

Q_DECLARE_METATYPE(asulSignal*)

#endif // ASULSIGNAL_H
