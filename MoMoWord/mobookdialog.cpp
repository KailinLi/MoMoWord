#include "mobookdialog.h"
#include "ui_mobookdialog.h"
#include <QStack>
#include <QDebug>

MoBookDialog::MoBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoBookDialog)
{
    ui->setupUi(this);
    backBtn = ui->backBtn;
    ui->wordListView->setModel( &model );
    addToComboBox ();
//    refreshList ();
    connect (ui->bookComboBox, &QComboBox::currentTextChanged, [this](QString s){
        qDebug() << s;
        refreshList ();
    });
    connect (ui->loadBtn, &QPushButton::clicked, [this](){learnNewWords ();});
    QPixmap pic("://images/logo_minimum.png");
    ui->logoLabel->setPixmap(pic);
}

MoBookDialog::~MoBookDialog()
{
    delete ui;
}

void MoBookDialog::addToComboBox()
{
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare("select bname from book");
    query.exec();
    while (query.next()) {
        QString item = query.value ("bname").toString ();
        ui->bookComboBox->addItem (item);
    }
}

void MoBookDialog::refreshList()
{
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare("select bid from book where bname = :bname");
    query.bindValue (":bname", ui->bookComboBox->currentText ());
    query.exec();
    query.next();
    int bid = query.value ("bid").toInt ();
    query.clear ();
    query.prepare ("select wb.wid, word from word inner join \
                   word_book wb on word.wid = wb.wid where wb.bid = :bid and \
            wb.wid not in ( select wid from plan where uid = :uid ) order by wb.wid");
    query.bindValue (":bid", bid);
    query.bindValue (":uid", userID);
    query.exec ();
    model.clear ();
    widList.clear ();
    while (query.next ()) {
        QStandardItem *item = new QStandardItem();
        QList<QStandardItem*> list;
        item->setCheckable( true );
        item->setCheckState( Qt::Unchecked );
        item->setText (query.value ("word").toString ());
        list.append (item);
        model.appendRow (list);
        widList.append (query.value ("wid").toInt ());
    }
//    model->setItem ();
//    ui->wordListView->setModel( model );
}

void MoBookDialog::learnNewWords()
{
    QStack<int> stack;
    for (int i = 0; i < model.rowCount (); ++i) {
        QStandardItem *item = model.item (i);
        if (item->checkState () == Qt::Checked) {
            qDebug() << item->text ();
            stack.push (i);
        }
    }
    while (!stack.empty ()) {
        int index = stack.pop ();
        QSqlQuery query(QSqlDatabase::database("momoword"));
        query.prepare("insert into plan (uid, wid, is_new) values (:uid, :wid, 1)");
        query.bindValue (":uid", userID);
        query.bindValue (":wid", widList[index]);
//        qDebug() << widList[index];
        if (!query.exec()) {
            //TODO
            QMessageBox::warning (this, tr("请充值"), tr("学习单词数已达到上限\n充值可以使你更强"), QMessageBox::Ok);
            return;
        }
        model.removeRow (index);
        widList.removeAt (index);
    }
}
