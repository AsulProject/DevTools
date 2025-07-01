#include <asulException/asulException.h>
#include <asulPackageManager/asulPackageManager.h>

void asulPackageManager::enablePackageWithDenpendencies(const QString& IaV) {
    // check if this package exsits
    if (this->packageList.contains(IaV) == false) {
        throw asulException::Exception(QString("package '%1' does not exsit!").arg(IaV));
    }

    QStringList enable_list;

    QSet<QString> visited;

    auto dfs = [&enable_list, &visited, this](auto& dfs, const QString& cur) -> void {
        visited.insert(cur);
        if (this->getPackageStatus(cur) == PACKAGE_STATE::DISABLE) {
            enable_list.append(cur);
        }
        for (const auto& nxt : this->getPackage(cur)->getDependencyList()) {
            if (visited.contains(nxt))
                continue;
            if (this->contain(nxt) == false)
                throw asulException::unkownDependency(cur, nxt);
            dfs(dfs, nxt);
        }
    };

    dfs(dfs, IaV);

    // enable
    for (const auto& pkg /* IaV */ : enable_list) {
        this->setPackageStatus(pkg, PACKAGE_STATE::ENABLE);
    }
}
