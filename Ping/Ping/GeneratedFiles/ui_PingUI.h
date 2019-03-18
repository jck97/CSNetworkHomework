/********************************************************************************
** Form generated from reading UI file 'PingUI.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PINGUI_H
#define UI_PINGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_PingUIClass
{
public:
    QPushButton *button;
    QLabel *topLable;
    QLineEdit *input;
    QLabel *middleLable;
    QTableView *resTable;

    void setupUi(QDialog *PingUIClass)
    {
        if (PingUIClass->objectName().isEmpty())
            PingUIClass->setObjectName(QString::fromUtf8("PingUIClass"));
        PingUIClass->resize(400, 495);
        button = new QPushButton(PingUIClass);
        button->setObjectName(QString::fromUtf8("button"));
        button->setGeometry(QRect(280, 60, 93, 31));
        topLable = new QLabel(PingUIClass);
        topLable->setObjectName(QString::fromUtf8("topLable"));
        topLable->setGeometry(QRect(30, 10, 331, 21));
        input = new QLineEdit(PingUIClass);
        input->setObjectName(QString::fromUtf8("input"));
        input->setGeometry(QRect(30, 60, 241, 31));
        middleLable = new QLabel(PingUIClass);
        middleLable->setObjectName(QString::fromUtf8("middleLable"));
        middleLable->setGeometry(QRect(40, 110, 101, 21));
        resTable = new QTableView(PingUIClass);
        resTable->setObjectName(QString::fromUtf8("resTable"));
        resTable->setGeometry(QRect(20, 150, 361, 331));

        retranslateUi(PingUIClass);

        QMetaObject::connectSlotsByName(PingUIClass);
    } // setupUi

    void retranslateUi(QDialog *PingUIClass)
    {
        PingUIClass->setWindowTitle(QApplication::translate("PingUIClass", "Dialog", nullptr));
        button->setText(QApplication::translate("PingUIClass", "\345\274\200\345\247\213", nullptr));
        topLable->setText(QApplication::translate("PingUIClass", "\350\276\223\345\205\245\345\215\201\350\277\233\345\210\266\344\273\245\347\202\271\345\210\206\351\232\224ip,\347\202\271\345\207\273\346\214\211\351\222\256\345\274\200\345\247\213\347\273\223\346\235\237\346\220\234\347\264\242", nullptr));
        middleLable->setText(QApplication::translate("PingUIClass", "\346\220\234\347\264\242\345\210\260\347\232\204\347\273\223\346\236\234:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PingUIClass: public Ui_PingUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PINGUI_H
