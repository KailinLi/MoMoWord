#ifndef MOSEARCHDIALOG_H
#define MOSEARCHDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>

namespace Ui {
class MoSearchDialog;
}

class MoSearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoSearchDialog(QWidget *parent = 0);
    ~MoSearchDialog();

public:
    QToolButton *backBtn;

private:
    Ui::MoSearchDialog *ui;
};

#endif // MOSEARCHDIALOG_H
