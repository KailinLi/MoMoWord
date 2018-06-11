#ifndef MORECITEDIALOG_H
#define MORECITEDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>

namespace Ui {
class MoReciteDialog;
}

class MoReciteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoReciteDialog(QWidget *parent = 0);
    ~MoReciteDialog();

public:
    QToolButton *searchBtn;
    QToolButton *bookBtn;
    QToolButton *statisticBtn;
    QToolButton *personalBtn;

private:
    Ui::MoReciteDialog *ui;
};

#endif // MORECITEDIALOG_H
