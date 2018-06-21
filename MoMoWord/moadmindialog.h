#ifndef MOADMINDIALOG_H
#define MOADMINDIALOG_H

#include <QDialog>
#include <QSqlTableModel>

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

private:
    void refresh();

private:
    Ui::MoAdminDialog *ui;
};

#endif // MOADMINDIALOG_H
