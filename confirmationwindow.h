#ifndef CONFIRMATIONWINDOW_H
#define CONFIRMATIONWINDOW_H

#include <QDialog>

namespace Ui {
class ConfirmationWindow;
}

class ConfirmationWindow : public QDialog
{
    Q_OBJECT
public:
    bool answer = false;
    bool need_fix_transaction = false;
    explicit ConfirmationWindow(QWidget *parent = nullptr);
    ~ConfirmationWindow();

private slots:

    void on_GoBackButton_clicked();

    void on_ConfirmButton_clicked();

private:
    Ui::ConfirmationWindow *ui;
};

#endif // CONFIRMATIONWINDOW_H
