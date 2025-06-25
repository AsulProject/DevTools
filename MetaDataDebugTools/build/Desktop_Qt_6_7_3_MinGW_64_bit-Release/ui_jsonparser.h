/********************************************************************************
** Form generated from reading UI file 'jsonparser.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JSONPARSER_H
#define UI_JSONPARSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JsonParser
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QComboBox *languageChooseComboBox;
    QPushButton *ReadJson;
    QPlainTextEdit *p_JsonInputPlainTextEdit;
    QPushButton *p_GeneratedPushButton;
    QLabel *l_JsonTitleLabel;
    QComboBox *FileSelectComboBox;
    QGroupBox *groupBox_2;
    QLabel *l_ProvideLabel;
    QPlainTextEdit *p_SubScriptionPlainTextEdit;
    QLabel *l_CFGsLabel;
    QPlainTextEdit *p_CFGsPlainTextEdit;
    QLabel *l_SubScriptionLabel;
    QLabel *l_ControlsLabel;
    QPlainTextEdit *p_providePlainTextEdit;
    QGroupBox *groupBox_5;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *uiGeneratedVLayout;
    QGroupBox *groupBox_3;
    QLineEdit *signalDetailInfo;
    QLabel *DebugLabel;
    QPlainTextEdit *debugPlainTextEdit;
    QTreeWidget *signalTreeWidget;
    QPushButton *clearDebugMsgButton;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *signalHostInfo;
    QGroupBox *groupBox_4;
    QLabel *l_packageInfoDisplay;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *JsonParser)
    {
        if (JsonParser->objectName().isEmpty())
            JsonParser->setObjectName("JsonParser");
        JsonParser->resize(2020, 1185);
        JsonParser->setMinimumSize(QSize(2020, 1185));
        JsonParser->setMaximumSize(QSize(2020, 1185));
        centralwidget = new QWidget(JsonParser);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 100, 441, 751));
        languageChooseComboBox = new QComboBox(groupBox);
        languageChooseComboBox->addItem(QString());
        languageChooseComboBox->addItem(QString());
        languageChooseComboBox->addItem(QString());
        languageChooseComboBox->setObjectName("languageChooseComboBox");
        languageChooseComboBox->setGeometry(QRect(31, 30, 381, 23));
        ReadJson = new QPushButton(groupBox);
        ReadJson->setObjectName("ReadJson");
        ReadJson->setGeometry(QRect(110, 80, 141, 23));
        p_JsonInputPlainTextEdit = new QPlainTextEdit(groupBox);
        p_JsonInputPlainTextEdit->setObjectName("p_JsonInputPlainTextEdit");
        p_JsonInputPlainTextEdit->setGeometry(QRect(31, 110, 381, 561));
        p_GeneratedPushButton = new QPushButton(groupBox);
        p_GeneratedPushButton->setObjectName("p_GeneratedPushButton");
        p_GeneratedPushButton->setGeometry(QRect(31, 680, 381, 51));
        l_JsonTitleLabel = new QLabel(groupBox);
        l_JsonTitleLabel->setObjectName("l_JsonTitleLabel");
        l_JsonTitleLabel->setGeometry(QRect(31, 66, 71, 40));
        FileSelectComboBox = new QComboBox(groupBox);
        FileSelectComboBox->addItem(QString());
        FileSelectComboBox->addItem(QString());
        FileSelectComboBox->addItem(QString());
        FileSelectComboBox->setObjectName("FileSelectComboBox");
        FileSelectComboBox->setGeometry(QRect(290, 80, 121, 23));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(470, 100, 1531, 751));
        l_ProvideLabel = new QLabel(groupBox_2);
        l_ProvideLabel->setObjectName("l_ProvideLabel");
        l_ProvideLabel->setGeometry(QRect(40, 50, 110, 16));
        p_SubScriptionPlainTextEdit = new QPlainTextEdit(groupBox_2);
        p_SubScriptionPlainTextEdit->setObjectName("p_SubScriptionPlainTextEdit");
        p_SubScriptionPlainTextEdit->setGeometry(QRect(410, 90, 330, 640));
        p_SubScriptionPlainTextEdit->setReadOnly(true);
        l_CFGsLabel = new QLabel(groupBox_2);
        l_CFGsLabel->setObjectName("l_CFGsLabel");
        l_CFGsLabel->setGeometry(QRect(790, 50, 42, 15));
        p_CFGsPlainTextEdit = new QPlainTextEdit(groupBox_2);
        p_CFGsPlainTextEdit->setObjectName("p_CFGsPlainTextEdit");
        p_CFGsPlainTextEdit->setGeometry(QRect(790, 90, 330, 640));
        p_CFGsPlainTextEdit->setReadOnly(true);
        l_SubScriptionLabel = new QLabel(groupBox_2);
        l_SubScriptionLabel->setObjectName("l_SubScriptionLabel");
        l_SubScriptionLabel->setGeometry(QRect(410, 50, 150, 16));
        l_ControlsLabel = new QLabel(groupBox_2);
        l_ControlsLabel->setObjectName("l_ControlsLabel");
        l_ControlsLabel->setGeometry(QRect(1170, 50, 61, 16));
        p_providePlainTextEdit = new QPlainTextEdit(groupBox_2);
        p_providePlainTextEdit->setObjectName("p_providePlainTextEdit");
        p_providePlainTextEdit->setGeometry(QRect(30, 90, 330, 640));
        p_providePlainTextEdit->setReadOnly(true);
        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(1170, 70, 321, 661));
        verticalLayoutWidget = new QWidget(groupBox_5);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 20, 321, 639));
        uiGeneratedVLayout = new QVBoxLayout(verticalLayoutWidget);
        uiGeneratedVLayout->setObjectName("uiGeneratedVLayout");
        uiGeneratedVLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(20, 860, 1981, 291));
        signalDetailInfo = new QLineEdit(groupBox_3);
        signalDetailInfo->setObjectName("signalDetailInfo");
        signalDetailInfo->setGeometry(QRect(1330, 40, 641, 23));
        signalDetailInfo->setReadOnly(true);
        DebugLabel = new QLabel(groupBox_3);
        DebugLabel->setObjectName("DebugLabel");
        DebugLabel->setGeometry(QRect(30, 20, 101, 21));
        debugPlainTextEdit = new QPlainTextEdit(groupBox_3);
        debugPlainTextEdit->setObjectName("debugPlainTextEdit");
        debugPlainTextEdit->setGeometry(QRect(30, 50, 741, 231));
        signalTreeWidget = new QTreeWidget(groupBox_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        signalTreeWidget->setHeaderItem(__qtreewidgetitem);
        signalTreeWidget->setObjectName("signalTreeWidget");
        signalTreeWidget->setGeometry(QRect(800, 20, 471, 261));
        clearDebugMsgButton = new QPushButton(groupBox_3);
        clearDebugMsgButton->setObjectName("clearDebugMsgButton");
        clearDebugMsgButton->setGeometry(QRect(690, 20, 80, 23));
        label = new QLabel(groupBox_3);
        label->setObjectName("label");
        label->setGeometry(QRect(1290, 50, 53, 15));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(1290, 90, 31, 16));
        signalHostInfo = new QLineEdit(groupBox_3);
        signalHostInfo->setObjectName("signalHostInfo");
        signalHostInfo->setGeometry(QRect(1330, 80, 641, 23));
        signalHostInfo->setReadOnly(true);
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(20, 10, 1981, 80));
        l_packageInfoDisplay = new QLabel(groupBox_4);
        l_packageInfoDisplay->setObjectName("l_packageInfoDisplay");
        l_packageInfoDisplay->setGeometry(QRect(10, 20, 1961, 51));
        QFont font;
        font.setPointSize(14);
        l_packageInfoDisplay->setFont(font);
        JsonParser->setCentralWidget(centralwidget);
        menubar = new QMenuBar(JsonParser);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 2020, 20));
        JsonParser->setMenuBar(menubar);
        statusbar = new QStatusBar(JsonParser);
        statusbar->setObjectName("statusbar");
        JsonParser->setStatusBar(statusbar);

        retranslateUi(JsonParser);

        QMetaObject::connectSlotsByName(JsonParser);
    } // setupUi

    void retranslateUi(QMainWindow *JsonParser)
    {
        JsonParser->setWindowTitle(QCoreApplication::translate("JsonParser", "JsonParser", nullptr));
        groupBox->setTitle(QCoreApplication::translate("JsonParser", "GetIn", nullptr));
        languageChooseComboBox->setItemText(0, QCoreApplication::translate("JsonParser", "Choose Language (Need \"Locales Dir Existed in {PWD}\")", nullptr));
        languageChooseComboBox->setItemText(1, QCoreApplication::translate("JsonParser", "zh_cn", nullptr));
        languageChooseComboBox->setItemText(2, QCoreApplication::translate("JsonParser", "en_us", nullptr));

        ReadJson->setText(QCoreApplication::translate("JsonParser", "Read ./data.json", nullptr));
        p_JsonInputPlainTextEdit->setPlainText(QString());
        p_GeneratedPushButton->setText(QCoreApplication::translate("JsonParser", "Parse", nullptr));
        l_JsonTitleLabel->setText(QCoreApplication::translate("JsonParser", "Json", nullptr));
        FileSelectComboBox->setItemText(0, QCoreApplication::translate("JsonParser", "Choose File", nullptr));
        FileSelectComboBox->setItemText(1, QCoreApplication::translate("JsonParser", "data.json", nullptr));
        FileSelectComboBox->setItemText(2, QCoreApplication::translate("JsonParser", "data2.json", nullptr));

        groupBox_2->setTitle(QCoreApplication::translate("JsonParser", "OutPut", nullptr));
        l_ProvideLabel->setText(QCoreApplication::translate("JsonParser", "Provide", nullptr));
        l_CFGsLabel->setText(QCoreApplication::translate("JsonParser", "CFGs", nullptr));
        l_SubScriptionLabel->setText(QCoreApplication::translate("JsonParser", "Subscription", nullptr));
        l_ControlsLabel->setText(QCoreApplication::translate("JsonParser", "Controls", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("JsonParser", "Layout", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("JsonParser", "Debug Area", nullptr));
        signalDetailInfo->setPlaceholderText(QCoreApplication::translate("JsonParser", "Click And Show Area", nullptr));
        DebugLabel->setText(QCoreApplication::translate("JsonParser", "Debug", nullptr));
        clearDebugMsgButton->setText(QCoreApplication::translate("JsonParser", "Clear", nullptr));
        label->setText(QCoreApplication::translate("JsonParser", "Argu:", nullptr));
        label_2->setText(QCoreApplication::translate("JsonParser", "Host:", nullptr));
        signalHostInfo->setPlaceholderText(QCoreApplication::translate("JsonParser", "Click And Show Area", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("JsonParser", "Display", nullptr));
        l_packageInfoDisplay->setText(QCoreApplication::translate("JsonParser", "%Display%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JsonParser: public Ui_JsonParser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JSONPARSER_H
