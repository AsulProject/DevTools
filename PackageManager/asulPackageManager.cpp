#include "asulPackageManager.h"
#include "asulException.h"

asulPackageManager::asulPackageManager(){}

asulPackageManager::~asulPackageManager()
{
    this->clear();
}


// adds

void asulPackageManager::addPackage(asulPackage *P)
{
    this->packageList.insert(P->getName(),P);
}

void asulPackageManager::setPackageStatus(const QString &IaV, PACKAGE_STATE status)
{
    // check if this package exsits
    if(this->packageList.contains(IaV)==false){
        throw asulException(QString("package '%1' does not exsit!").arg(IaV));
    }

    // set status
    this->packageStatus[IaV]=status;
}

void asulPackageManager::setAllPackageStatus(PACKAGE_STATE status)
{
    // set status for all packages
    for(const auto& key:this->packageStatus.keys()){
        this->packageStatus[key]=status;
    }
}






void asulPackageManager::clear()
{
    for(auto P:this->packageList)   delete P;
    this->packageList.clear();
}




// gets

const auto &asulPackageManager::getPackageList() const
{
    return this->packageList;
}
