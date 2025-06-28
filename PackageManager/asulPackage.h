#ifndef ASULPACKAGE_H
#define ASULPACKAGE_H

#include <QString>
#include <QVector>
#include <QList>

class asulSignal;
class asulSubscription;


class asulPackage
{
    QString id;
    QString version;
    QVector<QString /*IaV*/> dependencyList;

    QVector<asulSignal*> signalList;
    QVector<asulSubscription*> subscriptionList;

public:
    asulPackage(const QString& I,const QString& V);
    asulPackage(const QString& IaV);
    ~asulPackage();

    void addDependency(const QString& D);
    void addSignal(asulSignal* S);
    void addSubscription(asulSubscription* S);

    QString getID()const;
    QString getVersion()const;
    QString getName()const;
    const auto& getDependencyList()const;
    const auto& getSigalList()const;

    QString toString()const;
};

#endif // ASULPACKAGE_H
