#ifndef MOBOOKDIALOG_H
#define MOBOOKDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>

namespace Ui {
class MoBookDialog;
}

class MoBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoBookDialog(QWidget *parent = 0);
    ~MoBookDialog();

public:
    QToolButton *backBtn;

private:
    Ui::MoBookDialog *ui;
};

#endif // MOBOOKDIALOG_H
