#ifndef MOMOMAINDIALOG_H
#define MOMOMAINDIALOG_H

#include <QDialog>

namespace Ui {
class MoMoMainDialog;
}

class MoMoMainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoMoMainDialog(QWidget *parent = 0);
    ~MoMoMainDialog();

private:
    Ui::MoMoMainDialog *ui;
};

#endif // MOMOMAINDIALOG_H
