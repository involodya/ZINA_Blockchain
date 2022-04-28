/********************************************************************************
** Form generated from reading UI file 'addtransactiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTRANSACTIONDIALOG_H
#define UI_ADDTRANSACTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddTransactionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *input_hash;
    QLabel *label_3;
    QLineEdit *input_value;
    QLabel *label_2;
    QLineEdit *input_message;
    QPushButton *Commit_button;
    QPushButton *pushButton;

    void setupUi(QDialog *AddTransactionDialog)
    {
        if (AddTransactionDialog->objectName().isEmpty())
            AddTransactionDialog->setObjectName(QString::fromUtf8("AddTransactionDialog"));
        AddTransactionDialog->resize(441, 307);
        verticalLayout = new QVBoxLayout(AddTransactionDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(AddTransactionDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        input_hash = new QLineEdit(AddTransactionDialog);
        input_hash->setObjectName(QString::fromUtf8("input_hash"));

        verticalLayout->addWidget(input_hash);

        label_3 = new QLabel(AddTransactionDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        input_value = new QLineEdit(AddTransactionDialog);
        input_value->setObjectName(QString::fromUtf8("input_value"));

        verticalLayout->addWidget(input_value);

        label_2 = new QLabel(AddTransactionDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        input_message = new QLineEdit(AddTransactionDialog);
        input_message->setObjectName(QString::fromUtf8("input_message"));

        verticalLayout->addWidget(input_message);

        Commit_button = new QPushButton(AddTransactionDialog);
        Commit_button->setObjectName(QString::fromUtf8("Commit_button"));

        verticalLayout->addWidget(Commit_button);

        pushButton = new QPushButton(AddTransactionDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(AddTransactionDialog);
        QObject::connect(pushButton, SIGNAL(clicked()), AddTransactionDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(AddTransactionDialog);
    } // setupUi

    void retranslateUi(QDialog *AddTransactionDialog)
    {
        AddTransactionDialog->setWindowTitle(QCoreApplication::translate("AddTransactionDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AddTransactionDialog", "Hash of recipient:", nullptr));
        label_3->setText(QCoreApplication::translate("AddTransactionDialog", "Value (in ZINAs, eg. 123.45)", nullptr));
        label_2->setText(QCoreApplication::translate("AddTransactionDialog", "Message:", nullptr));
        Commit_button->setText(QCoreApplication::translate("AddTransactionDialog", "Commit", nullptr));
        pushButton->setText(QCoreApplication::translate("AddTransactionDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddTransactionDialog: public Ui_AddTransactionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTRANSACTIONDIALOG_H
