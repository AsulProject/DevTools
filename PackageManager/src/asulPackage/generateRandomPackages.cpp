#include <asulPackage/asulPackage.h>

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
    QMap<QString, asulPackage*> list;

    if (number == 0) {
        // nothing to do
        return list.values();
    }

    constexpr int id_length = 5;

    for (int i = 1; i <= number; i++) {
        const auto& packages = list.keys();
        asulPackage* pkg = new asulPackage(nullptr);

        // generate ID
        QString id = "random_" + randomString(id_length);
        while (list.contains(id)) {
            id = "random_" + randomString(id_length);
        }
        pkg->setID(id);

        // generate version
        pkg->setVersion("1.0.0");

        // generate dependency
        {
            int pre_number = int(list.size());
            int dependency_number = std::min(_max_dependency, pre_number);

            std::vector<int> indexs = generateRandomIndex(pre_number, dependency_number);

            for (auto j : indexs) {
                pkg->addDependency(packages[j]);
            }
        }

        // add to list
        list.insert(pkg->getName(), pkg);
    }

    return list.values();
}
