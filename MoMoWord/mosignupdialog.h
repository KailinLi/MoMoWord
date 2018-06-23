#ifndef MOSIGNUPDIALOG_H
#define MOSIGNUPDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QPropertyAnimation>

namespace Ui {
class MoSignUpDialog;
}

class MoSignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoSignUpDialog(QWidget *parent = 0, int *userID = nullptr);
    ~MoSignUpDialog();

private:
    int *userID;
private:
    void clickSignUp();
    void shakeWindow();

private:
    Ui::MoSignUpDialog *ui;
};

#endif // MOSIGNUPDIALOG_H
