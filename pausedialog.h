#ifndef PAUSEDIALOG_H
#define PAUSEDIALOG_H

#include <QDialog>

namespace Ui {
class PauseDialog;
}

class PauseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PauseDialog(QWidget *parent = nullptr);
    ~PauseDialog();

private:
    Ui::PauseDialog *ui;
};

#endif // PAUSEDIALOG_H
