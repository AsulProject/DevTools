#include "asulSignal.h"

#include "asulPackage.h"

asulSignal::asulSignal(asulPackage* H, const QString& N, const QString& T)
    : targetFile(T) {
    this->host = H;
    this->id = N;
}

// adds

void asulSignal::addSubscriber(asulSubscription* S) {
    this->subscriberList.append(S);
}
