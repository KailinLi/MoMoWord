#include "mosearchdialog.h"
#include "ui_mosearchdialog.h"

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
