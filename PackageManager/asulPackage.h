#ifndef ASULPACKAGE_H
#define ASULPACKAGE_H

#include <QList>
#include <QString>

#include "asulSignal.h"
#include "asulSubscription.h"

class asulPackage {
    QString id;
    QString version;
    QList<QString /*IaV*/> dependencyList;

    QList<asulSignal*> signalList;
    QList<asulSubscription*> subscriptionList;

public:
    explicit asulPackage(const QString& I, const QString& V);
    explicit asulPackage(const QString& IaV);
    ~asulPackage();

    void addDependency(const QString& IaV);
    void addSignal(asulSignal* S);
    void addSubscription(asulSubscription* S);

    inline QString getID() const { return this->id; }
    inline QString getVersion() const { return this->version; }
    inline QString getName() const { return this->id + "@" + this->version; }
    inline const auto& getDependencyList() const { return this->dependencyList; }
    inline const auto& getSigalList() const { return this->signalList; }
    inline const auto& getSubcriptionList() const { return this->subscriptionList; }

    QString toString() const { return this->getName(); }
};

#endif // ASULPACKAGE_H
