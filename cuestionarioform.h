#ifndef CUESTIONARIOFORM_H
#define CUESTIONARIOFORM_H

#include <QWidget>
#include <QList>

#include <preguntaform.h>

#include <asignatura.h>
#include <cuestionario.h>

namespace Ui {
class CuestionarioForm;
}

class CuestionarioForm : public QWidget
{
    Q_OBJECT

public:
    explicit CuestionarioForm(QWidget *parent = nullptr);
    ~CuestionarioForm();

    void cargarAsignaturas();
    void setAsignaturas(QList<Asignatura *> &newAsignaturas);

signals:
    void cuestionarioCreado(Cuestionario *cuestionario);
private slots:
    void on_cmbAsignatura_currentIndexChanged(int index);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CuestionarioForm *ui;
    QList<Asignatura*> *m_asignaturas;
};

#endif // CUESTIONARIOFORM_H
