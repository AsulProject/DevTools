#include <asulPackageManager/asulPackageManager.h>

#include <QList>
#include <QSet>
#include <QString>
#include <QStringList>

QStringList asulPackageManager::getMissingDependencies(const QString& IaV) const {
    QStringList list;

    QSet<QString> visited;

    auto dfs = [&list, &visited, this](auto& dfs, const QString& cur) -> void {
        visited.insert(cur);
        if (this->contain(cur) == false || this->getPackageStatus(cur) == PACKAGE_STATE::DISABLE) {
            list.append(cur);
            return;
        }
        for (const auto& nxt : this->getPackage(cur)->getDependencyList()) {
            if (visited.contains(nxt))
                continue;
            dfs(dfs, nxt);
        }
    };

    dfs(dfs, IaV);

    return list;
}
