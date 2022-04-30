#include "confirmationwindow.h"
#include "ui_confirmationwindow.h"

ConfirmationWindow::ConfirmationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmationWindow)
{
    ui->setupUi(this);
}

ConfirmationWindow::~ConfirmationWindow()
{
    delete ui;
}


void ConfirmationWindow::on_GoBackButton_clicked()
{
    close();
}

void ConfirmationWindow::on_ConfirmButton_clicked()
{
    answer = true;
    close();
}
