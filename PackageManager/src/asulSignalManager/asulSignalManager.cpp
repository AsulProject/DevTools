#include <asulSignal/asulSignal.h>
#include <asulSignalManager/asulSignalManager.h>

asulSignalManager::asulSignalManager(asulPackage* H, const QString& T)
    : QObject(H)
    , targetFile(T) {
    this->host = H;
}

void asulSignalManager::addSignal(asulSignal* S) {
    this->signalList.append(S);
    S->setParent(this);
}
