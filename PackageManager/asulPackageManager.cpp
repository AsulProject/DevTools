#include "asulPackageManager.h"

asulPackageManager::asulPackageManager(){}

asulPackageManager::~asulPackageManager()
{
    this->clear();
}


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






void asulPackageManager::clear()
{
    for(auto P:this->packageList)   delete P;
    for(auto S:this->signalList)    delete S;
    for(auto S:this->subscriptionList)    delete S;
    this->packageList.clear();
    this->signalList.clear();
    this->subscriptionList.clear();
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
