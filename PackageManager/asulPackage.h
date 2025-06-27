#ifndef ASULPACKAGE_H
#define ASULPACKAGE_H

#include <QString>
#include <QVector>

#include "asulSignal.h"


class asulPackage
{
    QString id;
    QString version;
    QVector<asulPackage*> dependencyList;

    QVector<asulSignal*> signalList;
    QVector<asulSignal*> subscriptionList;

public:
    asulPackage(const QString& I,const QString& V);
    asulPackage(const QString& IaV);

    void add_dependency(asulPackage* D);
    void add_signal(asulSignal* S);
    void add_subscription(asulSignal* S);

    asulPackage& operator = (const QString& Iav);

    QString getID()const;
    QString getVersion()const;
    QString getName()const;
    const auto& getDependencyList()const;
    const auto& getSigalList()const;

    QString toString()const;
};

#endif // ASULPACKAGE_H
