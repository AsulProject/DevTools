#include "asulSubscription.h"

#include <QDebug>

#include "asulException.h"

asulSubscription::asulSubscription(asulPackage* H, asulSignal* S) {
    this->host = H;
    this->signal = S;
}

// appends

void asulSubscription::addCommand(const QString& command) {
    this->commandList.append(command);
}

void asulSubscription::addCommand(const QVector<QString>& commands) {
    this->commandList.append(commands);
}

void asulSubscription::addArg(const QString& key, const QString& value) {
    // check if this arg exsits
    if (this->argList.contains(key) == false) {
        throw asulException(QString("arg {%1,%2} already exsits.").arg(key, value));
    }

    // add it to argList
    this->argList.insert(key, value);
}
