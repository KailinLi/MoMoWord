#include "morecitedialog.h"
#include "ui_morecitedialog.h"
#include <QDebug>

MoReciteDialog::MoReciteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoReciteDialog)
{
    ui->setupUi(this);
    searchBtn = ui->searchBtn;
    bookBtn = ui->bookBtn;
    statisticBtn = ui->statisticBtn;
    personalBtn = ui->personalBtn;
    ui->wordLineEdit->hide ();
    connect (ui->middleBtn, &QPushButton::clicked, this, &MoReciteDialog::clickMiddleBtn);
    connect (ui->leftBtn, &QPushButton::clicked, this, &MoReciteDialog::clickLeftBtn);
    connect (ui->rightBtn, &QPushButton::clicked, this, &MoReciteDialog::clickRightBtn);
    QPixmap pic("://images/logo_minimum.png");
    ui->logoLabel->setPixmap(pic);
    connect (ui->wordLineEdit, &QLineEdit::returnPressed, this, &MoReciteDialog::clickMiddleBtn);
//    this->setStyleSheet ("background-color: rgb(255, 255, 255)");
}

MoReciteDialog::~MoReciteDialog()
{
    delete ui;
}

void MoReciteDialog::loadWord()
{
    //TODO
    if (reciteQueue.empty ()) {
        if (checkFinishDaily ()) showPunch ();
        return;
    }
    if (spell) {
        ui->wordLabel->setText (reciteQueue.front ()->word);
        ui->phonogramLabel->setText (reciteQueue.front ()->phonogram);
        ui->translationLabel->setText (tr("请把英文发音和中文解释说出口"));
        ui->leftBtn->hide ();
        ui->rightBtn->hide ();
        ui->wordLineEdit->hide ();
        ui->middleBtn->setStyleSheet ("background-color: rgb(0, 190, 159, 60%)");
        ui->middleBtn->show ();
        ui->middleBtn->setText (tr("显示"));
        state = State::Hide;
        repaintAll ();
    }
    else {
        QString showWord = reciteQueue.front ()->word.left (1);
        for (int i = 1; i < reciteQueue.front ()->word.size (); ++i) showWord.append ('_');
        ui->wordLabel->setText (showWord);
        ui->phonogramLabel->setText (reciteQueue.front ()->phonogram);
        ui->translationLabel->setText (reciteQueue.front ()->translation);
        ui->leftBtn->hide ();
        ui->rightBtn->hide ();
        ui->wordLineEdit->show ();
        ui->middleBtn->show();
        ui->middleBtn->setStyleSheet ("background-color: rgb(0, 190, 159, 60%)");
        ui->middleBtn->setText (tr("显示"));
        ui->wordLineEdit->setEnabled (true);
        ui->wordLineEdit->clear ();
        state = State::Hide;
        repaintAll ();
    }
    //    ui->translationLabel->setText (reciteQueue.front ()->translation);
}

