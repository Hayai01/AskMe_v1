#include "cuestionarioform.h"
#include "ui_cuestionarioform.h"

CuestionarioForm::CuestionarioForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CuestionarioForm)
{
    ui->setupUi(this);
}

CuestionarioForm::~CuestionarioForm()
{
    delete ui;
}

void CuestionarioForm::cargarAsignaturas()
{
    ui->cmbAsignatura->clear();
    foreach(Asignatura *a, *m_asignaturas)
    {
        ui->cmbAsignatura->addItem(a->nombre());
    }
}

void CuestionarioForm::setAsignaturas(QList<Asignatura *> &newAsignaturas)
{
    m_asignaturas = &newAsignaturas;
}

void CuestionarioForm::on_cmbAsignatura_currentIndexChanged(int index)
{
    ui->cmbTema->clear();
    if (index >= 0 && index < m_asignaturas->size()){
        Asignatura *a = m_asignaturas->at(index);
        foreach(Tema *t, a->temas()){
            ui->cmbTema->addItem(t->nombre());
        }
    }
}

void CuestionarioForm::on_buttonBox_accepted()
{
    // Obtener los indices de los combos
    int indexAsignatura = ui->cmbAsignatura->currentIndex();
    int indexTema = ui->cmbTema->currentIndex();
    // Obtener el texto de la asignatura seleccionada
    QString asignatura = ui->cmbAsignatura->currentText();
    //Crear la tarea
    Tema *t = m_asignaturas->at(indexAsignatura)->temas().at(indexTema);
    // emite señal
    emit cuestionarioCreado(new Cuestionario(asignatura, t));
    // cerrar
    this->parentWidget()->close();

}


void CuestionarioForm::on_buttonBox_rejected()
{
    this->parentWidget()->close();
}

