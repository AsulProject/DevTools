#ifndef ASULSIGNAL_H
#define ASULSIGNAL_H

#include <QFile>
#include <QList>
#include <QString>

class asulSubscription;

class asulSignal {
    QString host; // IaV
    QString id;
    QFile targetFile;
    QList<asulSubscription*> subscriberList;

public:
    explicit asulSignal(const QString& H, const QString& I, const QString& T);

    void addSubscriber(asulSubscription* S);
    void clearSubscriber();

    auto getHost() const { return this->host; }
    auto getID() const { return this->id; }
    auto getFullID() const { return this->host + "." + this->id; }
    auto getAliasCommand() const;
    const auto& getTargetFile() const { return this->targetFile; }
    const auto& getSubscriberList() const { return this->subscriberList; }
};

#endif // ASULSIGNAL_H
