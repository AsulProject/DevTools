#include <asulException/asulException.h>
#include <asulSubscription/asulSubscription.h>

#include <QDebug>
#include <QVariant>

asulSubscription::asulSubscription(asulPackage* H, const QString& S)
    : QObject(H) {
    this->host = H;
    this->signal = S;
}

// appends

void asulSubscription::addCommand(const QString& command) {
    this->commandList.append(command);
}

void asulSubscription::addCommand(const QList<QString>& commands) {
    this->commandList.append(commands);
}
