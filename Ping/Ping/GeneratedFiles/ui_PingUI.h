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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PingUIClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PingUIClass)
    {
        if (PingUIClass->objectName().isEmpty())
            PingUIClass->setObjectName(QString::fromUtf8("PingUIClass"));
        PingUIClass->resize(600, 400);
        menuBar = new QMenuBar(PingUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        PingUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PingUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PingUIClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PingUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        PingUIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PingUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PingUIClass->setStatusBar(statusBar);

        retranslateUi(PingUIClass);

        QMetaObject::connectSlotsByName(PingUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *PingUIClass)
    {
        PingUIClass->setWindowTitle(QApplication::translate("PingUIClass", "PingUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PingUIClass: public Ui_PingUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PINGUI_H
