#include <asulException/asulException.h>
#include <asulSubscription/asulSubscription.h>

#include <QDebug>
#include <QVariant>

asulSubscription::asulSubscription()
    : QObject(nullptr) {
}

// appends

void asulSubscription::addCommand(const QString& command) {
    this->commandList.append(command);
}

void asulSubscription::addCommand(const QStringList& commands) {
    this->commandList.append(commands);
}
