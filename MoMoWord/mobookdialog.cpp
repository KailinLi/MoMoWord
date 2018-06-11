#include "mobookdialog.h"
#include "ui_mobookdialog.h"

MoBookDialog::MoBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoBookDialog)
{
    ui->setupUi(this);
    backBtn = ui->backBtn;
}

MoBookDialog::~MoBookDialog()
{
    delete ui;
}
