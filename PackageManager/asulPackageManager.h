#ifndef ASULPACKAGEMANAGER_H
#define ASULPACKAGEMANAGER_H

#include <QMap>
#include <QObject>

#include "asulPackage.h"

class asulPackageManager : public QObject {
    Q_OBJECT

public:
    enum class PACKAGE_STATE : int {
        ENABLE,
        DISABLE
    };

private:
    QMap<QString /* IaV */, asulPackage*> packageList;
    QMap<QString /* IaV */, PACKAGE_STATE> packageStatus;

signals:
    void onPackageStatusChanged(const QString& IaV, PACKAGE_STATE status);

public:
    asulPackageManager(QObject* parent = nullptr);
    ~asulPackageManager();

    void addPackage(asulPackage* P, PACKAGE_STATE status = PACKAGE_STATE::ENABLE);

    void setPackageStatus(const QString& IaV, PACKAGE_STATE status);
    void togglePacakgeStatus(const QString& IaV);
    void setAllPackageStatus(PACKAGE_STATE status);

    void buildPackages();

    bool contain(const QString& IaV) const;
    void clear();

    PACKAGE_STATE getPackageStatus(const QString& IaV) const;
    asulPackage* getPackage(const QString& IaV) const;

    inline const auto& getPackageList() const { return this->packageList; }
};

#endif // ASULPACKAGEMANAGER_H
