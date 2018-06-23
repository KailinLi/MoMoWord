#include "moadmindialog.h"
#include "ui_moadmindialog.h"
#include <QDebug>

MoAdminDialog::MoAdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoAdminDialog)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    QPixmap pic("://images/logo_min.png");
    ui->logoLabel->setPixmap(pic.scaledToHeight (50));
    model = new QSqlTableModel(this, QSqlDatabase::database("momoword"));
    model->setTable("payment_list");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("uname"));
    model->setHeaderData(1, Qt::Horizontal, tr("income"));
    model->setHeaderData(2, Qt::Horizontal, tr("date"));


    ui->tableView->setModel(model);
//    this->setStyleSheet ("background-color: rgb(255, 255, 255)");
    connect (ui->refreshBtn, &QToolButton::clicked, this, &MoAdminDialog::refresh);
    connect (timer, &QTimer::timeout, this, &MoAdminDialog::refresh);

    ui->tableView->setColumnWidth (0, 70);
    ui->tableView->setColumnWidth (1, 70);
    ui->tableView->setColumnWidth (2, 200);
    loadUserCnt ();

    timer->start (1500);

}

MoAdminDialog::~MoAdminDialog()
{
    delete ui;
}

void MoAdminDialog::refresh()
{
    model->select ();
    loadUserCnt ();
    //    ui->tableView->setModel (model);
}

void MoAdminDialog::loadUserCnt()
{
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare ("select count(*) cnt from user");
    query.exec ();
    query.next ();
    ui->countLabel->setText (tr("总注册用户 %1 人").arg (query.value ("cnt").toInt ()));
    ui->countLabel->repaint ();
}
