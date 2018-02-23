/********************************************************************************
** Form generated from reading UI file 'SEColorizerAppGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECOLORIZERAPPGUI_H
#define UI_SECOLORIZERAPPGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SEColorizerAppGUIClass
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;

    void setupUi(QWidget *SEColorizerAppGUIClass)
    {
        if (SEColorizerAppGUIClass->objectName().isEmpty())
            SEColorizerAppGUIClass->setObjectName(QStringLiteral("SEColorizerAppGUIClass"));
        SEColorizerAppGUIClass->resize(300, 100);
        SEColorizerAppGUIClass->setMinimumSize(QSize(300, 100));
        verticalLayout = new QVBoxLayout(SEColorizerAppGUIClass);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(SEColorizerAppGUIClass);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);


        retranslateUi(SEColorizerAppGUIClass);

        QMetaObject::connectSlotsByName(SEColorizerAppGUIClass);
    } // setupUi

    void retranslateUi(QWidget *SEColorizerAppGUIClass)
    {
        SEColorizerAppGUIClass->setWindowTitle(QString());
        label->setText(QApplication::translate("SEColorizerAppGUIClass", "SAMSON Element generator pro tip: modify me", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SEColorizerAppGUIClass: public Ui_SEColorizerAppGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECOLORIZERAPPGUI_H
