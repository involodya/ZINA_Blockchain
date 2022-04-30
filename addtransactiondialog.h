#ifndef ADDTRANSACTIONDIALOG_H
#define ADDTRANSACTIONDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <iostream>
#include <QInputDialog>
#include <Transaction.h>
#include <unordered_map>
#include <QDialogButtonBox>
#include "confirmationwindow.h"

namespace Ui {
class AddTransactionDialog;
}

class AddTransactionDialog : public QDialog
{
    Q_OBJECT
public:
    CPKey dialog_recipient;
    ZINA dialog_value;
    std::string dialog_message;
    bool need_to_send = false;
    explicit AddTransactionDialog(QWidget *parent = nullptr);
    ~AddTransactionDialog();

private slots:
    void on_Commit_button_clicked();

    void on_CancelButton_clicked();

private:
    Ui::AddTransactionDialog *ui;
};

#endif // ADDTRANSACTIONDIALOG_H
