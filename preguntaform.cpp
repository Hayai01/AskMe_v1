#include "preguntaform.h"
#include "ui_preguntaform.h"

PreguntaForm::PreguntaForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreguntaForm),
    m_cuestionario(nullptr)
{
    ui->setupUi(this);

   // connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(on_buttonBox_accepted()));
}

PreguntaForm::~PreguntaForm()
{
    delete ui;
}

void PreguntaForm::setCuestionario(Cuestionario *newCuestionario)
{
    m_cuestionario = newCuestionario;
    cargarDatos();
}

void PreguntaForm::mostrarConceptos()
{
    /*if (m_cuestionario) {
        qDebug() << "Antes de siguiente";
        Pregunta *preguntaActual = m_cuestionario->siguiente();
        qDebug() << "Después de siguiente";
        if (preguntaActual) {
            ui->txtConceptos->setText(preguntaActual->apunte()->concepto());
    }*/

    if(m_cuestionario->hayMasPreguntas())
    {
        m_pregunta = m_cuestionario->siguiente();
        ui->txtConceptos->setText(m_pregunta->apunte()->concepto());
        ui->txtConceptos->setReadOnly(true);
        int actual = m_cuestionario->mostradas();
        int total = m_cuestionario->totalPreguntas();
        ui->lblContador->setText(QString::number(actual) + " / " + QString::number(total));
    }
    else
    {
        ui->txtConceptos->clear();
        ui->txtConceptos->setText("** ** * Fin de las preguntas * ** **");
    }
}

void PreguntaForm::on_buttonBox_accepted()
{
    // Responde la pregunta actual
    QString respuesta = ui->cmbTerminos->currentText();
    if (!respuesta.isEmpty()) {
        m_pregunta->responder(respuesta);
        mostrarConceptos();
    } else {
        qDebug() << "Error: Respuesta vacía.";
    }
}

void PreguntaForm::siguienteConcepto()
{
    /*QString termino = ui->cmbTerminos->currentText();
    m_pregunta->responder(termino);
    mostrarConceptos();*/
}

void PreguntaForm::cargarDatos()
{
    ui->lblTema->setText(m_cuestionario->nombreTema());
    ui->cmbTerminos->addItems(m_cuestionario->terminos());
    mostrarConceptos();
}

void PreguntaForm::setAsignaturaAsomada(const QString &asignatura)
{
    ui->lblTema->setText(asignatura);
}

void PreguntaForm::setTemaAsomado(const QString &tema)
{
    ui->lblTema->setText(tema);
}

void PreguntaForm::on_buttonBox_rejected()
{
    qDebug() << "Antes de emitir la señal preguntasContestadas.";
    emit preguntasContestadas(m_cuestionario);
    // m_cuestionario->finalizar();
    this->parentWidget()->close();
    qDebug() << "Señal preguntasContestadas emitida.";
}

