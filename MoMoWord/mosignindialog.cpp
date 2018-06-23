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
//    this->setStyleSheet ("background-color: rgb(255, 255, 255)");
}

MoSignInDialog::~MoSignInDialog()
{
    delete ui;
}

void MoSignInDialog::clickSignIn()
{
    if (ui->nameLineEdit->text ().isEmpty () || ui->passwdLineEdit->text ().isEmpty ()) {
        shakeWindow ();
        ui->nameLineEdit->clear ();
        ui->passwdLineEdit->clear ();
        ui->nameLineEdit->setPlaceholderText (tr("信息不完整"));
    }
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
            shakeWindow ();
            ui->nameLineEdit->clear ();
            ui->passwdLineEdit->clear ();
            ui->nameLineEdit->setPlaceholderText (tr("用户名或密码错误"));
        }
    }
    else {
        shakeWindow ();
        ui->nameLineEdit->clear ();
        ui->passwdLineEdit->clear ();
        ui->nameLineEdit->setPlaceholderText (tr("用户名或密码错误"));
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

void MoSignInDialog::shakeWindow()
{
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "pos");
    pAnimation->setDuration(500);
    pAnimation->setLoopCount(2);
    pAnimation->setKeyValueAt(0, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->setKeyValueAt(0.1, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.2, QPoint(geometry().x() - 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.3, QPoint(geometry().x() + 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.4, QPoint(geometry().x() - 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.5, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.6, QPoint(geometry().x() - 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.7, QPoint(geometry().x() + 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.8, QPoint(geometry().x() - 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.9, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(1, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}
