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

    QString id;
    QList<asulSubscription*> subscriberList;

public:
    explicit asulSignal();

    inline void setHost(asulSignalManager* H) { QObject::setParent(H); }
    inline void setID(const QString& I) { this->id = I; }

    void addSubscriber(asulSubscription* S);
    void clearSubscriber();

    const asulSignalManager* getHostSignalManager() const { return static_cast<asulSignalManager*>(this->parent()); }
    const asulPackage* getHostPackage() const { return this->getHostSignalManager()->getHostPackage(); }
    QString getID() const { return this->id; }
    QString getFullID() const { return this->getHostPackage()->getID() + "." + this->id; }
    QString getAliasCommand() const;
    const auto& getSubscriberList() const { return this->subscriberList; }
};

Q_DECLARE_METATYPE(asulSignal*)

#endif // ASULSIGNAL_H
