#include "mopersonaldialog.h"
#include "ui_mopersonaldialog.h"

MoPersonalDialog::MoPersonalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoPersonalDialog)
{
    ui->setupUi(this);
    backBtn = ui->backBtn;
    connect (ui->maleCheckBox, &QCheckBox::clicked, [=](){
        if (ui->maleCheckBox->isChecked ()) ui->femaleCheckBox->setCheckable (false);
        else ui->femaleCheckBox->setCheckable (true);
    });
    connect (ui->femaleCheckBox, &QCheckBox::clicked, [=](){
        if (ui->femaleCheckBox->isChecked ()) ui->maleCheckBox->setCheckable (false);
        else ui->maleCheckBox->setCheckable (true);
    });
    connect (ui->CECheckBox, &QCheckBox::clicked, [=](){
        if (ui->CECheckBox->isChecked ()) ui->ECCheckBox->setCheckable (false);
        else ui->ECCheckBox->setCheckable (true);
    });
    connect (ui->ECCheckBox, &QCheckBox::clicked, [=](){
        if (ui->ECCheckBox->isChecked ()) ui->CECheckBox->setCheckable (false);
        else ui->CECheckBox->setCheckable (true);
    });
}

MoPersonalDialog::~MoPersonalDialog()
{
    delete ui;
}

void MoPersonalDialog::loadData()
{
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare("select uid, uname, sex, daily_plan, english_or_chinese from user where uid = :uid");
    query.bindValue(":uid", userID);
    query.exec();
    if (query.next()) {
        ui->userNameLabel->setText (query.value ("uname").toString ());
        ui->userID->setText (query.value ("uid").toString ());
        if (query.value ("sex").toBool ())
            ui->maleCheckBox->setChecked (true);
        else ui->femaleCheckBox->setChecked (true);
        if (query.value ("english_or_chinese").toBool ())
            ui->ECCheckBox->setChecked (true);
        else ui->CECheckBox->setChecked (true);
        ui->planSpinBox->setValue (query.value ("daily_plan").toInt ());
    }
}
