#include "momomaindialog.h"
#include "ui_momomaindialog.h"

MoMoMainDialog::MoMoMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoMoMainDialog)
{
    ui->setupUi(this);
}

MoMoMainDialog::~MoMoMainDialog()
{
    delete ui;
}
