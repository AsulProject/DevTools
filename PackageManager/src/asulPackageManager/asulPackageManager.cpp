#include <asulException/asulException.h>
#include <asulPackageManager/asulPackageManager.h>

asulPackageManager::asulPackageManager(QObject* parent)
    : QObject(parent) {}

asulPackageManager::~asulPackageManager() {
    this->clear();
}

// appends

void asulPackageManager::addPackage(asulPackage* P, PACKAGE_STATE status) {
    this->packageList.insert(P->getName(), P);
    this->packageStatus.insert(P->getName(), status);

    // signal
    emit this->onPackageStatusChanged(P->getName(), status);
}

// package state

void asulPackageManager::setPackageStatus(const QString& IaV, PACKAGE_STATE status) {
    // check if this package exsits
    if (this->packageList.contains(IaV) == false) {
        throw asulException::Exception(QString("package '%1' does not exsit!").arg(IaV));
    }

    // set status
    this->packageStatus[IaV] = status;

    // signal
    emit this->onPackageStatusChanged(IaV, status);
}

void asulPackageManager::togglePackageStatus(const QString& IaV) {
    // check if this package exsits
    if (this->packageList.contains(IaV) == false) {
        throw asulException::Exception(QString("package '%1' does not exsit!").arg(IaV));
    }

    // set status
    auto& status = this->packageStatus[IaV];
    if (status == PACKAGE_STATE::DISABLE)
        status = PACKAGE_STATE::ENABLE;
    else
        status = PACKAGE_STATE::DISABLE;

    // signal
    emit this->onPackageStatusChanged(IaV, status);
}

void asulPackageManager::setAllPackageStatus(PACKAGE_STATE status) {
    // set status for all packages
    const auto& packages = this->packageList.keys();
    for (const auto& IaV : packages) {
        this->packageStatus[IaV] = status;
        emit this->onPackageStatusChanged(IaV, status);
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
        throw asulException::Exception(QString("package '%1' does not exsit!").arg(IaV));
    }

    // get status
    return this->packageStatus[IaV];
}

asulPackage* asulPackageManager::getPackage(const QString& IaV) const {
    // check if this package exsits
    if (this->packageList.contains(IaV) == false) {
        throw asulException::Exception(QString("package '%1' does not exsit!").arg(IaV));
    }

    return this->packageList[IaV];
}
