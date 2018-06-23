#include "momomaindialog.h"
#include "ui_momomaindialog.h"

MoMoMainDialog::MoMoMainDialog(QWidget *parent) :
    QDialog(parent),
    haveDraw(false),
    ui(new Ui::MoMoMainDialog)
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget (&reciteDialog);
    ui->stackedWidget->addWidget (&searchDialog);
    ui->stackedWidget->addWidget (&bookDialog);
    ui->stackedWidget->addWidget (&statisticDialog);
    ui->stackedWidget->addWidget (&personalDialog);
    connect (reciteDialog.searchBtn, &QToolButton::clicked, [this](){ui->stackedWidget->setCurrentIndex (1);});
    connect (reciteDialog.bookBtn, &QToolButton::clicked, [this](){ui->stackedWidget->setCurrentIndex (2);});
    connect (reciteDialog.statisticBtn, &QToolButton::clicked, [this](){
        if (!haveDraw) {
            statisticDialog.drawDaily ();
            statisticDialog.drawSum ();
            haveDraw = true;
        }
        ui->stackedWidget->setCurrentIndex (3);
    });
    connect (reciteDialog.personalBtn, &QToolButton::clicked, [this](){personalDialog.loadData (); ui->stackedWidget->setCurrentIndex (4);});
    connect (searchDialog.backBtn, &QToolButton::clicked, this, &MoMoMainDialog::popBack);
    connect (bookDialog.backBtn, &QToolButton::clicked, this, &MoMoMainDialog::popBack);
    connect (statisticDialog.backBtn, &QToolButton::clicked, this, &MoMoMainDialog::popBack);
    connect (personalDialog.backBtn, &QToolButton::clicked, this, &MoMoMainDialog::popBack);
}

MoMoMainDialog::~MoMoMainDialog()
{
    delete ui;
}

void MoMoMainDialog::setUserID()
{
    reciteDialog.userID = userID;
    searchDialog.userID = userID;
    bookDialog.userID = userID;
    statisticDialog.userID = userID;
    personalDialog.userID = userID;
    reciteDialog.initRecite ();
    personalDialog.loadData ();
//    statisticDialog.drawDaily ();
//    statisticDialog.drawSum ();
    searchDialog.loadHistory ();
    bookDialog.addToComboBox ();
    bookDialog.refreshList ();
//    searchDialog.ifFilter = true;
}

void MoMoMainDialog::popBack()
{
    ui->stackedWidget->setCurrentIndex (0);
    reciteDialog.initRecite ();
}
