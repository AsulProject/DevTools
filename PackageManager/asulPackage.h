#ifndef ASULPACKAGE_H
#define ASULPACKAGE_H

#include <QList>
#include <QString>
#include <QVector>

class asulSignal;
class asulSubscription;

class asulPackage {
    QString id;
    QString version;
    QVector<QString /*IaV*/> dependencyList;

    QVector<asulSignal*> signalList;
    QVector<asulSubscription*> subscriptionList;

public:
    explicit asulPackage(const QString& I, const QString& V);
    explicit asulPackage(const QString& IaV);
    ~asulPackage();

    void addDependency(const QString& D);
    void addSignal(asulSignal* S);
    void addSubscription(asulSubscription* S);

    inline QString getID() const { return this->id; }
    inline QString getVersion() const { return this->version; }
    inline QString getName() const { return this->id + "@" + this->version; }
    inline const auto& getDependencyList() const { return this->dependencyList; }
    inline const auto& getSigalList() const { return this->signalList; }

    QString toString() const;
};

#endif // ASULPACKAGE_H
