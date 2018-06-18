#ifndef MOMOMAINDIALOG_H
#define MOMOMAINDIALOG_H

#include <QDialog>
#include "morecitedialog.h"
#include "mosearchdialog.h"
#include "mobookdialog.h"
#include "mostatisticdialog.h"
#include "mopersonaldialog.h"

namespace Ui {
class MoMoMainDialog;
}

class MoMoMainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoMoMainDialog(QWidget *parent = 0);
    ~MoMoMainDialog();

public:
    int userID;
public:
    void setUserID();

private:
    MoReciteDialog reciteDialog;
    MoSearchDialog searchDialog;
    MoBookDialog bookDialog;
    MoStatisticDialog statisticDialog;
    MoPersonalDialog personalDialog;
private:
    void popBack();

private:
    Ui::MoMoMainDialog *ui;
};

#endif // MOMOMAINDIALOG_H