void MoReciteDialog::clickMiddleBtn()
{
    if (state == State::Hide) {
        if (spell) {
            ui->leftBtn->setStyleSheet ("background-color: rgb(0, 190, 159, 60%)");
            ui->leftBtn->setText (tr("认识"));
            ui->middleBtn->setStyleSheet ("background-color: rgb(250, 170, 20, 60%)");
            ui->middleBtn->setText (reciteQueue.front ()->is_new ? tr("不熟悉") : tr("模糊"));
            ui->rightBtn->setStyleSheet ("background-color: rgb(255, 52, 106, 60%)");
            ui->rightBtn->setText (reciteQueue.front ()->is_new ? tr("不认识") : tr("忘记"));
            ui->leftBtn->show ();
            ui->rightBtn->show ();
            ui->translationLabel->setText (reciteQueue.front ()->translation);
            state = State::Unhide;
            repaintAll ();
        }
        else {
//            state = State::Unhide;
            ui->middleBtn->setStyleSheet ("background-color: rgb(0, 190, 159, 60%)");
            ui->middleBtn->setText (tr("确定"));
            ui->wordLineEdit->setEnabled (false);
            if (checkSpell ()) {
                ui->wordLabel->setText ("<font color='Green'>" + reciteQueue.front ()->word + "</font>");
//                clickLeftBtn ();
//                ui->wordLabel->setText ("<font color='Green'>" + reciteQueue.front ()->word + "</font>");
            }
            else {
//                clickMiddleBtn ();
                ui->wordLabel->setText ("<font color='Red'>" + reciteQueue.front ()->word + "</font>");
            }
            state = State::Hold;
            repaintAll ();
        }
    }
    else if (state == State::Unhide) {
        if (reciteQueue.front ()->first_time) {
            //TODO
            QSqlQuery query(QSqlDatabase::database("momoword"));
            query.prepare("update plan set date = \
                          TIMESTAMPADD(HOUR, 0, TIMESTAMPADD(DAY, 2, CURDATE())), is_new = false where wid = :wid and uid = :uid");
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
        reciteQueue.front ()->is_new = false;
        reciteQueue.push_back (reciteQueue.front ());
        reciteQueue.pop_front ();
        loadWord ();
    }
    else if (state == State::Hold) {
        state = State::Unhide;
        if (checkSpell ())
            clickLeftBtn ();
        else clickMiddleBtn ();
    }
}

void MoReciteDialog::clickLeftBtn()
{
    if (state == State::Unhide) {
        if (reciteQueue.front ()->first_time) {
            //TODO
            QSqlQuery query(QSqlDatabase::database("momoword"));
            query.prepare("update plan set date = \
                          TIMESTAMPADD(HOUR, 0, TIMESTAMPADD(DAY, 3, CURDATE())), is_new = false where wid = :wid and uid = :uid");
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
        if (!--reciteQueue.front ()->count)
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
                          TIMESTAMPADD(HOUR, 0, TIMESTAMPADD(DAY, 1, CURDATE())), is_new = false where wid = :wid and uid = :uid");
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
        reciteQueue.front ()->is_new = false;
        reciteQueue.front ()->count += 1;
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
    ui->wordLineEdit->repaint ();
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
    ui->wordLineEdit->hide ();
    ui->leftBtn->hide ();
    ui->middleBtn->hide ();
    ui->rightBtn->hide ();
    repaintAll ();
}

bool MoReciteDialog::checkSpell()
{
    return !ui->wordLineEdit->text ().compare (reciteQueue.front ()->word);
}

bool MoReciteDialog::checkFinishDaily()
{
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare("select count(*) from plan where DATE(first_time) = CURDATE() and uid = :uid");
    query.bindValue (":uid", userID);
    query.exec();
    query.next ();
    qDebug() << query.value (0).toInt ();
    if (query.value (0).toInt () < planCnt) {
        ui->wordLabel->setText (tr("今天任务未完成"));
        ui->translationLabel->setText (tr("快去选词吧"));
        ui->phonogramLabel->setText (tr(""));
        ui->wordLineEdit->hide ();
        ui->middleBtn->hide ();
        ui->leftBtn->hide ();
        ui->rightBtn->hide ();
        repaintAll ();
        return false;
    }
    return true;
}


void MoReciteDialog::initRecite()
{
    while (!reciteQueue.empty ()) {
        if (!--reciteQueue.front ()->count)
            delete reciteQueue.front ();
        reciteQueue.pop_front ();
    }
    QSqlQuery query(QSqlDatabase::database("momoword"));
    query.prepare("select w.wid, word, phonogram, translation, is_new from plan \
                  inner join word w on plan.wid = w.wid where DATE(date) = current_date() or is_new = 1 and uid = :uid");
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
    //TODO
    query.clear ();
    query.prepare ("select english_or_chinese, daily_plan from user where uid = :uid");
    query.bindValue (":uid", userID);
    query.exec ();
    if (query.next ()) {
        spell = query.value ("english_or_chinese").toBool ();
        planCnt = query.value ("daily_plan").toInt ();
    }
    loadWord ();
}
