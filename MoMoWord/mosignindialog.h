#ifndef MOSIGNINDIALOG_H
#define MOSIGNINDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>

namespace Ui {
class MoSignInDialog;
}

class MoSignInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoSignInDialog(QWidget *parent = 0, int *userID = nullptr);
    ~MoSignInDialog();

public:
    enum ReturnType : int {
        Success = 1,
        Exit = 2,
        SignUp = 3
    };
private:
    int *userID;
private:
    void clickSignIn();
    void clickSignUp();

private:
    Ui::MoSignInDialog *ui;
};

#endif // MOSIGNINDIALOG_H
