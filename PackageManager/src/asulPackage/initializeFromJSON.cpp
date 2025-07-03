#include <asulException/asulException.h>
#include <asulPackage/asulPackage.h>
#include <asulSignal/asulSignal.h>
#include <asulSubscription/asulSubscription.h>

#include <QDebug>

#define DBG(x) this->debug(x)

void asulPackage::initializeFromJSON(const QJsonObject& pRoot) {
    const auto& pData = pRoot["packageData"].toObject();
    const auto& pProvides = pRoot["provides"].toObject();
    const auto& _exports = pProvides["exports"].toArray();
    const auto& _signals = pProvides["signals"].toArray();
    const auto& pSubscriptions = pRoot["subscriptions"].toArray();

    this->id = pData["id"].toString();
    this->version = pData["version"].toString();
    this->dependencyList.clear();
    this->signalManagerList.clear();
    this->subscriptionList.clear();

    DBG("Reading package " + this->getFullID());

    // 处理 dependencies
    for (const auto& dependencyId : pData["dependencies"].toVariant().toStringList()) {
        // 提取依赖
        DBG("-- [Dependencies] " + this->getFullID() + " -> " + dependencyId);
        this->addDependency(dependencyId);
    }

    // 处理 signals
    DBG("-- Handling signals");
    QMap<QString, asulSignalManager*> loaded_signalManager; // loaded signalManager of this package
    QMap<QString, asulSignal*> loaded_signal;               // loaded signal of this package
    for (const auto& signalValue : _signals) {
        const auto& signalObj = signalValue.toObject();
        const auto& entriesArray = signalObj["entries"].toArray();
        QString targetFileLocation = signalObj["targetFileLocation"].toString();

        // id for signal Manager
        QString registerName = this->getFullID() + "/" + targetFileLocation;

        DBG("-- [signalManager] new signalManager " + registerName);

        // construct signalManager
        asulSignalManager* signalManager = new asulSignalManager();
        signalManager->setTargetFile(targetFileLocation);
        this->addSignalManager(signalManager);

        // check signalManager
        if (loaded_signalManager.contains(registerName)) {
            // duplicate signalManager
            throw asulException::duplicateSignalManagerDeclaration(loaded_signalManager[registerName]);
        }
        loaded_signalManager.insert(registerName, signalManager);

        for (const auto& entry : entriesArray) {
            // construct signal
            asulSignal* signal = new asulSignal();
            signal->setID(entry.toString());
            signalManager->addSignal(signal);

            // check signal
            if (loaded_signal.contains(signal->getFullID())) {
                // duplicate signal
                throw asulException::duplicateSignalDeclaration(loaded_signal[registerName]);
            }
            loaded_signal.insert(signal->getFullID(), signal);

            DBG("-- [signal] new signal " + signal->getFullID());
        }
    }

    // 处理 subscriptions
    DBG("-- Handling subsriptions");
    for (const auto& subscriptionValue : pSubscriptions) {
        DBG("-- [subscriptions] new subscription");

        auto subscriptionObj = subscriptionValue.toObject();
        QString signal = subscriptionObj["signal"].toString();

        DBG("-- [subscription] -- signal: " + signal);

        // construct subscription object
        asulSubscription* subscription = new asulSubscription();
        subscription->setSignal(signal);
        this->addSubscription(subscription);

        // add commands
        const auto& commandsArray = subscriptionObj["commands"].toArray();
        for (const auto& command : commandsArray) {
            subscription->addCommand(command.toString());
            DBG("-- [subscription] -- command: " + command.toString());
        }
    }

    DBG("Reading package " + this->getFullID() + " successfully\n");
}
