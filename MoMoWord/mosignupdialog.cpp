#include "mosignupdialog.h"
#include "ui_mosignupdialog.h"
#include <QDebug>
#include <QSqlError>

MoSignUpDialog::MoSignUpDialog(QWidget *parent, int *userID) :
    QDialog(parent),
    userID(userID),
    ui(new Ui::MoSignUpDialog)
{
    ui->setupUi(this);
    ui->passwdLineEdit->setEchoMode (QLineEdit::Password);
    ui->passwdAgainLineEdit->setEchoMode (QLineEdit::Password);
    connect (ui->signUpBtn, &QPushButton::clicked, this, &MoSignUpDialog::clickSignUp);
    connect (ui->maleCheckBox, &QCheckBox::clicked, [=](){
        if (ui->maleCheckBox->isChecked ()) ui->femaleCheckBox->setCheckable (false);
        else ui->femaleCheckBox->setCheckable (true);
    });
    connect (ui->femaleCheckBox, &QCheckBox::clicked, [=](){
        if (ui->femaleCheckBox->isChecked ()) ui->maleCheckBox->setCheckable (false);
        else ui->maleCheckBox->setCheckable (true);
    });
    connect (ui->CECheckBox, &QCheckBox::clicked, [=](){
        if (ui->CECheckBox->isChecked ()) ui->ECCheckBox->setCheckable (false);
        else ui->ECCheckBox->setCheckable (true);
    });
    connect (ui->ECCheckBox, &QCheckBox::clicked, [=](){
        if (ui->ECCheckBox->isChecked ()) ui->CECheckBox->setCheckable (false);
        else ui->CECheckBox->setCheckable (true);
    });
}

MoSignUpDialog::~MoSignUpDialog()
{
    delete ui;
}

void MoSignUpDialog::clickSignUp()
{
    //TODO
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare("SELECT * FROM `user` WHERE uname = :uname");
    query.bindValue(":uname", ui->userNameLineEdit->text ());
    query.exec();
    if (query.next()) {
        //TODO
    }
    else {
        query.clear ();
        QByteArray passwordSHA256;
        passwordSHA256.append (ui->passwdLineEdit->text ());
        query.prepare ("insert into user (uname, passwd, sex, daily_plan, english_or_chinese) \
                       VALUE (:uname, :passwd, :sex , :daily_plan, :english_or_chines)");
        query.bindValue (":uname", ui->userNameLineEdit->text ());
        query.bindValue (":passwd", QString::fromLocal8Bit (QCryptographicHash::hash (passwordSHA256, QCryptographicHash::Sha256).toHex ()));
        query.bindValue (":sex", ui->maleCheckBox->isChecked () ? 1 : 0);
        query.bindValue (":daily_plan", ui->planSpinBox->value ());
        query.bindValue (":english_or_chines", ui->ECCheckBox->isChecked () ? 1 : 0);
        if (!query.exec ()) {
            //TODO
            qDebug() << query.lastError().text();
        }
        else {
            query.clear ();
            query.prepare("SELECT * FROM `user` WHERE uname = :uname");
            query.bindValue(":uname", ui->userNameLineEdit->text ());
            query.exec();
            query.next ();
            *userID = query.value ("uid").toInt ();
            accept ();
        }
    }
}
