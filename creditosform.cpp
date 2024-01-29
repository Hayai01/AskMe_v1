#include "creditosform.h"
#include "ui_creditosform.h"

CreditosForm::CreditosForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreditosForm)
{
    ui->setupUi(this);

    // Colaboradores de Computación

    // Nombres

    ui->cmbColaboradores1->addItem("Christopher Ariel Flores Caiza");
    ui->cmbColaboradores1->addItem("Mayerli Julieth Campuez de la Cruz");
    ui->cmbColaboradores1->addItem("Fabian Liam Izquierdo Oñate");
    ui->cmbColaboradores1->addItem("Luis Adrian Pillajo Lema");
    ui->cmbColaboradores1->addItem("Jose David Ramos Cuenca");
    ui->cmbColaboradores1->addItem("Sebastian Mateo Espinosa Jimenez");
    ui->cmbColaboradores1->addItem("Joseph Andres Uyana Mora");

    // GitHub

    ui->cmbColaboradoresUno->addItem("rtufino");
    ui->cmbColaboradoresUno->addItem("FLiam Tech");
    ui->cmbColaboradoresUno->addItem("ArielFLores5");
    ui->cmbColaboradoresUno->addItem("Hayai01");
    ui->cmbColaboradoresUno->addItem("Mayerli12");
    ui->cmbColaboradoresUno->addItem("LuisCOD369");
    ui->cmbColaboradoresUno->addItem("defaultdavr21");
    ui->cmbColaboradoresUno->addItem("EonSoulCout");

    // Colaboradores de Filosofia

    ui->cmbColaboradoresDos->addItem("Jonathan Andrés Analuisa Vargas");
    ui->cmbColaboradoresDos->addItem("Juan Pablo Pauchi Cerda");
    ui->cmbColaboradoresDos->addItem("Jimmy Xavier Zambrano");
    ui->cmbColaboradoresDos->addItem("Félix David Tulcán Coral");
    ui->cmbColaboradoresDos->addItem("Gustavo Rubén Quishpe Ayala");
    ui->cmbColaboradoresDos->addItem("Rómulo Yordan Valera Quispilaya");
    ui->cmbColaboradoresDos->addItem("Jennifer Nicole Játiva Erazo");
}

CreditosForm::~CreditosForm()
{
    delete ui;
}

void CreditosForm::on_pushButton_released()
{
    int index = ui->cmbColaboradoresUno->currentIndex();
    QString URL;
    switch(index)
    {
    case 0:
        URL = "https://github.com/rtufino";
        break;
    case 1:
        URL = "https://github.com/FLiamTech";
        break;
    case 2:
        URL = "https://github.com/ArielFLores5";
        break;
    case 3:
        URL = "https://github.com/Hayai01";
        break;
    case 4:
        URL = "https://github.com/Mayerli12";
        break;
    case 5:
        URL = "https://github.com/LuisCOD369";
        break;
    case 6:
        URL = "https://github.com/defaultdavr21";
        break;
    case 7:
        URL = "https://github.com/EonSoulCout";
        break;

    }

    if(!URL.isEmpty())
    {
        QDesktopServices::openUrl(QUrl(URL));
    }

}


void CreditosForm::on_pushButton_2_released()
{
    // Crear y configurar el cuadro de diálogo
    QMessageBox mensaje;
    mensaje.setIcon(QMessageBox::Information);
    mensaje.setWindowTitle("Agradecimientos");
    mensaje.setText("Desde el Departamento de la Carrera de Filosofía de la Universidad Politécnica Salesiana, con sede en el campus El Girón, en conjunto con la Carrera de Computación ubicada en el Campus Sur, nos complace expresar nuestros sinceros agradecimientos por la valiosa colaboración entre ambas carreras en la realización de este gran proyecto.\n\n"
                    "Con la concepción y planificación por parte de la Carrera de Filosofía, aportando con una visión y un enfoque inicial marcando su origen. Por otra parte, la Carrera de Computación asumió la responsabilidad de su desarrollo y ejecución, desempeñando un papel fundamental en la realización de esta aplicación.\n\n"
                    "Expresamos nuestros profundos agradecimientos a todos los involucrados en este proyecto. ¡Gracias por hacer posible esta exitosa colaboración!");

    // Mostrar el cuadro de diálogo
    mensaje.exec();
}

