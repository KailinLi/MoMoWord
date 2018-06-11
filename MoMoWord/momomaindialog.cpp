#include "momomaindialog.h"
#include "ui_momomaindialog.h"

MoMoMainDialog::MoMoMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoMoMainDialog)
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget (&reciteDialog);
    ui->stackedWidget->addWidget (&searchDialog);
    ui->stackedWidget->addWidget (&bookDialog);
    ui->stackedWidget->addWidget (&statisticDialog);
    ui->stackedWidget->addWidget (&personalDialog);
    connect (reciteDialog.searchBtn, &QToolButton::clicked, this, &MoMoMainDialog::pushToSearch);
    connect (reciteDialog.bookBtn, &QToolButton::clicked, this, &MoMoMainDialog::pushToBook);
    connect (reciteDialog.statisticBtn, &QToolButton::clicked, this, &MoMoMainDialog::pushToStatistic);
    connect (reciteDialog.personalBtn, &QToolButton::clicked, this, &MoMoMainDialog::pushToPersonal);
    connect (searchDialog.backBtn, &QToolButton::clicked, this, &MoMoMainDialog::popBack);
    connect (bookDialog.backBtn, &QToolButton::clicked, this, &MoMoMainDialog::popBack);
    connect (statisticDialog.backBtn, &QToolButton::clicked, this, &MoMoMainDialog::popBack);
    connect (personalDialog.backBtn, &QToolButton::clicked, this, &MoMoMainDialog::popBack);
}

MoMoMainDialog::~MoMoMainDialog()
{
    delete ui;
}

void MoMoMainDialog::pushToSearch()
{
    ui->stackedWidget->setCurrentIndex (1);
}

void MoMoMainDialog::pushToBook()
{
    ui->stackedWidget->setCurrentIndex (2);
}

void MoMoMainDialog::pushToStatistic()
{
    ui->stackedWidget->setCurrentIndex (3);
}

void MoMoMainDialog::pushToPersonal()
{
    ui->stackedWidget->setCurrentIndex (4);
}

void MoMoMainDialog::popBack()
{
    ui->stackedWidget->setCurrentIndex (0);
}
