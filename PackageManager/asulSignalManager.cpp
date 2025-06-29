#include "asulSignalManager.h"

asulSignalManager::asulSignalManager(const QString& T, QObject* parent)
    : QObject{parent}
    , targetFile(T) {
}

void asulSignalManager::addSignal(asulSignal* S) {
    this->signalList.append(S);
}
