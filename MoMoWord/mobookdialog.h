#ifndef MOBOOKDIALOG_H
#define MOBOOKDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QList>

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
    int userID;

private:
    void addToComboBox();
    void refreshList();
    void learnNewWords();

private:
    QStandardItemModel model;
    QList<int> widList;

private:
    Ui::MoBookDialog *ui;
};

#endif // MOBOOKDIALOG_H
