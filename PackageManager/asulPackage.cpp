#include "asulPackage.h"
#include "asulSignal.h"
#include "asulSubscription.h"
#include <QStringList>


asulPackage::asulPackage(const QString &I, const QString &V)
{
    this->id=I;
    this->version=V;
}

asulPackage::asulPackage(const QString &IaV)
{
    QStringList parts = IaV.split("@");
    this->id = (parts.size() > 0) ? parts[0] : "";
    this->version = (parts.size() > 1) ? parts[1] : "";
}

asulPackage::~asulPackage()
{
    for(auto *S:this->signalList)   delete S;
    for(auto *S:this->subscriptionList)   delete S;
}




// adds

void asulPackage::addDependency(const QString& D)
{
    this->dependencyList.append(D);
}

void asulPackage::addSignal(asulSignal *S)
{
    this->signalList.append(S);
}

void asulPackage::addSubscription(asulSubscription *S)
{
    this->subscriptionList.append(S);
}






// gets


QString asulPackage::getID() const
{
    return this->id;
}

QString asulPackage::getVersion() const
{
    return this->version;
}

QString asulPackage::getName() const
{
    return this->getID()+"@"+this->getVersion();
}

const auto &asulPackage::getDependencyList() const
{
    return this->dependencyList;
}

const auto &asulPackage::getSigalList() const
{
    return this->signalList;
}

QString asulPackage::toString() const
{
    return this->getName();
}











