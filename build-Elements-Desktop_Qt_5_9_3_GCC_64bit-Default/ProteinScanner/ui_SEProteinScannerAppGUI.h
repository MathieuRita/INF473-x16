/********************************************************************************
** Form generated from reading UI file 'SEProteinScannerAppGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEPROTEINSCANNERAPPGUI_H
#define UI_SEPROTEINSCANNERAPPGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SEProteinScannerAppGUIClass
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;

    void setupUi(QWidget *SEProteinScannerAppGUIClass)
    {
        if (SEProteinScannerAppGUIClass->objectName().isEmpty())
            SEProteinScannerAppGUIClass->setObjectName(QStringLiteral("SEProteinScannerAppGUIClass"));
        SEProteinScannerAppGUIClass->resize(300, 100);
        SEProteinScannerAppGUIClass->setMinimumSize(QSize(300, 100));
        verticalLayout = new QVBoxLayout(SEProteinScannerAppGUIClass);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(SEProteinScannerAppGUIClass);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);


        retranslateUi(SEProteinScannerAppGUIClass);

        QMetaObject::connectSlotsByName(SEProteinScannerAppGUIClass);
    } // setupUi

    void retranslateUi(QWidget *SEProteinScannerAppGUIClass)
    {
        SEProteinScannerAppGUIClass->setWindowTitle(QString());
        label->setText(QApplication::translate("SEProteinScannerAppGUIClass", "SAMSON Element generator pro tip: modify me", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SEProteinScannerAppGUIClass: public Ui_SEProteinScannerAppGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEPROTEINSCANNERAPPGUI_H
