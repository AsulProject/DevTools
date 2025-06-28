#include "asulPackageManager.h"

#include "asulException.h"

asulPackageManager::asulPackageManager() {}

asulPackageManager::~asulPackageManager() {
    this->clear();
}

// appends

void asulPackageManager::addPackage(asulPackage* P) {
    this->packageList.insert(P->getName(), P);
}

void asulPackageManager::setPackageStatus(const QString& IaV, PACKAGE_STATE status) {
    // check if this package exsits
    if (this->packageList.contains(IaV) == false) {
        throw asul::Exception(QString("package '%1' does not exsit!").arg(IaV));
    }

    // set status
    this->packageStatus[IaV] = status;
}

void asulPackageManager::setAllPackageStatus(PACKAGE_STATE status) {
    // set status for all packages
    const auto& packages = this->packageList.keys();
    for (const auto& IaV : packages) {
        this->packageStatus[IaV] = status;
    }
}

// utils

bool asulPackageManager::contain(const QString& IaV) const {
    return this->packageList.contains(IaV);
}

void asulPackageManager::clear() {
    const auto& packages = this->packageList.keys();
    for (const auto& IaV : packages) {
        delete this->packageList[IaV];
    }

    this->packageList.clear();
    this->packageStatus.clear();
}

// gets

asulPackageManager::PACKAGE_STATE asulPackageManager::getPackageStatus(const QString& IaV) const {
    // check if this package exsits
    if (this->packageList.contains(IaV) == false) {
        throw asulException(QString("package '%1' does not exsit!").arg(IaV));
    }

    // get status
    return this->packageStatus[IaV];
}
