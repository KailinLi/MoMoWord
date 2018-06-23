#ifndef MOADMINDIALOG_H
#define MOADMINDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QTimer>

namespace Ui {
class MoAdminDialog;
}

class MoAdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoAdminDialog(QWidget *parent = 0);
    ~MoAdminDialog();

private:
    QSqlTableModel * model;
    QTimer *timer;

private:
    void refresh();
    void loadUserCnt();

private:
    Ui::MoAdminDialog *ui;
};

#endif // MOADMINDIALOG_H
