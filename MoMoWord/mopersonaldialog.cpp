#include "mopersonaldialog.h"
#include "ui_mopersonaldialog.h"

MoPersonalDialog::MoPersonalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoPersonalDialog)
{
    ui->setupUi(this);
    backBtn = ui->backBtn;
}

MoPersonalDialog::~MoPersonalDialog()
{
    delete ui;
}
