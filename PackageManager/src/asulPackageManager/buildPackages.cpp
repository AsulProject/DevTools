#include <asulException/asulException.h>
#include <asulPackageManager/asulPackageManager.h>
#include <asulSignal/asulSignal.h>
#include <asulSubscription/asulSubscription.h>

#include <QDebug>
#include <QList>
#include <queue>
#include <vector>

void checkCircularDependency(int packageCount, const std::vector<std::vector<int>>& edge, const QStringList& index_to_IaV) {
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

                QStringList path;
                for (const auto& index : stack) path.append(index_to_IaV[index]); // make index(int) -> IaV(QString) for exception

                throw asulException::circularDependency(path);
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

    QStringList index_to_IaV;
    QList<asulPackage*> index_to_ptr;

    for (auto it = this->packageList.begin(); it != this->packageList.end(); it++) {
        // it = [ IaV(QString) , pkg(asulPackage*) ]

        // clear signal's subscriber
        for (const auto& signalManager : it.value()->getSigalManagerList()) {
            for (const auto& signal : signalManager->getSignalList()) {
                signal->clearSubscriber();
            }
        }

        // skip disabled package
        if (this->getPackageStatus(it.key()) == asulPackageManager::PACKAGE_STATE::DISABLE)
            continue;

        // collect enabled package
        index_to_IaV.append(it.key());
        index_to_ptr.append(it.value());
    }
    int packageCount = index_to_IaV.size();

    QMap<QString /* IaV */, int /* index */> IaV_to_index;
    for (int index = 0; index < packageCount; index++) { // generate a map between package(QString::IaV) and index(int)
        IaV_to_index[index_to_IaV[index]] = index;
    }

    // 2. Build the dependency graph

    if (packageCount == 0) {
        // there is no enabled package in this packageManager. return and do nothing.
        return;
    }

    std::vector<std::vector<int>> edge;             // edges
    edge.resize(packageCount, std::vector<int>(0)); // resize to fit the graph

    // generate edges
    for (int cur = 0; cur < packageCount; cur++) {
        for (const auto& IaV : index_to_ptr[cur]->getDependencyList()) {
            if (IaV_to_index.contains(IaV) == false) {
                // unknown dependency
                // the denpendency pkg may be disabled
                // or deoendency pkg does not exsit
                throw asulException::unkownDependency(index_to_IaV[cur], IaV);
            }

            int dependency = IaV_to_index[IaV];
            // add a dependency
            edge[dependency].push_back(cur);
        }
    }

    // 3. Check if there is circular dependency
    // if there is one, this function will throw an exception (asulException::circularDenpendencyDetected)
    checkCircularDependency(packageCount, edge, index_to_IaV);

    // 4. Do topo-sort to generate a correct order of package building
    std::vector<int> order = generateBuildingOrder(packageCount, edge);

    // 5. load packages
    QMap<QString, asulSignal*> loaded_signal; // loaded signals

    for (auto cur : order) {
        // load it's signals
        for (const auto& signalManager : index_to_ptr[cur]->getSigalManagerList()) {
            for (const auto& signal : signalManager->getSignalList()) {
                loaded_signal.insert(signal->getFullID(), signal);
            }
        }

        // process it's subscriptions
        for (const auto& subscription : index_to_ptr[cur]->getSubcriptionList()) {
            // if the host package hasn't loaded, throw an exception (asulException::unknownSignal)
            // the author may forget to add dependency
            // or dependency was disabled
            if (loaded_signal.contains(subscription->getSignal()) == false) {
                qDebug() << loaded_signal << Qt::endl;
                throw asulException::unkownSignal(subscription);
            }

            // add it to targetSignal's subscriber list
            loaded_signal[subscription->getSignal()]->addSubscriber(subscription);
        }
    }

    // build end
}
