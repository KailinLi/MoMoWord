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
    connect (ui->middleBtn, &QPushButton::clicked, this, &MoReciteDialog::clickMiddleBtn);
    connect (ui->leftBtn, &QPushButton::clicked, this, &MoReciteDialog::clickLeftBtn);
    connect (ui->rightBtn, &QPushButton::clicked, this, &MoReciteDialog::clickRightBtn);
}

MoReciteDialog::~MoReciteDialog()
{
    delete ui;
}

void MoReciteDialog::loadWord()
{
    //TODO
    if (reciteQueue.empty ()) {
        showPunch ();
        return;
    }
    ui->wordLabel->setText (reciteQueue.front ()->word);
    ui->phonogramLabel->setText (reciteQueue.front ()->phonogram);
    ui->translationLabel->setText (tr("请把英文发音和中文解释说出口"));
    ui->leftBtn->hide ();
    ui->rightBtn->hide ();
    ui->middleBtn->setText (tr("显示"));
    state = State::Hide;
    repaintAll ();
    //    ui->translationLabel->setText (reciteQueue.front ()->translation);
}

void MoReciteDialog::clickMiddleBtn()
{
    if (state == State::Hide) {
        ui->leftBtn->setText (tr("认识"));
        ui->middleBtn->setText (reciteQueue.front ()->is_new ? tr("不熟悉") : tr("模糊"));
        ui->rightBtn->setText (reciteQueue.front ()->is_new ? tr("不认识") : tr("忘记"));
        ui->leftBtn->show ();
        ui->rightBtn->show ();
        ui->translationLabel->setText (reciteQueue.front ()->translation);
        state = State::Unhide;
        repaintAll ();
    }
    else if (state == State::Unhide) {
        if (reciteQueue.front ()->first_time) {
            //TODO
            QSqlQuery query(QSqlDatabase::database("momoword"));
            query.prepare("update plan set date = \
                          TIMESTAMPADD(HOUR, 0, TIMESTAMPADD(DAY, 2, CURDATE())) where wid = :wid and uid = :uid");
            query.bindValue (":uid", userID);
            query.bindValue (":wid", reciteQueue.front ()->wid);
            if (!query.exec()) {
                //TODO
            }
        }
        QSqlQuery query(QSqlDatabase::database("momoword"));
        query.prepare("insert into memory(uid, wid, proficiency) VALUE (:uid, :wid, :proficiency)");
        query.bindValue (":uid", userID);
        query.bindValue (":wid", reciteQueue.front ()->wid);
        query.bindValue (":proficiency", 2);
        if (!query.exec()) {
            //TODO
        }
//        delete reciteQueue.front ();
        reciteQueue.front ()->first_time = false;
        reciteQueue.push_back (reciteQueue.front ());
        reciteQueue.pop_front ();
        loadWord ();
    }
}

void MoReciteDialog::clickLeftBtn()
{
    if (state == State::Unhide) {
        if (reciteQueue.front ()->first_time) {
            //TODO
            QSqlQuery query(QSqlDatabase::database("momoword"));
            query.prepare("update plan set date = \
                          TIMESTAMPADD(HOUR, 0, TIMESTAMPADD(DAY, 3, CURDATE())) where wid = :wid and uid = :uid");
            query.bindValue (":uid", userID);
            query.bindValue (":wid", reciteQueue.front ()->wid);
            if (!query.exec()) {
                //TODO
            }
        }
        QSqlQuery query(QSqlDatabase::database("momoword"));
        query.prepare("insert into memory(uid, wid, proficiency) VALUE (:uid, :wid, :proficiency)");
        query.bindValue (":uid", userID);
        query.bindValue (":wid", reciteQueue.front ()->wid);
        query.bindValue (":proficiency", 1);
        if (!query.exec()) {
            //TODO
        }
        delete reciteQueue.front ();
        reciteQueue.pop_front ();
        loadWord ();
    }
}

void MoReciteDialog::clickRightBtn()
{
    if (state == State::Unhide) {
        if (reciteQueue.front ()->first_time) {
            //TODO
            QSqlQuery query(QSqlDatabase::database("momoword"));
            query.prepare("update plan set date = \
                          TIMESTAMPADD(HOUR, 0, TIMESTAMPADD(DAY, 1, CURDATE())) where wid = :wid and uid = :uid");
            query.bindValue (":uid", userID);
            query.bindValue (":wid", reciteQueue.front ()->wid);
            if (!query.exec()) {
                //TODO
            }
        }
        QSqlQuery query(QSqlDatabase::database("momoword"));
        query.prepare("insert into memory(uid, wid, proficiency) VALUE (:uid, :wid, :proficiency)");
        query.bindValue (":uid", userID);
        query.bindValue (":wid", reciteQueue.front ()->wid);
        query.bindValue (":proficiency", 3);
        if (!query.exec()) {
            //TODO
        }
//        delete reciteQueue.front ();
        reciteQueue.front ()->first_time = false;
        reciteQueue.push_back (reciteQueue.front ());
        reciteQueue.push_back (reciteQueue.front ());
        reciteQueue.pop_front ();
        loadWord ();
    }
}

void MoReciteDialog::repaintAll()
{
//    qApp->processEvents();
//    QApplication.processEvents()
    ui->leftBtn->repaint ();
    ui->middleBtn->repaint ();
    ui->rightBtn->repaint ();
    ui->wordLabel->repaint ();
    ui->phonogramLabel->repaint ();
    ui->translationLabel->repaint ();
}

void MoReciteDialog::showPunch()
{
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare("insert into punch(uid) value (:uid)");
    query.bindValue (":uid", userID);
    if (!query.exec()) {
        //TODO
    }
    query.clear ();
    query.prepare("select count(*) cnt from punch where uid = :uid");
    query.bindValue (":uid", userID);
    if (!query.exec()) {
        //TODO
    }
    query.next ();
    ui->wordLabel->setText (tr("打卡成功"));
    ui->phonogramLabel->setText (tr("今天的任务完成了"));
    ui->translationLabel->setText (tr("累计打卡 %1 天").arg (query.value (0).toInt ()));
    ui->leftBtn->hide ();
    ui->middleBtn->hide ();
    ui->rightBtn->hide ();
    repaintAll ();
}


void MoReciteDialog::initRecite()
{
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare("select w.wid, word, phonogram, translation, is_new from plan \
                  inner join word w on plan.wid = w.wid where DATE(date) = current_date() and uid = :uid");
    query.bindValue (":uid", userID);
    if (!query.exec()) {
        //TODO
    }
    while (query.next()) {
        WordEntry *entry = new WordEntry(query.value ("wid").toInt (),
                                         query.value ("word").toString (),
                                         query.value ("phonogram").toString (),
                                         query.value ("translation").toString (),
                                         query.value ("is_new").toBool ());
        reciteQueue.push_back (entry);
    }
    loadWord ();
}
