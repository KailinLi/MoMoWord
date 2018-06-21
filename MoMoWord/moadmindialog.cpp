#include "moadmindialog.h"
#include "ui_moadmindialog.h"

MoAdminDialog::MoAdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoAdminDialog)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this, QSqlDatabase::database("momoword"));
    model->setTable("payment_list");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("uname"));
    model->setHeaderData(1, Qt::Horizontal, tr("income"));
    model->setHeaderData(2, Qt::Horizontal, tr("date"));

    ui->tableView->setModel(model);

    connect (ui->refreshBtn, &QToolButton::clicked, this, &MoAdminDialog::refresh);
}

MoAdminDialog::~MoAdminDialog()
{
    delete ui;
}

void MoAdminDialog::refresh()
{
    model->select ();
//    ui->tableView->setModel (model);
}
