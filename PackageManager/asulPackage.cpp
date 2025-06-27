#include "asulPackage.h"
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




// logic

void asulPackage::add_dependency(asulPackage *D)
{
    this->dependencyList.push_back(D);
}

void asulPackage::add_signal(asulSignal *S)
{
    this->signalList.push_back(S);
}

void asulPackage::add_subscription(asulSignal *S)
{
    this->subscriptionList.push_back(S);
}





// operator





asulPackage &asulPackage::operator =(const QString &Iav)
{
    return (*this)=asulPackage(Iav);
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











