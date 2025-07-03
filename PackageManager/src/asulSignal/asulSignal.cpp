#include <asulSignal/asulSignal.h>
#include <asulSubscription/asulSubscription.h>

asulSignal::asulSignal()
    : QObject(nullptr) {}

// adds

void asulSignal::addSubscriber(asulSubscription* S) {
    this->subscriberList.append(S);
}

void asulSignal::clearSubscriber() {
    this->subscriberList.clear();
}

// gets

QString asulSignal::getAliasCommand() const {
    QString cmds = "";

    for (const auto& subscription : this->subscriberList) {
        QStringList cmdList = subscription->getCommandList();
        cmdList.removeAll(QString(""));
        cmds += cmdList.join(";") + ";";
    }

    return QString("alias %1 \"%2\"").arg(this->id, cmds);
}
