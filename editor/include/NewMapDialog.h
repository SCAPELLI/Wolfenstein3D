#ifndef EDITOR_NEWMAPDIALOG_H
#define EDITOR_NEWMAPDIALOG_H


#include <QtWidgets/QDialog>

namespace Ui {
    class NewMapDialog;
}

class NewMapDialog : public QDialog {
    Q_OBJECT;

    private:
        Ui::NewMapDialog *ui;
        bool validState;

    public:
        NewMapDialog(QWidget *parent = 0);
        ~NewMapDialog();
        void connectEvents();
        void accept();
        void close();
        bool giveLenghtWidthIfHasAValidState(int *lenght, int *width);
};


#endif //EDITOR_NEWMAPDIALOG_H
