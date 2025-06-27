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
    QVector<asulPackage*> dependencyList;

    QVector<asulSignal*> signalList;
    QVector<asulSubscription*> subscriptionList;

public:
    asulPackage(const QString& I,const QString& V);
    asulPackage(const QString& IaV);

    void addDependency(asulPackage* D);
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
