#include "mosignindialog.h"
#include "ui_mosignindialog.h"
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
    connect (ui->connectBtn, &QToolButton::clicked, this, &MoSignInDialog::clickConnect);
    ui->loginBtn->setEnabled (false);
    ui->signupBtn->setEnabled (false);
    QPixmap pic("://images/logo_min.png");
    ui->logoLabel->setPixmap(pic.scaledToHeight (50));
    ui->nameLineEdit->setFocus ();
//    this->setStyleSheet ("background-color: rgb(0, 190, 159, 20%)");
    this->setStyleSheet ("background-color: rgb(255, 255, 255)");
}

MoSignInDialog::~MoSignInDialog()
{
    delete ui;
}

void MoSignInDialog::clickSignIn()
{
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare("SELECT * FROM `user` WHERE uname = :uname");
    query.bindValue(":uname", ui->nameLineEdit->text ());
//    query.prepare("SELECT * FROM `user` WHERE uid = :uid");
//    query.bindValue(":uid", ui->nameLineEdit->text ());
    query.exec();
    if (query.next()) {
        QByteArray passwordSHA256;
        passwordSHA256.append (ui->passwdLineEdit->text ());
        QString hash = QString::fromLocal8Bit (QCryptographicHash::hash (passwordSHA256, QCryptographicHash::Sha256).toHex ());
        QString passwd = query.value ("passwd").toByteArray ();
        if (!hash.compare (passwd)) {
            *userID = query.value ("uid").toInt ();
            if (!ui->nameLineEdit->text ().compare ("admin"))
                done(MoSignInDialog::Admin);
            else done (MoSignInDialog::Success);
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

void MoSignInDialog::clickConnect()
{
    bool hadInput;
    QString str = QInputDialog::getText (nullptr, "MySQL登录", "请输入root密码", QLineEdit::Password, "", &hadInput);
    if (hadInput) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "momoword");
        db.setHostName("localhost");
        db.setDatabaseName("momo_word");
        db.setUserName("root");
        db.setPassword(str);
        if (!db.open()) {
            qDebug() << "fail";
        }
        else {
            ui->loginBtn->setEnabled (true);
            ui->signupBtn->setEnabled (true);
        }
    }
}
