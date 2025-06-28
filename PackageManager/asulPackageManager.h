#ifndef ASULPACKAGEMANAGER_H
#define ASULPACKAGEMANAGER_H

#include <QVector>
#include <QMap>
#include "asulPackage.h"
#include "asulSignal.h"
#include "asulSubscription.h"

class asulPackageManager
{
public:
    enum class PACKAGE_STATE : int {
        ENABLE,
        DISABLE
    };

private:
    QMap<QString /* IaV */,asulPackage*> packageList;
    QMap<QString /* IaV */,PACKAGE_STATE> packageStatus;

public:
    asulPackageManager();
    ~asulPackageManager();

    void addPackage(asulPackage* P);

    void setPackageStatus(const QString& IaV,PACKAGE_STATE status);
    void setAllPackageStatus(PACKAGE_STATE status);

    bool contain(const QString& IaV)const;
    void clear();

    const auto& getPackageList()const;
    const auto& getSignalList()const;
    const auto& getSubscriptionList()const;
    PACKAGE_STATE getPackageStatus(const QString& IaV)const;
};

#endif // ASULPACKAGEMANAGER_H
