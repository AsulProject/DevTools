#include "asulPackage.h"

#include <QStringList>

#include "asulSignal.h"
#include "asulSubscription.h"

asulPackage::asulPackage(const QString& I, const QString& V) {
    this->id = I;
    this->version = V;
}

asulPackage::asulPackage(const QString& IaV) {
    QStringList parts = IaV.split("@");
    this->id = (parts.size() > 0) ? parts[0] : "";
    this->version = (parts.size() > 1) ? parts[1] : "";
}

asulPackage::~asulPackage() {
    for (auto* S : std::as_const(this->signalList)) delete S;
    for (auto* S : std::as_const(this->subscriptionList)) delete S;
}

// appends

void asulPackage::addDependency(const QString& IaV) {
    this->dependencyList.append(IaV);
}

void asulPackage::addSignal(asulSignal* S) {
    this->signalList.append(S);
}

void asulPackage::addSubscription(asulSubscription* S) {
    this->subscriptionList.append(S);
}
