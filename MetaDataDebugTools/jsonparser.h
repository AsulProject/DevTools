#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QMainWindow>
#include "qtreewidget.h"
#include "stdafx.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class JsonParser;
}
QT_END_NAMESPACE

class JsonParser : public QMainWindow
{
    Q_OBJECT

public:
    JsonParser(QWidget *parent = nullptr);
    ~JsonParser();


private slots:
    void on_p_GeneratedPushButton_clicked();

    void on_clearDebugMsgButton_clicked();

    void on_ReadJson_clicked();

    void on_FileSelectComboBox_currentTextChanged(const QString &arg1);

private:

    Ui::JsonParser *ui;
    QString getRandomId();
    QWidget * generateArea(QString name,QString detail,QStringList names,QStringList values);
    void clearLayout(QLayout *layout);
    QMap<int,QString> sumContents;
    QStringList signalList /*Package Name + targetFileLocation*/; //All the packages (with signal provided)
    QMap<QString /*Package Name + targetFileLocation*/ ,QStringList /*SignalList*/> signalMap;
    QMap<QString /*Signal*/,QString /*cmds*/> signalArgu;
    void onSignalItemClicked(QTreeWidgetItem *item, int column);
    void updateSignalTreeWidget();
    void registerSignal(QString Host,QString signalName,QString cmds="");
};
#endif // JSONPARSER_H
