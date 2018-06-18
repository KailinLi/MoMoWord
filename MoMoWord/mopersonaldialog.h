#ifndef MOPERSONALDIALOG_H
#define MOPERSONALDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>

namespace Ui {
class MoPersonalDialog;
}

class MoPersonalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoPersonalDialog(QWidget *parent = 0);
    ~MoPersonalDialog();

    void loadData();

private:

public:
    QToolButton *backBtn;
    int userID;

private:
    Ui::MoPersonalDialog *ui;
};

#endif // MOPERSONALDIALOG_H
