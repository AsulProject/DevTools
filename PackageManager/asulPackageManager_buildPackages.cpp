#include <QDebug>
#include <QList>
#include <queue>
#include <vector>

#include "asulException.h"
#include "asulPackageManager.h"

void checkCircularDependency(int packageCount, const std::vector<std::vector<int>>& edge, const QList<QString>& index_to_IaV) {
    std::vector<int> checked(packageCount, 0); // packages which have been visited
    std::vector<int> instack(packageCount, 0); // packages which are in the dfs stack
    std::vector<int> stack(0);                 // packages along the path

    auto dfs = [&](auto& dfs, int cur) -> void {
        stack.push_back(cur);
        instack[cur] = true;
        checked[cur] = true;

        for (const auto& nxt : edge[cur]) {
            if (checked[cur] == true)
                continue; // this pack has already been checked. ignore it.

            if (instack[cur] == true) {
                // find a circular dependency

                QList<QString> path;
                for (const auto& pkg : stack) path.append(index_to_IaV[pkg]); // make index(int) -> IaV(QString) for exception

                throw asul::PackageManagerCircularDependencyError(path);
            }

            dfs(dfs, nxt);
        }

        instack[cur] = false;
        stack.pop_back();
    };

    for (int cur = 0; cur < packageCount; cur++) {
        if (checked[cur] == true)
            continue; // this pack has already been checked. ignore it
        dfs(dfs, cur);
    }
}

std::vector<int> generateBuildingOrder(int packageCount, const std::vector<std::vector<int>>& edge) {
    std::queue<int> Queue;                      // queue for bfs
    std::vector<int> inDegree(packageCount, 0); // in-degree for each package

    // calc inDegree
    for (int cur = 0; cur < packageCount; cur++) {
        for (const auto& nxt : edge[cur]) {
            inDegree[nxt]++;
        }
    }

    // push packages with no dependencies into the queue
    for (int cur = 0; cur < packageCount; cur++) {
        if (inDegree[cur] == 0) {
            Queue.push(cur);
        }
    }

    // generate
    std::vector<int> order(0);
    while (Queue.empty() == false) {
        int cur = Queue.front();
        Queue.pop();

        order.push_back(cur);

        for (const auto& nxt : edge[cur]) {
            inDegree[nxt] -= 1;
            // one of nxt's dependencies has been processed

            if (inDegree[nxt] == 0) { // if nxt has no dependencies, we push it into the Queue
                Queue.push(nxt);
            }
        }
    }

    return order;
}

void asulPackageManager::buildPackages() {
    // 1. init package infomation

    const auto packages = this->packageList.keys();
    int packageCount = packages.size();

    QMap<QString /* IaV */, int /* index */> IaV_to_index;
    for (int index = 0; index < packageCount; index++) { // generate a map between package(QString::IaV) and index(int)
        IaV_to_index[packages[index]] = index;
    }

    if (packageCount == 0) {
        // there is no package in this packageManager. return and do nothing.
        return;
    }

    // 2. Build the dependency graph

    std::vector<std::vector<int>> edge;             // edges
    edge.resize(packageCount, std::vector<int>(0)); // resize to fit the graph

    // generate edges
    for (const auto& package : packages) {
        int current_package = IaV_to_index[package];
        for (const auto& IaV : this->packageList[package]->getDependencyList()) {
            int forward_package = IaV_to_index[IaV];
            // add a dependency
            edge[forward_package].push_back(current_package);
        }
    }

    // 3. Check if there is circular dependency
    // if there is one, this function will throw an exception (asul::packageManagerCircularDenpendencyDetected)
    checkCircularDependency(packageCount, edge, packages);

    // 4. Do topo-sort to generate a correct order of building packages
    std::vector<int> order = generateBuildingOrder(packageCount, edge);
}
