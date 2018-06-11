#ifndef MORECITEDIALOG_H
#define MORECITEDIALOG_H

#include <QDialog>

namespace Ui {
class MoReciteDialog;
}

class MoReciteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoReciteDialog(QWidget *parent = 0);
    ~MoReciteDialog();

private:
    Ui::MoReciteDialog *ui;
};

#endif // MORECITEDIALOG_H
