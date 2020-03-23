/********************************************************************************
** Form generated from reading UI file 'CubeSettings.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUBESETTINGS_H
#define UI_CUBESETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_CubeSettingsDialog
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *HeightcomboBox;
    QLabel *label_3;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *LeftTopLonlineEdit;
    QLineEdit *LeftTopLatlineEdit;
    QGroupBox *groupBox_2;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *RightBottonLonlineEdit;
    QLineEdit *RightBottonLatlineEdit;
    QLabel *label_4;
    QLineEdit *NamelineEdit;
    QLabel *label_5;
    QComboBox *HeightDownComboBox;
    QComboBox *HeightUpComboBox;
    QLabel *label_8;
    QGroupBox *groupBox_3;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_12;
    QCheckBox *checkBox_13;
    QCheckBox *checkBox_14;
    QCheckBox *checkBox_15;
    QCheckBox *checkBox_16;
    QLabel *label_9;
    QLabel *label_10;

    void setupUi(QDialog *CubeSettingsDialog)
    {
        if (CubeSettingsDialog->objectName().isEmpty())
            CubeSettingsDialog->setObjectName(QString::fromUtf8("CubeSettingsDialog"));
        CubeSettingsDialog->resize(418, 324);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../Debug/icon/boxSetting.png"), QSize(), QIcon::Normal, QIcon::Off);
        CubeSettingsDialog->setWindowIcon(icon);
        buttonBox = new QDialogButtonBox(CubeSettingsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(44, 292, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        HeightcomboBox = new QComboBox(CubeSettingsDialog);
        HeightcomboBox->setObjectName(QString::fromUtf8("HeightcomboBox"));
        HeightcomboBox->setGeometry(QRect(156, 358, 63, 22));
        label_3 = new QLabel(CubeSettingsDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(108, 354, 31, 25));
        groupBox = new QGroupBox(CubeSettingsDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 72, 191, 81));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 20, 31, 21));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 50, 31, 21));
        LeftTopLonlineEdit = new QLineEdit(groupBox);
        LeftTopLonlineEdit->setObjectName(QString::fromUtf8("LeftTopLonlineEdit"));
        LeftTopLonlineEdit->setGeometry(QRect(50, 20, 113, 20));
        LeftTopLatlineEdit = new QLineEdit(groupBox);
        LeftTopLatlineEdit->setObjectName(QString::fromUtf8("LeftTopLatlineEdit"));
        LeftTopLatlineEdit->setGeometry(QRect(50, 50, 113, 20));
        LeftTopLatlineEdit->raise();
        label_2->raise();
        label->raise();
        LeftTopLonlineEdit->raise();
        groupBox_2 = new QGroupBox(CubeSettingsDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(210, 72, 191, 81));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 20, 31, 21));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 50, 31, 21));
        RightBottonLonlineEdit = new QLineEdit(groupBox_2);
        RightBottonLonlineEdit->setObjectName(QString::fromUtf8("RightBottonLonlineEdit"));
        RightBottonLonlineEdit->setGeometry(QRect(50, 20, 113, 20));
        RightBottonLatlineEdit = new QLineEdit(groupBox_2);
        RightBottonLatlineEdit->setObjectName(QString::fromUtf8("RightBottonLatlineEdit"));
        RightBottonLatlineEdit->setGeometry(QRect(50, 50, 113, 20));
        label_4 = new QLabel(CubeSettingsDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 12, 31, 21));
        NamelineEdit = new QLineEdit(CubeSettingsDialog);
        NamelineEdit->setObjectName(QString::fromUtf8("NamelineEdit"));
        NamelineEdit->setGeometry(QRect(60, 12, 339, 20));
        label_5 = new QLabel(CubeSettingsDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(18, 40, 61, 25));
        HeightDownComboBox = new QComboBox(CubeSettingsDialog);
        HeightDownComboBox->setObjectName(QString::fromUtf8("HeightDownComboBox"));
        HeightDownComboBox->setGeometry(QRect(78, 40, 95, 22));
        HeightUpComboBox = new QComboBox(CubeSettingsDialog);
        HeightUpComboBox->setObjectName(QString::fromUtf8("HeightUpComboBox"));
        HeightUpComboBox->setGeometry(QRect(278, 40, 79, 22));
        label_8 = new QLabel(CubeSettingsDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(216, 40, 61, 25));
        groupBox_3 = new QGroupBox(CubeSettingsDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(8, 156, 395, 121));
        checkBox_1 = new QCheckBox(groupBox_3);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setGeometry(QRect(38, 36, 39, 16));
        checkBox_2 = new QCheckBox(groupBox_3);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(86, 36, 71, 16));
        checkBox_3 = new QCheckBox(groupBox_3);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(128, 36, 71, 16));
        checkBox_4 = new QCheckBox(groupBox_3);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(170, 36, 71, 16));
        checkBox_5 = new QCheckBox(groupBox_3);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(214, 36, 71, 16));
        checkBox_6 = new QCheckBox(groupBox_3);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setGeometry(QRect(262, 36, 71, 16));
        checkBox_7 = new QCheckBox(groupBox_3);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setGeometry(QRect(304, 36, 71, 16));
        checkBox_8 = new QCheckBox(groupBox_3);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));
        checkBox_8->setGeometry(QRect(346, 36, 71, 16));
        checkBox_9 = new QCheckBox(groupBox_3);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));
        checkBox_9->setGeometry(QRect(38, 76, 71, 16));
        checkBox_10 = new QCheckBox(groupBox_3);
        checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));
        checkBox_10->setGeometry(QRect(86, 76, 71, 16));
        checkBox_11 = new QCheckBox(groupBox_3);
        checkBox_11->setObjectName(QString::fromUtf8("checkBox_11"));
        checkBox_11->setGeometry(QRect(128, 76, 71, 16));
        checkBox_12 = new QCheckBox(groupBox_3);
        checkBox_12->setObjectName(QString::fromUtf8("checkBox_12"));
        checkBox_12->setGeometry(QRect(170, 76, 71, 16));
        checkBox_13 = new QCheckBox(groupBox_3);
        checkBox_13->setObjectName(QString::fromUtf8("checkBox_13"));
        checkBox_13->setGeometry(QRect(214, 76, 33, 16));
        checkBox_14 = new QCheckBox(groupBox_3);
        checkBox_14->setObjectName(QString::fromUtf8("checkBox_14"));
        checkBox_14->setGeometry(QRect(262, 76, 33, 16));
        checkBox_15 = new QCheckBox(groupBox_3);
        checkBox_15->setObjectName(QString::fromUtf8("checkBox_15"));
        checkBox_15->setGeometry(QRect(306, 76, 35, 16));
        checkBox_16 = new QCheckBox(groupBox_3);
        checkBox_16->setObjectName(QString::fromUtf8("checkBox_16"));
        checkBox_16->setGeometry(QRect(346, 76, 37, 16));
        label_9 = new QLabel(CubeSettingsDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(176, 44, 41, 16));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        label_9->setFont(font);
        label_10 = new QLabel(CubeSettingsDialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(358, 44, 33, 16));
        label_10->setFont(font);

        retranslateUi(CubeSettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CubeSettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CubeSettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CubeSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *CubeSettingsDialog)
    {
        CubeSettingsDialog->setWindowTitle(QApplication::translate("CubeSettingsDialog", "\350\267\237\350\270\252\346\241\206\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CubeSettingsDialog", "\351\253\230\345\272\246\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("CubeSettingsDialog", "\345\267\246\344\270\212", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CubeSettingsDialog", "\347\272\254\345\272\246\357\274\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CubeSettingsDialog", "\347\273\217\345\272\246\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("CubeSettingsDialog", "\345\217\263\344\270\213", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("CubeSettingsDialog", "\347\272\254\345\272\246\357\274\232", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("CubeSettingsDialog", "\347\273\217\345\272\246\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("CubeSettingsDialog", "\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("CubeSettingsDialog", "\344\270\213\351\231\220\351\253\230\345\272\246\357\274\232", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("CubeSettingsDialog", "\344\270\212\351\231\220\351\253\230\345\272\246\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("CubeSettingsDialog", "\345\217\215\345\260\204\347\216\207\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        checkBox_1->setText(QApplication::translate("CubeSettingsDialog", "-5", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("CubeSettingsDialog", "0", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("CubeSettingsDialog", "5", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("CubeSettingsDialog", "10", 0, QApplication::UnicodeUTF8));
        checkBox_5->setText(QApplication::translate("CubeSettingsDialog", "15", 0, QApplication::UnicodeUTF8));
        checkBox_6->setText(QApplication::translate("CubeSettingsDialog", "20", 0, QApplication::UnicodeUTF8));
        checkBox_7->setText(QApplication::translate("CubeSettingsDialog", "25", 0, QApplication::UnicodeUTF8));
        checkBox_8->setText(QApplication::translate("CubeSettingsDialog", "30", 0, QApplication::UnicodeUTF8));
        checkBox_9->setText(QApplication::translate("CubeSettingsDialog", "35", 0, QApplication::UnicodeUTF8));
        checkBox_10->setText(QApplication::translate("CubeSettingsDialog", "40", 0, QApplication::UnicodeUTF8));
        checkBox_11->setText(QApplication::translate("CubeSettingsDialog", "45", 0, QApplication::UnicodeUTF8));
        checkBox_12->setText(QApplication::translate("CubeSettingsDialog", "50", 0, QApplication::UnicodeUTF8));
        checkBox_13->setText(QApplication::translate("CubeSettingsDialog", "55", 0, QApplication::UnicodeUTF8));
        checkBox_14->setText(QApplication::translate("CubeSettingsDialog", "60", 0, QApplication::UnicodeUTF8));
        checkBox_15->setText(QApplication::translate("CubeSettingsDialog", "65", 0, QApplication::UnicodeUTF8));
        checkBox_16->setText(QApplication::translate("CubeSettingsDialog", "70", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("CubeSettingsDialog", "\357\274\210\347\261\263\357\274\211", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("CubeSettingsDialog", "\357\274\210\347\261\263\357\274\211", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CubeSettingsDialog: public Ui_CubeSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUBESETTINGS_H
