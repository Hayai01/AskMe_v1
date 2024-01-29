#ifndef RESULTADOSFORM_H
#define RESULTADOSFORM_H

#include <QWidget>
#include <QMessageBox>


#include <cuestionario.h>

namespace Ui {
class ResultadosForm;
}

class ResultadosForm : public QWidget
{
    Q_OBJECT

public:
    explicit ResultadosForm(QWidget *parent = nullptr);
    ~ResultadosForm();
    void setDatos(Cuestionario *cuestionario);

private slots:
    void on_btnCerrar_released();

private:
    Ui::ResultadosForm *ui;

    Cuestionario *m_cuestionario;

    void cargarDatos();
};

#endif // RESULTADOSFORM_H
