#include <asulException/asulException.h>
#include <asulPackageManager/asulPackageManager.h>

void asulPackageManager::disablePackageWithDenpendents(const QString& IaV) {
    // check if this package exsits
    if (this->packageList.contains(IaV) == false) {
        throw asulException::Exception(QString("package '%1' does not exsit!").arg(IaV));
    }

    // generate reversed graph

    QMap<QString, QStringList> edge;

    for (const auto& pkg : this->getPackageList()) {
        for (const auto& dependency : pkg->getDependencyList()) {
            edge[dependency].append(pkg->getName());
        }
    }

    QStringList disable_list;

    QSet<QString> visited;

    auto dfs = [&disable_list, &visited, &edge, this](auto& dfs, const QString& cur) -> void {
        visited.insert(cur);
        if (this->getPackageStatus(cur) == PACKAGE_STATE::ENABLE) {
            disable_list.append(cur);
        }
        for (const auto& nxt : std::as_const(edge[cur])) {
            if (visited.contains(nxt))
                continue;
            dfs(dfs, nxt);
        }
    };

    dfs(dfs, IaV);

    // disable
    for (const auto& pkg /* IaV */ : disable_list) {
        this->setPackageStatus(pkg, PACKAGE_STATE::DISABLE);
    }
}
