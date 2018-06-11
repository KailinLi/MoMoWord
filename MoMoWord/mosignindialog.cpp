#include "mosignindialog.h"
#include "ui_mosignindialog.h"
#include <QCryptographicHash>
#include <QDebug>

MoSignInDialog::MoSignInDialog(QWidget *parent, int *userID) :
    QDialog(parent),
    userID(userID),
    ui(new Ui::MoSignInDialog)
{
    ui->setupUi(this);
    connect (ui->loginBtn, &QPushButton::clicked, this, &MoSignInDialog::clickSignIn);
    connect (ui->signupBtn, &QPushButton::clicked, this, &MoSignInDialog::clickSignUp);
    ui->passwdLineEdit->setEchoMode (QLineEdit::Password);
}

MoSignInDialog::~MoSignInDialog()
{
    delete ui;
}

void MoSignInDialog::clickSignIn()
{
//    QSqlQueryModel model;

//    model.setQuery(QString("SELECT uname FROM `user` WHERE uid = %1"), QSqlDatabase::database("momoword"));
//    for (int i = 0; i < model.rowCount(); ++i) {
////            int id = model.record(i).value("id").toInt();
//        QString name = model.record(i).value("uname").toString();
//        qDebug()<< name;
//    }
//    QSqlDatabase db = QSqlDatabase::database ("momoword");
    QSqlQuery query(QSqlDatabase::database("momoword"));
//    query.prepare("SELECT * FROM `user` WHERE uname = :uname");
//    query.bindValue(":uname", "李悯之");
    query.prepare("SELECT * FROM `user` WHERE uid = :uid");
    query.bindValue(":uid", ui->nameLineEdit->text ());
    query.exec();
    if (query.next()) {
        QByteArray passwordSHA256;
        passwordSHA256.append (ui->passwdLineEdit->text ());
        QString hash = QString::fromLocal8Bit (QCryptographicHash::hash (passwordSHA256, QCryptographicHash::Sha256).toHex ());
        QString passwd = query.value ("passwd").toByteArray ();
        if (!hash.compare (passwd)) {
            *userID = query.value ("uid").toInt ();
            done (MoSignInDialog::Success);
        }
        else {
            //TODO
        }
    }
    //    done (MoSignInDialog::Success);
}

void MoSignInDialog::clickSignUp()
{
    done (MoSignInDialog::SignUp);
}
