#ifndef MORECITEDIALOG_H
#define MORECITEDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QQueue>
#include <QSqlQuery>
//#include <qapplication.h>
//#include <QtConcurrent>
#include "wordentry.h"

namespace Ui {
class MoReciteDialog;
}

class MoReciteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoReciteDialog(QWidget *parent = 0);
    ~MoReciteDialog();

private:
    enum State : int {
        Unhide = 1,
        Hide = 2
    };

public:
    QToolButton *searchBtn;
    QToolButton *bookBtn;
    QToolButton *statisticBtn;
    QToolButton *personalBtn;
    int userID;

private:
    QQueue<WordEntry*> reciteQueue;
    State state;
    bool spell;

private:
    void loadWord();

    void clickMiddleBtn();
    void clickLeftBtn();
    void clickRightBtn();

    void repaintAll();
    void showPunch();

public:
    void initRecite();

private:
    Ui::MoReciteDialog *ui;
};

#endif // MORECITEDIALOG_H
