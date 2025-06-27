#ifndef ASULPACKAGEMANAGER_H
#define ASULPACKAGEMANAGER_H

#include <QVector>
#include "asulPackage.h"
#include "asulSignal.h"
#include "asulSubscription.h"

class asulPackageManager
{
    QVector<asulPackage*> packageList;
    QVector<asulSignal*> signalList;
    QVector<asulSubscription*> subscriptionList;
public:
    asulPackageManager();
    ~asulPackageManager();

    void addPackage(asulPackage* P);
    void addSignal(asulSignal* S);
    void addSubscription(asulSubscription* S);

    void clear();

    const auto& getPackageList()const;
    const auto& getSignalList()const;
    const auto& getSubscriptionList()const;
};

#endif // ASULPACKAGEMANAGER_H
