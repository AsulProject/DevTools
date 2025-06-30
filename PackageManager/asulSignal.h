#ifndef ASULSIGNAL_H
#define ASULSIGNAL_H

#include <QFile>
#include <QList>
#include <QObject>
#include <QString>

class asulSubscription;

class asulSignal : public QObject {
    Q_OBJECT


    QString host; // IaV
    QString id;   // package.signal
    QString targetFileLocation; //package.signal[targetFileLocation];
    QList<asulSubscription*> subscriberList;

public:
    explicit asulSignal(const QString& H, const QString& I, QObject* parent = nullptr);

    void addSubscriber(asulSubscription* S);
    void clearSubscriber();
    auto getHost() const { return this->host; }
    auto getID() const { return this->id; }
    QString getAliasCommand() const;
    const auto& getSubscriberList() const { return this->subscriberList; }

};

Q_DECLARE_METATYPE(asulSignal*)

#endif // ASULSIGNAL_H
