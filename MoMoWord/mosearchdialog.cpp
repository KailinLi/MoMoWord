#include "mosearchdialog.h"
#include "ui_mosearchdialog.h"
#include <QDebug>

MoSearchDialog::MoSearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoSearchDialog)
{
    ui->setupUi(this);
    backBtn = ui->backBtn;

}

MoSearchDialog::~MoSearchDialog()
{
    delete ui;
}

void MoSearchDialog::loadHistory(const QString &s)
{
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare("select word from word inner join history h \
                  on word.wid = h.wid where uid = :uid and word like :pattern");
    query.bindValue (":uid", userID);
    query.bindValue (":pattern", s + "%");
    query.exec ();
    while (query.next ()) {
        ui->comboBox->addItem (query.value ("word").toString ());
    }
}
