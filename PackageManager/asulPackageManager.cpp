#include "asulPackageManager.h"

asulPackageManager::asulPackageManager(){}


// adds

void asulPackageManager::addPackage(asulPackage *P)
{
    this->packageList.append(P);
}

void asulPackageManager::addSignal(asulSignal *S)
{
    this->signalList.append(S);
}

void asulPackageManager::addSubscription(asulSubscription *S)
{
    this->subscriptionList.append(S);
}




// gets

const auto &asulPackageManager::getPackageList() const
{
    return this->packageList;
}

const auto &asulPackageManager::getSignalList() const
{
    return this->signalList;
}

const auto &asulPackageManager::getSubscriptionList() const
{
    return this->subscriptionList;
}
