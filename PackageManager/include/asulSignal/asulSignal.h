#ifndef ASULSIGNAL_H
#define ASULSIGNAL_H

#include <asulSignalManager/asulSignalManager.h>

#include <QFile>
#include <QList>
#include <QObject>
#include <QString>

class asulSubscription;

class asulSignal : public QObject {
    Q_OBJECT

    asulSignalManager* host;
    QString id; // package.signal
    QList<asulSubscription*> subscriberList;

public:
    explicit asulSignal(asulSignalManager* H, const QString& I);

    void addSubscriber(asulSubscription* S);
    void clearSubscriber();

    const asulSignalManager* getHostSignalManager() const { return this->host; }
    const asulPackage* getHostPackage() const { return this->host->getHostPackage(); }
    auto getID() const { return this->id; }
    QString getAliasCommand() const;
    const auto& getSubscriberList() const { return this->subscriberList; }
};

Q_DECLARE_METATYPE(asulSignal*)

#endif // ASULSIGNAL_H
