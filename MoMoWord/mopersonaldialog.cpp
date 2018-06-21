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
    connect (ui->saveBtn, &QPushButton::clicked, this, &MoPersonalDialog::updateInfo);
    connect (ui->buyBtn, &QPushButton::clicked, this, &MoPersonalDialog::buyMore);
    QPixmap pic("://images/logo_minimum.png");
    ui->logoLabel->setPixmap(pic);
}

MoPersonalDialog::~MoPersonalDialog()
{
    delete ui;
}

void MoPersonalDialog::loadData()
{
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare("select uid, uname, sex, daily_plan, english_or_chinese, word_limit from user where uid = :uid");
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
        ui->limitCntLabel->setText (QString::number (query.value ("word_limit").toInt ()));
        ui->limitCntLabel->repaint ();
    }
}

void MoPersonalDialog::updateInfo()
{
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare ("update user set sex = :sex, daily_plan = :daily_plan, \
                   english_or_chinese = :english_or_chines where uid = :uid");
    query.bindValue (":sex", ui->maleCheckBox->isChecked () ? 1 : 0);
    query.bindValue (":daily_plan", ui->planSpinBox->value ());
    query.bindValue (":english_or_chines", ui->ECCheckBox->isChecked () ? 1 : 0);
    query.bindValue (":uid", userID);
    if (!query.exec ()) {
        //TODO
    }
}

void MoPersonalDialog::buyMore()
{
    bool ok;
    int money = QInputDialog::getInt(this, tr("购买更多单词量"),
                                     tr("输入购买金额(1元=10单词)"), 5, 0, 1000, 1, &ok);
    if (ok) {
        QSqlQuery query(QSqlDatabase::database("momoword"));
        query.prepare ("insert into payment(uid, money) VALUE (:uid, :money)");
        query.bindValue (":uid", userID);
        query.bindValue (":money", money);
        query.exec ();
    }
    loadData ();
}
