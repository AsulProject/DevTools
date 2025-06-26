#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QQueue>
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
    AsulSignal getSignalBySignalName(QString sName);
    AsulSignal getSignalByArgus(QString sArgu);
    QList<AsulSignal> getSignalsBySignalHost(QString sHost);
    QList<AsulSignal> getAllSignal();

    struct packageData{
        QString Id;
        QString Version;
        packageData(QString I, QString V) : Id(I), Version(V) {}

        // 构造函数：从 "Id@Version" 字符串初始化
        packageData(QString IaV) {
            QStringList parts = IaV.split("@");
            Id = (parts.size() > 0) ? parts[0] : "";
            Version = (parts.size() > 1) ? parts[1] : "";
        }
        packageData() : Id(""), Version("") {}

        packageData& operator=(const QString& str) {
            QStringList parts = str.split("@");
            Id = (parts.size() > 0) ? parts[0] : "";
            Version = (parts.size() > 1) ? parts[1] : "";
            return *this;
        }
        bool operator==(const packageData& other) const {
            return (Id == other.Id) && (Version == other.Version);
        }
        bool operator<(const packageData& other) const {
            return std::tie(Id,Version) < std::tie(other.Id,other.Version);
        }
        // 保留编译器生成的拷贝赋值运算符
        packageData& operator=(const packageData&) = default;

        // 可选：添加输出字符串的辅助函数
        QString toString() const {
            return Id + "@" + Version;
        }
    };

    struct dataNode{
        packageData data;
        QList<dataNode*> childList;

    };

    QMap<packageData,dataNode*> nodeMap;
    QList<packageData> Packages={};

    QStringList signalList /*Package Name + targetFileLocation*/; //All the packages (with signal provided)
    QMap<QString /*Package Name + targetFileLocation*/ ,QStringList /*SignalList*/> signalMap;
    QMap<QString /*Signal*/,QString /*cmds*/> signalArgu;
    QMap<QString /*Package ID*/,QString/*Package Dir Name*/>id_dir_map;
    QMap<packageData , bool> packageEnabledMap;
    QStringList closedPackageList={},PackageList={};

    void registerSignal(QString sHost,QString sName,QString sArgu="");
    void clearLayout(QLayout *layout);
    void clearSignals();
    void addBaseSignals();
    void onSignalItemClicked(QTreeWidgetItem *item, int column);
    void updateSignalTreeWidget();
    void updateSignals(QList<packageData> WithOutPackageList={});


    void cleanupTopology();
    QList<packageData> findSubsequentNodes(const packageData &target);
private slots:
    void on_DebugClearBtn_clicked();

private:
    Ui::PackageManager *ui;
};
#endif // PACKAGEMANAGER_H
