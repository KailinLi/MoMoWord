#include "momomaindialog.h"
#include "mosignindialog.h"
#include "mosignupdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "momoword");
    db.setHostName("localhost");
    db.setDatabaseName("momo_word");
    db.setUserName("root");
    db.setPassword("e,271828");
    if (!db.open()) {
        return -1;
    }
    QApplication a(argc, argv);
    MoMoMainDialog w;
    MoSignInDialog *singIn = new MoSignInDialog(nullptr, &w.userID);
    switch (static_cast<MoSignInDialog::ReturnType>(singIn->exec())) {
    case MoSignInDialog::Success:
        singIn->~MoSignInDialog ();
        w.show();
        return a.exec ();
        break;
    case MoSignInDialog::SignUp: {
        MoSignUpDialog *signUp = new MoSignUpDialog(nullptr, &w.userID);
        if (signUp->exec () == QDialog::Accepted) {
            signUp->~MoSignUpDialog ();
            w.show ();
            return a.exec ();
        }
        else {
            signUp->~MoSignUpDialog ();
            return 0;
        }
        break;
    }
    default:
        return 0;
        break;
    }
}
