/********************************************************************************
** Form generated from reading UI file 'UserInterface.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINTERFACE_H
#define UI_USERINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserInterface
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QPushButton *Send_button;
    QPushButton *Receive_button;
    QListWidget *listWidget;
    QLabel *label_3;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QMainWindow *UserInterface)
    {
        if (UserInterface->objectName().isEmpty())
            UserInterface->setObjectName(QString::fromUtf8("UserInterface"));
        UserInterface->setEnabled(true);
        UserInterface->resize(680, 451);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UserInterface->sizePolicy().hasHeightForWidth());
        UserInterface->setSizePolicy(sizePolicy);
        UserInterface->setAutoFillBackground(true);
        centralwidget = new QWidget(UserInterface);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        Send_button = new QPushButton(centralwidget);
        Send_button->setObjectName(QString::fromUtf8("Send_button"));

        gridLayout_2->addWidget(Send_button, 1, 0, 1, 1);

        Receive_button = new QPushButton(centralwidget);
        Receive_button->setObjectName(QString::fromUtf8("Receive_button"));

        gridLayout_2->addWidget(Receive_button, 1, 1, 1, 1);

        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy1);
        listWidget->setAutoFillBackground(false);

        gridLayout_2->addWidget(listWidget, 2, 0, 1, 2);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAutoFillBackground(true);

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayout_2, 2, 0, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 3, 0, 1, 1);

        UserInterface->setCentralWidget(centralwidget);

        retranslateUi(UserInterface);
        QObject::connect(pushButton, SIGNAL(clicked()), UserInterface, SLOT(close()));

        QMetaObject::connectSlotsByName(UserInterface);
    } // setupUi

    void retranslateUi(QMainWindow *UserInterface)
    {
        UserInterface->setWindowTitle(QCoreApplication::translate("UserInterface", "UserInterface", nullptr));
        Send_button->setText(QCoreApplication::translate("UserInterface", "Send", nullptr));
        Receive_button->setText(QCoreApplication::translate("UserInterface", "Receive", nullptr));
        label_3->setText(QCoreApplication::translate("UserInterface", "Balance", nullptr));
        label->setText(QCoreApplication::translate("UserInterface", "1000", nullptr));
        pushButton->setText(QCoreApplication::translate("UserInterface", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserInterface: public Ui_UserInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINTERFACE_H
