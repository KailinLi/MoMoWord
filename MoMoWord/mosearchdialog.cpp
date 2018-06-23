#include "mosearchdialog.h"
#include "ui_mosearchdialog.h"
#include <QDebug>

MoSearchDialog::MoSearchDialog(QWidget *parent) :
    QDialog(parent),
//    ifFilter(false),
    ui(new Ui::MoSearchDialog)
{
    ui->setupUi(this);
    backBtn = ui->backBtn;
    connect (ui->searchBtn, &QPushButton::clicked, this, &MoSearchDialog::clickSearch);
    QPixmap pic("://images/logo_minimum.png");
    ui->logoLabel->setPixmap(pic);
//    this->setStyleSheet ("background-color: rgb(255, 255, 255)");
}

MoSearchDialog::~MoSearchDialog()
{
    delete ui;
}

void MoSearchDialog::loadHistory()
{
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare("select distinct word from word inner join history h \
                  on word.wid = h.wid where uid = :uid");
    query.bindValue (":uid", userID);
//    query.bindValue (":pattern", s + "%");
    query.exec ();
//    while (ui->comboBox->count ()) ui->comboBox->removeItem (0);
    while (query.next ()) {
        ui->comboBox->addItem (query.value ("word").toString ());
    }
}

void MoSearchDialog::clickSearch()
{
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare("select wid, word, phonogram, translation from word where word = :word");
    query.bindValue (":word", ui->comboBox->currentText ());
    query.exec ();
    if (query.next ()) {
        ui->comboBox->addItem (query.value ("word").toString ());
        int wid = query.value ("wid").toInt ();
        ui->wordLabel->setText (query.value ("word").toString ());
        ui->phonogramLabel->setText (query.value ("phonogram").toString ());
        ui->translationLabel->setText (query.value ("translation").toString ());
        ui->wordLabel->repaint ();
        ui->phonogramLabel->repaint ();
        ui->translationLabel->repaint ();
        query.clear ();
        query.prepare("insert into history(uid, wid) VALUE (:uid, :wid)");
        query.bindValue (":uid", userID);
        query.bindValue (":wid", wid);
        query.exec ();
    }
    else {
        ui->wordLabel->setText (tr("暂未收录"));
        ui->wordLabel->repaint ();
    }
}
