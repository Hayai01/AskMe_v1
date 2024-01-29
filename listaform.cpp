#include "listaform.h"
#include "ui_listaform.h"

listaForm::listaForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::listaForm),
    m_asignaturas(nullptr)
{
    ui->setupUi(this);

    // Configurar la tabla de temas
    ui->tblTemas->setColumnCount(1);
    QStringList tituloTemas;
    tituloTemas << "Tema";
    ui->tblTemas->setHorizontalHeaderLabels(tituloTemas);

    // Configurar la tabla de terminos
    ui->tblTerminos->setColumnCount(1);
    QStringList tituloTerminos;
    tituloTerminos << "Termino";
    ui->tblTerminos->setHorizontalHeaderLabels(tituloTerminos);

    // Conectar señal de cambio en la asignatura
    connect(ui->cmbAsignaturas, SIGNAL(currentIndexChanged(int)), this, SLOT(cargarTemas()));
    // Conectar señal de clic en la tabla de temas
    connect(ui->tblTemas, SIGNAL(cellClicked(int, int)), this, SLOT(cargarTerminos(int, int)));

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
}

void listaForm::cargarTemas()
{
    ui->tblTemas->clearContents();
    ui->tblTemas->setRowCount(0);

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

            int fila = 0;
            foreach (Tema *t, temas)
            {
                // Insertar fila en la tabla de temas
                ui->tblTemas->insertRow(fila);
                ui->tblTemas->setItem(fila, 0, new QTableWidgetItem(t->nombre()));
                fila++;
            }
        }
    }

    // Limpiar y reiniciar la tabla de términos
    ui->tblTerminos->clearContents();
    ui->tblTerminos->setRowCount(0);
}

void listaForm::cargarTerminos(int fila, int columna)
{
    ui->tblTerminos->clearContents();
    ui->tblTerminos->setRowCount(0);

    if (fila >= 0)
    {
        QString nombreAsignatura = ui->cmbAsignaturas->currentText();
        QString nombreTema = ui->tblTemas->item(fila, columna)->text();

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
                    if (t->nombre() == nombreTema)
                    {
                        // Mostrar términos asociados al tema seleccionado
                        QList<Apunte *> apuntes = t->apuntes();
                        int filaTerminos = 0;
                        foreach (Apunte *ap, apuntes)
                        {
                            ui->tblTerminos->insertRow(filaTerminos);
                            ui->tblTerminos->setItem(filaTerminos, 0, new QTableWidgetItem(ap->termino()));
                            filaTerminos++;
                        }
                        break;
                    }
                }
            }
        }
    }
}

void listaForm::on_tblTemas_cellClicked(int row, int column)
{
    cargarTerminos(row, column);
}
