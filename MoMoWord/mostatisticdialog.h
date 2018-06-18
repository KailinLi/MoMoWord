#ifndef MOSTATISTICDIALOG_H
#define MOSTATISTICDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>

namespace Ui {
class MoStatisticDialog;
}

class MoStatisticDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoStatisticDialog(QWidget *parent = 0);
    ~MoStatisticDialog();

public:
    void drawDaily();
    void drawSum();

public:
    QToolButton *backBtn;
    int userID;

private:
    Ui::MoStatisticDialog *ui;
};

#endif // MOSTATISTICDIALOG_H
