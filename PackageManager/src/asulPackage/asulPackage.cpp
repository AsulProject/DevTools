#include <asulPackage/asulPackage.h>

#include <QStringList>

void asulPackage::debug(const QString& msg) {
    emit this->sendMsg("[DEBUG] " + msg);
}

asulPackage::asulPackage(const QString& I, const QString& V, QObject* parent)
    : QObject(parent) {
    this->id = I;
    this->version = V;
}

asulPackage::asulPackage(const QString& IaV, QObject* parent)
    : QObject(parent) {
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
