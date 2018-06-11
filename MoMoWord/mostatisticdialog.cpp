#include "mostatisticdialog.h"
#include "ui_mostatisticdialog.h"

MoStatisticDialog::MoStatisticDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoStatisticDialog)
{
    ui->setupUi(this);
    backBtn = ui->backBtn;
}

MoStatisticDialog::~MoStatisticDialog()
{
    delete ui;
}
