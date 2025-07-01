#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <asulPackageManager/asulPackageManager.h>

#include <QMainWindow>
#include <QQueue>
#include <QTreeWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class PackageManager;
}
QT_END_NAMESPACE

class PackageManager : public QMainWindow {
    Q_OBJECT

    asulPackageManager packageManager;

public:
    PackageManager(QWidget* parent = nullptr);
    ~PackageManager();

    void collectPackage(const QString& dirName, asulPackage* currentPackage);
    void collectPackageFromDir(const QString& path);

    void clearLayout(QLayout* layout);
    void onSignalItemClicked(QTreeWidgetItem* item, int column);
    void updateSignalTreeWidget();
private slots:
    void on_DebugClearBtn_clicked();

private:
    Ui::PackageManager* ui;
};
#endif // PACKAGEMANAGER_H
