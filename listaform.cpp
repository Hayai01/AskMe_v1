#include "listaform.h"
#include "ui_listaform.h"

#include "listaform.h"
#include "ui_listaform.h"

listaForm::listaForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::listaForm),
    m_asignaturas(nullptr)
{
    ui->setupUi(this);
    // Conectar señal de cambio en la asignatura
    connect(ui->cmbAsignaturas, SIGNAL(currentIndexChanged(int)), this, SLOT(cargarTemas()));
    // Conectar señal de cambio en el tema
    connect(ui->cmbTemas, SIGNAL(currentIndexChanged(int)), this, SLOT(cargarTerminos()));

    cargarAsignaturas();
}

listaForm::~listaForm()
{
    delete ui;
}

void listaForm::setAsignaturas(QList<Asignatura *> *asignaturas)
{
    m_asignaturas = asignaturas;
}

void listaForm::cargarAsignaturas()
{
    ui->cmbAsignaturas->clear();

    if (m_asignaturas)
    {
        foreach(Asignatura *a, *m_asignaturas)
        {
            ui->cmbAsignaturas->addItem(a->nombre());
        }
    }

    // Cargar los temas cuando se selecciona una asignatura inicialmente
    cargarTemas();
}

void listaForm::cargarTemas()
{
    ui->cmbTemas->clear();
    ui->txtApuntes->clear(); // Limpiar el contenido actual

    QString nombreAsignatura = ui->cmbAsignaturas->currentText();

    if (m_asignaturas)
    {
        Asignatura *asignaturaSeleccionada = nullptr;
        foreach (Asignatura *a, *m_asignaturas)
        {
            if (a->nombre() == nombreAsignatura)
            {
                asignaturaSeleccionada = a;
                break;
            }
        }

        if (asignaturaSeleccionada)
        {
            QList<Tema *> temas = asignaturaSeleccionada->temas();

            foreach (Tema *t, temas)
            {
                ui->cmbTemas->addItem(t->nombre());
            }
        }
    }

    qDebug() << "Temas cargados correctamente.";

}



void listaForm::cargarTerminos()
{
    ui->txtApuntes->clear(); // Limpiar el contenido actual

    QString nombreAsignatura = ui->cmbAsignaturas->currentText();
    QString nombreTema = ui->cmbTemas->currentText();

    if (m_asignaturas)
    {
        Asignatura *asignaturaSeleccionada = nullptr;
        foreach (Asignatura *a, *m_asignaturas)
        {
            if (a->nombre() == nombreAsignatura)
            {
                asignaturaSeleccionada = a;
                break;
            }
        }

        qDebug() << "Apunte:" << asignaturaSeleccionada;

        if (asignaturaSeleccionada)
        {
            QList<Tema *> temas = asignaturaSeleccionada->temas();
            foreach (Tema *t, temas)
            {
                if (t->nombre() == nombreTema)
                {
                    // Mostrar términos asociados al tema seleccionado
                    QList<Apunte *> apuntes = t->apuntes();
                    foreach (Apunte *ap, apuntes)
                    {
                        qDebug() << "Apunte:" << ap->toString();
                        ui->txtApuntes->append(ap->toString());
                        ui->txtApuntes->append("--------------------"); // Línea separadora
                    }
                    break;
                }
            }
        }
    }
}
