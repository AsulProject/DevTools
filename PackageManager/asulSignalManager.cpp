#include "asulSignalManager.h"

asulSignalManager::asulSignalManager(const QString& H, const QString& T, QObject* parent)
    : QObject{parent}
    , targetFile(T) {
    this->host = H;
}

void asulSignalManager::addSignal(asulSignal* S) {

    this->signalList.append(S);
}
