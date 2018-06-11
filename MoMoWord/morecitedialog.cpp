#include "morecitedialog.h"
#include "ui_morecitedialog.h"

MoReciteDialog::MoReciteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoReciteDialog)
{
    ui->setupUi(this);
    searchBtn = ui->searchBtn;
    bookBtn = ui->bookBtn;
    statisticBtn = ui->statisticBtn;
    personalBtn = ui->personalBtn;
}

MoReciteDialog::~MoReciteDialog()
{
    delete ui;
}
