#include "apunteform.h"
#include "ui_apunteform.h"

ApunteForm::ApunteForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApunteForm)
{
    ui->setupUi(this);
    connect(ui->cmbAsignatura, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cmbAsignaturas_currentIndexChanged(int)));
}

ApunteForm::~ApunteForm()
{
    delete ui;
}

QList<Asignatura *> &ApunteForm::asignaturas()
{
    return *m_asignaturas;
}

void ApunteForm::setAsignaturas(QList<Asignatura *> &asignaturas)
{
    m_asignaturas = &asignaturas;
}

void ApunteForm::cargarAsignaturas()
{
    ui->cmbAsignatura->clear();
    foreach(Asignatura *a, *m_asignaturas)
    {
        ui->cmbAsignatura->addItem(a->nombre());
    }
}

void ApunteForm::on_cmbAsignatura_currentIndexChanged(int index)
{
    cargarTemas(index);
}

void ApunteForm::cargarTemas(int indice)
{
    ui->cmbClase->clear();
    if(indice >= 0 && indice < m_asignaturas->size())
    {
        Asignatura *a = m_asignaturas->at(indice);
        QList<Tema *> temas = a->temas();
        foreach(Tema *t, temas)
        {
            ui->cmbClase->addItem(t->nombre());
        }
    }
}

void ApunteForm::on_btnAgragraAsignatura_released()
{
    bool ok;
    QString nombre = QInputDialog::getText(this, "Agregar nueva asignatura","Nombre", QLineEdit::Normal, "", &ok);
    if(ok && !nombre.isEmpty())
    {
        Asignatura *nuevaAsignatura = new Asignatura(nombre);
        m_asignaturas->append(nuevaAsignatura);
        cargarAsignaturas();
        ui->cmbAsignatura->setCurrentText(nombre);
        // Emitir la señal de nuevaAsignaturaCreada con la nueva asignatura como argumento
        emit nuevaAsignaturaCreada(nuevaAsignatura);
    }
}


void ApunteForm::on_pushButton_4_released()
{
    cargarAsignaturas();
}


void ApunteForm::on_btnAgregarTema_released()
{
    bool ok;

    QString tema = QInputDialog::getText(this, "Agregar tema", "Tema", QLineEdit::Normal, "", &ok);
    if(ok && !tema.isEmpty())
    {
        int indiceAsignatura = ui->cmbAsignatura->currentIndex();
        m_asignaturas->at(indiceAsignatura)->agregarTema(new Tema(tema));
        on_cmbAsignatura_currentIndexChanged(indiceAsignatura);
        ui->cmbClase->setCurrentText(tema);
    }
}


void ApunteForm::on_pushButton_6_released()
{
    cargarAsignaturas();
}


void ApunteForm::on_buttonBox_accepted()
{
    QString termino = ui->txtTermino->text();
    QString concepto = ui->textEdit->toPlainText();
    int temaIndex = ui->cmbClase->currentIndex();
    int asignaturaIndex = ui->cmbAsignatura->currentIndex();

    if (asignaturaIndex < 0 || temaIndex < 0 || termino.isEmpty() || concepto.isEmpty())
    {
        // No permitir guardar si los datos están incompletos
        QMessageBox::warning(this, "Agregar apunte", "Por favor, complete todos los campos antes de guardar.");
        return;
    }

    // Crear el nuevo apunte
    Apunte *apunte = new Apunte(termino, concepto);
    // Obtener la asignatura seleccionada
    Asignatura *a = m_asignaturas->at(asignaturaIndex);
    // Agregar el apunte al tema seleccionado
    a->temas().at(temaIndex)->agregarApunte(apunte);

    // Emitir la señal solo si hay conectados interesados
    if (QObject::receivers(SIGNAL(apunteTomado(Apunte*))) > 0) {
        emit apunteTomado(apunte);
    }

    // Limpiar los campos después de guardar
    ui->txtTermino->clear();
    ui->textEdit->clear();
    ui->cmbAsignatura->setCurrentIndex(-1);
    ui->cmbClase->clear();

    // Cerrar el formulario después de guardar
    this->parentWidget()->close();
}


void ApunteForm::on_buttonBox_rejected()
{
    this->parentWidget()->close();
}

