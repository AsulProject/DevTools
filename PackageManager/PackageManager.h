#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class PackageManager;
}
QT_END_NAMESPACE

class PackageManager : public QMainWindow
{
    Q_OBJECT

public:
    PackageManager(QWidget *parent = nullptr);
    ~PackageManager();
    struct AsulSignal{
        QString SignalHost;
        QString SignalName;
        QString SignalArgu;
        AsulSignal(QString Host,QString Name,QString Argu){
            this->SignalHost=Host;
            this->SignalName=Name;
            this->SignalArgu=Argu;
        }
        AsulSignal();
    };
    QStringList signalList /*Package Name + targetFileLocation*/; //All the packages (with signal provided)
    QMap<QString /*Package Name + targetFileLocation*/ ,QStringList /*SignalList*/> signalMap;
    QMap<QString /*Signal*/,QString /*cmds*/> signalArgu;
    QList<AsulSignal> getSignalsBySignalHost(QString sHost);
    QList<AsulSignal> getAllSignal();
    AsulSignal getSignalBySignalName(QString sName);
    AsulSignal getSignalByArgus(QString sArgu);

private:
    Ui::PackageManager *ui;
};
#endif // PACKAGEMANAGER_H
