#include "morecitedialog.h"
#include "ui_morecitedialog.h"

MoReciteDialog::MoReciteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoReciteDialog)
{
    ui->setupUi(this);
}

MoReciteDialog::~MoReciteDialog()
{
    delete ui;
}
