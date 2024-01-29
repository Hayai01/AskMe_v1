#ifndef CREDITOSFORM_H
#define CREDITOSFORM_H

#include <QWidget>
#include <QUrl>
#include <QDesktopServices>

#include <QString>
#include <QMessageBox>

namespace Ui {
class CreditosForm;
}

class CreditosForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreditosForm(QWidget *parent = nullptr);
    ~CreditosForm();

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

private:
    Ui::CreditosForm *ui;
};

#endif // CREDITOSFORM_H
