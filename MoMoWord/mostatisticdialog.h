#ifndef MOSTATISTICDIALOG_H
#define MOSTATISTICDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>

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
    QToolButton *backBtn;

private:
    Ui::MoStatisticDialog *ui;
};

#endif // MOSTATISTICDIALOG_H
