/********************************************************************************
** Form generated from reading UI file 'ospf_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSPF_UI_H
#define UI_OSPF_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ospf_uiClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QTableWidget *rtTable;
    QLabel *label_2;
    QGraphicsView *rtGraphics;

    void setupUi(QMainWindow *ospf_uiClass)
    {
        if (ospf_uiClass->objectName().isEmpty())
            ospf_uiClass->setObjectName(QString::fromUtf8("ospf_uiClass"));
        ospf_uiClass->resize(373, 723);
        centralWidget = new QWidget(ospf_uiClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        rtTable = new QTableWidget(centralWidget);
        rtTable->setObjectName(QString::fromUtf8("rtTable"));

        gridLayout->addWidget(rtTable, 1, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        rtGraphics = new QGraphicsView(centralWidget);
        rtGraphics->setObjectName(QString::fromUtf8("rtGraphics"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(8);
        rtGraphics->setFont(font);

        gridLayout->addWidget(rtGraphics, 3, 0, 1, 1);

        ospf_uiClass->setCentralWidget(centralWidget);

        retranslateUi(ospf_uiClass);

        QMetaObject::connectSlotsByName(ospf_uiClass);
    } // setupUi

    void retranslateUi(QMainWindow *ospf_uiClass)
    {
        ospf_uiClass->setWindowTitle(QApplication::translate("ospf_uiClass", "ospf_ui", nullptr));
        label->setText(QApplication::translate("ospf_uiClass", "router table item", nullptr));
        label_2->setText(QApplication::translate("ospf_uiClass", "Net Topology", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ospf_uiClass: public Ui_ospf_uiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSPF_UI_H
