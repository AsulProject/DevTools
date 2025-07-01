#ifndef ASULPACKAGE_H
#define ASULPACKAGE_H

#include <stdafx/stdafx.h>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QString>
class asulSignalManager;
class asulSubscription;

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

    static QList<asulPackage*> generateRandomPackages(int number = 1, int _max_dependency = false, int _max_signal = false, int _max_subscription = false);

    void initializeFromJSON(const QJsonObject& pRoot);
    void setID(const QString& I) { this->id = I; }
    void setVersion(const QString& V) { this->version = V; }

    void addDependency(const QString& IaV);
    void addSignalManager(asulSignalManager* SM);
    void addSubscription(asulSubscription* S);

    inline auto getID() const { return this->id; }
    inline auto getVersion() const { return this->version; }
    inline auto getFullID() const { return this->id + "@" + this->version; }
    inline const auto& getDependencyList() const { return this->dependencyList; }
    inline const auto& getSigalManagerList() const { return this->signalManagerList; }
    inline const auto& getSubcriptionList() const { return this->subscriptionList; }

    QString toString() const { return this->getFullID(); }
};

#endif // ASULPACKAGE_H
