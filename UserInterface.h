#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QMainWindow>
#include <BlockChain.h>
#include <User.h>

QT_BEGIN_NAMESPACE
namespace Ui { class UserInterface; }
QT_END_NAMESPACE

class UserInterface : public QMainWindow
{
    Q_OBJECT

public:
    UserInterface(QWidget *parent = nullptr);
    ~UserInterface();
    BlockChain local_blockchain;
    User this_user;
    Hash recipient;
    ZINA value;
    std::string message;
private slots:
    void on_Commit_hash_clicked();

private:
    Ui::UserInterface *ui;
};
#endif // USERINTERFACE_H
