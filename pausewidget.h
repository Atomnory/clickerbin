#ifndef PAUSEWIDGET_H
#define PAUSEWIDGET_H

#include <QWidget>

namespace Ui {
class pausewidget;
}

class pausewidget : public QWidget
{
    Q_OBJECT

public:
    explicit pausewidget(QWidget *parent = nullptr);
    ~pausewidget();

    void setAbsence(int, qint64);

private slots:
    void on_pushButton_clicked();

private:
    Ui::pausewidget *ui;

    int receivedCash;
    int receivedTime;
};

#endif // PAUSEWIDGET_H
