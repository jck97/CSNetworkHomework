/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *topLable;
    QHBoxLayout *horizontalLayout;
    QLineEdit *input;
    QPushButton *button;
    QLabel *midLable;
    QTableWidget *resTable;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(542, 692);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        topLable = new QLabel(centralwidget);
        topLable->setObjectName(QString::fromUtf8("topLable"));

        gridLayout->addWidget(topLable, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        input = new QLineEdit(centralwidget);
        input->setObjectName(QString::fromUtf8("input"));

        horizontalLayout->addWidget(input);

        button = new QPushButton(centralwidget);
        button->setObjectName(QString::fromUtf8("button"));

        horizontalLayout->addWidget(button);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        midLable = new QLabel(centralwidget);
        midLable->setObjectName(QString::fromUtf8("midLable"));

        gridLayout->addWidget(midLable, 2, 0, 1, 1);

        resTable = new QTableWidget(centralwidget);
        resTable->setObjectName(QString::fromUtf8("resTable"));

        gridLayout->addWidget(resTable, 3, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        topLable->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\345\215\201\350\277\233\345\210\266\344\273\245\347\202\271\345\210\206\351\232\224ip,\347\202\271\345\207\273\346\214\211\351\222\256\345\274\200\345\247\213\347\273\223\346\235\237\346\220\234\347\264\242", nullptr));
        button->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        midLable->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242\345\210\260\347\232\204\347\273\223\346\236\234:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
