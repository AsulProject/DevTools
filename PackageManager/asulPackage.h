#ifndef ASULPACKAGE_H
#define ASULPACKAGE_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QString>
#include "asulSignalManager.h"
#include "asulSubscription.h"
#include "stdafx.h"

class asulPackage : public QObject {
    Q_OBJECT

    QString id;
    QString version;
    QList<QString /*IaV*/> dependencyList;
    QList<asulSignalManager*> signalManagerList;
    QList<asulSubscription*> subscriptionList;
    void debug(const QString& msg);

signals:
    void sendMsg(const QString& msg);

public:
    explicit asulPackage(const QString& I, const QString& V, QObject* parent = nullptr);
    explicit asulPackage(const QString& IaV, QObject* parent = nullptr);
    explicit asulPackage(QObject* parent = nullptr);
    ~asulPackage();

    void initializeFromJSON(const QJsonObject& pRoot);
    void addDependency(const QString& IaV);
    void addSignalManager(asulSignalManager* SM);
    void addSubscription(asulSubscription* S);

    inline auto getID() const { return this->id; }
    inline auto getVersion() const { return this->version; }
    inline auto getName() const { return this->id + "@" + this->version; }
    inline const auto& getDependencyList() const { return this->dependencyList; }
    inline const auto& getSigalManagerList() const { return this->signalManagerList; }
    inline const auto& getSubcriptionList() const { return this->subscriptionList; }

    QString toString() const { return this->getName(); }
};

#endif // ASULPACKAGE_H
