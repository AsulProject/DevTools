#include <asulPackage/asulPackage.h>

#include <QStringList>

void asulPackage::debug(const QString& msg) {
    emit this->sendMsg("[DEBUG] " + msg);
}

void asulPackage::setIaV(const QString& IaV) {
    QStringList parts = IaV.split("@");
    this->id = (parts.size() > 0) ? parts[0] : "";
    this->version = (parts.size() > 1) ? parts[1] : "";
}

asulPackage::asulPackage(QObject* parent)
    : QObject(parent) {
}

asulPackage::~asulPackage() {}

// appends

void asulPackage::addDependency(const QString& IaV) {
    this->dependencyList.append(IaV);
}

void asulPackage::addSignalManager(asulSignalManager* SM) {
    this->signalManagerList.append(SM);
}

void asulPackage::addSubscription(asulSubscription* S) {
    this->subscriptionList.append(S);
}
