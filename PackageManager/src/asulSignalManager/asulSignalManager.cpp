#include <asulSignal/asulSignal.h>
#include <asulSignalManager/asulSignalManager.h>

asulSignalManager::asulSignalManager()
    : QObject(nullptr) {
}

void asulSignalManager::addSignal(asulSignal* S) {
    this->signalList.append(S);
    S->setHost(this);
}
