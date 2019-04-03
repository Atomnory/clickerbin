#include "pausewidget.h"
#include "ui_pausewidget.h"

pausewidget::pausewidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pausewidget)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::WindowModality::ApplicationModal);
    this->setWindowTitle("Pause");
    this->setAttribute(Qt::WA_DeleteOnClose, true);

}

pausewidget::~pausewidget()
{
    delete ui;
}

void pausewidget::setAbsence(int absCash, qint64 absTime)
{
    //receivedTime = static_cast<int>(absTime);

    ui->label_absence_cash->setText(QString::number(absCash));
    ui->label_absence_time->setText(QString::number(static_cast<int>(absTime)));

}

void pausewidget::on_pushButton_clicked()
{
    QWidget::close();
}
