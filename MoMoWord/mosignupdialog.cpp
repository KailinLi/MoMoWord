#include "mosignupdialog.h"
#include "ui_mosignupdialog.h"

MoSignUpDialog::MoSignUpDialog(QWidget *parent, int *userID) :
    QDialog(parent),
    userID(userID),
    ui(new Ui::MoSignUpDialog)
{
    ui->setupUi(this);
    ui->passwdLineEdit->setEchoMode (QLineEdit::Password);
    ui->passwdAgainLineEdit->setEchoMode (QLineEdit::Password);
}

MoSignUpDialog::~MoSignUpDialog()
{
    delete ui;
}
