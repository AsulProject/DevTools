#include <asulPackage/asulPackage.h>
#include <asulSignal/asulSignal.h>
#include <asulSubscription/asulSubscription.h>

#include <QMap>
#include <QRandomGenerator>
#include <QSet>
#include <QString>

QString randomString(int length) {
    const QString& charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    QString result;
    for (int i = 0; i < length; ++i) {
        int index = QRandomGenerator::global()->bounded(charset.size());
        result.append(charset.at(index));
    }
    return result;
}

std::vector<int> generateRandomIndex(int n, int k) {
    std::vector<int> pool(n, 0);
    std::iota(pool.begin(), pool.end(), 0);

    std::vector<int> result(k, 0);
    std::sample(pool.begin(), pool.end(), result.begin(), k, std::mt19937(std::random_device{}()));

    return result;
}

QList<asulPackage*> asulPackage::generateRandomPackages(int number, int _max_dependency, int _max_signal, int _max_subscription) {
    QMap<QString, asulPackage*> pkg_list;
    QStringList signal_list;

    if (number == 0) {
        // nothing to do
        return pkg_list.values();
    }

    constexpr int id_length = 5;

    for (int i = 1; i <= number; i++) {
        const auto _packages = pkg_list.keys();
        asulPackage* pkg = new asulPackage(nullptr);

        // generate ID
        QString id = "randomPKG_" + randomString(id_length);
        while (pkg_list.contains(id)) {
            id = "randomPKG_" + randomString(id_length);
        }
        pkg->setID(id);

        // generate version
        pkg->setVersion("1.0.0");

        // generate dependency
        {
            int pre_number = int(_packages.size());
            int dependency_number = std::min(_max_dependency, pre_number);

            std::vector<int> indexs = generateRandomIndex(pre_number, dependency_number);

            for (auto j : indexs) {
                pkg->addDependency(_packages[j]);
            }
        }

        // generate signals
        {
            int signal_number = QRandomGenerator::global()->bounded(_max_signal + 1);
            while (signal_number--) {
                QString id = "randomSIG_" + randomString(id_length);
                while (signal_list.contains(id)) {
                    id = "randomSIG_" + randomString(id_length);
                }

                asulSignalManager* signalManager = new asulSignalManager();
                asulSignal* signal = new asulSignal();

                signalManager->setTargetFile(id + ".cfg");
                signal->setID(id);

                signalManager->addSignal(signal);
                pkg->addSignalManager(signalManager);

                signal_list.append(signal->getFullID());
            }
        }

        // generate subscriptions
        {
            QStringList _signals;

            for (const auto& dependency : pkg->getDependencyList()) {
                for (const auto& signalManager : pkg_list[dependency]->getSigalManagerList()) {
                    for (const auto& signal : signalManager->getSignalList()) {
                        _signals.append(signal->getFullID());
                    }
                }
            }

            int pre_number = int(_signals.size());
            int subscription_number = std::min(_max_subscription, pre_number);

            std::vector<int> indexs = generateRandomIndex(pre_number, subscription_number);

            for (auto j : indexs) {
                asulSubscription* subscription = new asulSubscription();
                subscription->setSignal(_signals[j]);
                subscription->addCommand(randomString(3));
                pkg->addSubscription(subscription);
            }
        }

        // add to list
        pkg_list.insert(pkg->getFullID(), pkg);
    }

    return pkg_list.values();
}
