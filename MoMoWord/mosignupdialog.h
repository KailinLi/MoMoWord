#ifndef MOSIGNUPDIALOG_H
#define MOSIGNUPDIALOG_H

#include <QDialog>

namespace Ui {
class MoSignUpDialog;
}

class MoSignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoSignUpDialog(QWidget *parent = 0, int *userID = nullptr);
    ~MoSignUpDialog();

private:
    int *userID;

private:
    Ui::MoSignUpDialog *ui;
};

#endif // MOSIGNUPDIALOG_H
