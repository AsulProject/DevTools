#ifndef ASULPACKAGEMANAGER_H
#define ASULPACKAGEMANAGER_H

#include <QMap>
#include <QVector>

#include "asulPackage.h"

class asulPackageManager {
public:
    enum class PACKAGE_STATE : int {
        ENABLE,
        DISABLE
    };

private:
    QMap<QString /* IaV */, asulPackage*> packageList;
    QMap<QString /* IaV */, PACKAGE_STATE> packageStatus;

public:
    asulPackageManager();
    ~asulPackageManager();

    void addPackage(asulPackage* P);

    void setPackageStatus(const QString& IaV, PACKAGE_STATE status);
    void setAllPackageStatus(PACKAGE_STATE status);

    void buildPackages();

    bool contain(const QString& IaV) const;
    void clear();

    PACKAGE_STATE getPackageStatus(const QString& IaV) const;

    inline const auto& getPackageList() const {
        return this->packageList;
    }
};

#endif // ASULPACKAGEMANAGER_H
