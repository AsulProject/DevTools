#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <QMainWindow>
#include <QQueue>
#include <QTreeWidget>

#include "asulPackageManager.h"

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

    void collectPackageFromJSON(const QString& data);
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
