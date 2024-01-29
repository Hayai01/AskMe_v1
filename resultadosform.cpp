#include "resultadosform.h"
#include "ui_resultadosform.h"

ResultadosForm::ResultadosForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultadosForm)
{
    ui->setupUi(this);
}

ResultadosForm::~ResultadosForm()
{
    delete ui;
}

void ResultadosForm::setDatos(Cuestionario *cuestionario)
{
        m_cuestionario = cuestionario;
        cargarDatos();
}

void ResultadosForm::cargarDatos()
{
    float score = m_cuestionario->score();
    QString tema = m_cuestionario->nombreTema();
    QString asignatura = m_cuestionario->asignatura();
    QString porcentaje = QString::number(score, 'f', 2) + "%";
    // Mostrar el score
    ui->lblScore->setText("Score: " + porcentaje);
    // Mostar el tema
    ui->lblTema->setText(tema);
    //Mostrar la asignatura
    ui->lblAsignatura->setText(asignatura);
    // Cargar datos en la tabla
    QList<Pregunta *> preguntas = m_cuestionario->preguntas();

    QList<Pregunta *> preguntasContestadas;
    for (Pregunta *pregunta : preguntas) {
        if (pregunta->respuesta()) {
            preguntasContestadas.append(pregunta);
        }
    }
    ui->tblResultados->setRowCount(preguntas.size());
    ui->tblResultados->setColumnCount(3);

    ui->tblResultados->setHorizontalHeaderLabels({"Termino", "Concepto", "Contestada Correctamente"});

    // Llenar la tabla con los datos de las preguntas
    for (int i = 0; i < preguntasContestadas.size(); ++i)
    {
        QTableWidgetItem *terminoItem = new QTableWidgetItem(preguntas[i]->apunte()->termino());
        QTableWidgetItem *conceptoItem = new QTableWidgetItem(preguntas[i]->apunte()->concepto());
        QTableWidgetItem *correctoItem = new QTableWidgetItem(preguntas[i]->correcto() ? "✅" : "❌");


        ui->tblResultados->setItem(i, 0, terminoItem);
        ui->tblResultados->setItem(i, 1, conceptoItem);
        ui->tblResultados->setItem(i, 2, correctoItem);

    }
}

void ResultadosForm::on_btnCerrar_released()
{
    this->parentWidget()->close();
}

