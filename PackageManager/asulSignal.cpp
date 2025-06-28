#include "asulSignal.h"

#include "asulSubscription.h"

asulSignal::asulSignal(const QString& H, const QString& I, const QString& T)
    : targetFile(T) {
    this->host = H;
    this->id = I;
}

// adds

void asulSignal::addSubscriber(asulSubscription* S) {
    this->subscriberList.append(S);
}

void asulSignal::clearSubscriber() {
    this->subscriberList.clear();
}

// gets

auto asulSignal::getAliasCommand() const {
    QString cmds = "";
    for (const auto& subscription : this->subscriberList) {
        for (const auto& cmd : subscription->getCommandList()) {
            if (cmds.isEmpty() == false)
                cmds += ";";
            cmds += cmd;
        }
    }
    return QString("alias %1 \"%2\"").arg(this->id, cmds);
}
