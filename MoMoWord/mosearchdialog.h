#ifndef MOSEARCHDIALOG_H
#define MOSEARCHDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QCompleter>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>

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
    void loadHistory();

private:
    void clickSearch();


public:
    QToolButton *backBtn;
    int userID;
//    bool ifFilter;

private:
    Ui::MoSearchDialog *ui;
};

#endif // MOSEARCHDIALOG_H
