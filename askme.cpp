#include "askme.h"
#include "ui_askme.h"

Askme::Askme(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Askme)
{
    ui->setupUi(this);
    m_path = QDir::homePath() + QDir::separator() + "askme";
    m_archivo = m_path + QDir::separator() + "apuntes.csv";
    cargar();
    //guardar();
    connect(ui->actionCargar, SIGNAL(triggered()), this, SLOT(on_actionCargar_triggered()));

    this->setStyleSheet(
        "background-color: #333333; /* Fondo gris oscuro */"
        "color: #F2F1EB; /* Color de texto claro */"
        "font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;"
        "font-size: 14px; /* Tamaño de letra */"
        "border-radius: 15px; /* Bordes muy redondeados */"
        );

    // Establecer bordes redondos y fondo para todos los QPushButton
    QString elementStyle =
        "QComboBox, QLineEdit, QTextEdit, QTableWidget, QStringList {"
        "   background-color: #F2F1EB; /* Color claro para QComboBox y QLineEdit */"
        "   color: #333333; /* Color de texto oscuro */"
        "   border: 2px solid #666666; /* Borde sólido */"
        "   border-radius: 8px; /* Bordes redondeados */"
        "   padding: 5px; /* Relleno interno */"
        "}"
        "QPushButton {"
        "   background-color: #333333; /* Color de fondo de botón principal */"
        "   color: #F2F1EB; /* Color de texto en botón principal */"
        "   padding: 10px 20px; /* Relleno interno */"
        "   border: 2px solid #666666; /* Borde sólido */"
        "   border-radius: 15px; /* Bordes muy redondeados */"
        "   font-size: 14px; /* Tamaño de letra */"
        "   font-weight: bold; /* Texto en negrita */"
        "}"
        "QPushButton:hover {"
        "   background-color: #444444; /* Cambio de color al pasar el ratón */"
        "}"
        "QHeaderView::section {"
        "background-color: #333333; /* Color de fondo para los índices */"
        "   color: #F2F1EB; /* Color del texto para los índices */"
        "}";



    // Aplicar el estilo a los elementos específicos
    qApp->setStyleSheet(elementStyle);

}

Askme::~Askme()
{
    // disconnect(ui->actionCargar, SIGNAL(triggered()), this, SLOT(on_actionCargar_triggered()));
    delete ui;
}

void Askme::on_apunteTomado(Apunte *apunte)
{
    foreach(Asignatura *a, m_asignaturas)
    {
        qDebug().noquote() << a->toString();
    }
    guardar();
    //cargar();
    if (ui->mdiArea->currentSubWindow())
    {
        listaForm *listaVentana = qobject_cast<listaForm *>(ui->mdiArea->currentSubWindow()->widget());
        if (listaVentana)
        {
            listaVentana->cargarAsignaturas();
        }
    }
}

void Askme::on_cuestionarioCreado(Cuestionario *cuestionario)
{
    PreguntaForm *w = new PreguntaForm(this);
    w->setCuestionario(cuestionario);

    connect(w, SIGNAL(preguntasContestadas(Cuestionario*)), this, SLOT(on_preguntasContestadas(Cuestionario*)));

    cargarSubVentana(w);

}

void Askme::on_preguntasContestadas(Cuestionario *cuestionario)
{
    cuestionario->finalizar();
    ResultadosForm *w = new ResultadosForm(this);
    w->setDatos(cuestionario);
    cargarSubVentana(w);

    qDebug() << "Preguntas contestadas. Abriendo ResultadosForm...";

}

void Askme::cargarSubVentana(QWidget *ventana)
{
    auto sub = ui->mdiArea->addSubWindow(ventana);
    sub->show();
}

void Askme::guardar()
{
    QDir dir;
    if(!dir.exists(m_path))
    {
       dir.mkpath(m_path);
    }

    QFile file(m_archivo);
    QString path("");
    qDebug() << "Intentando abrir el archivo para escribir...";
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Archivo abierto correctamente.";
        QTextStream salida(&file);
        salida << "Asignatura\tTema\tTermino\tConcepto\n";
        foreach(Asignatura *a, m_asignaturas)
        {
            QString nombreAsignatura = a->nombre();
            foreach(Tema *t, a->temas())
            {
                QString nombreTema = t->nombre();
                foreach (Apunte *ap, t->apuntes())
                {
                    QString termino = ap->termino();
                    QString concepto = ap->concepto();

                    salida << nombreAsignatura << "\t" << nombreTema << "\t" << termino << "\t" << concepto << "\n";
                }
            }
        }
        file.close();
        if(m_normal)
        {
            QMessageBox::information(this, "Agregar apunte", "Apuntes agregados correctamente");
        }
        qDebug() << "Archivo cerrado correctamente.";
    }
    else
    {
        QMessageBox::critical(this, "Agregar apunte", "No se pudieron guardar los datos");
        qDebug() << "Error al abrir el archivo para escribir.";
    }
}

void Askme::cargar()
{
    QFile file(m_archivo);
    if(!file.exists())
    {
        m_normal = false;
        datosPrueba();
        guardar();
        m_normal = true;
        return;
    }
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream entrada(&file);
        entrada.readLine();
        while(!entrada.atEnd())
        {
            QString linea = entrada.readLine();
            QStringList datos = linea.split("\t");
            if(datos.size() >= 4)
            {
                QString nombreAsignatura = datos[0].trimmed();
                QString nombreTema = datos[1].trimmed();
                QString termino = datos[2].trimmed();
                QString concepto = datos[3].trimmed();
                Asignatura *asignatura = nullptr;
                Tema *tema = nullptr;


                foreach(Asignatura *a, m_asignaturas)
                {
                    if(a->nombre() == nombreAsignatura)
                    {
                        asignatura = a;
                        foreach(Tema *t, a->temas())
                        {
                            if(t->nombre() == nombreTema)
                            {
                                tema = t;
                                break;
                            }
                        }
                        break;
                    }
                }
                if (!asignatura)
                {
                    asignatura = new Asignatura(nombreAsignatura);
                    m_asignaturas.append(asignatura);
                }
                if (!tema)
                {
                    tema = new Tema(nombreTema);
                    asignatura->agregarTema(tema);
                }
                Apunte *apunte = new Apunte(termino, concepto);
                tema->agregarApunte(apunte);
            }
        }
        file.close();
    }
    else
    {
        QMessageBox::critical(this, "Cargar datos", "No se pudieron cargar los datos");
    }
}

void Askme::datosPrueba()
{
    Tema *t1 = new Tema("Electromagnetismo");
    t1->agregarApunte(new Apunte("Campo eléctrico", "Región del espacio alrededor de una carga eléctrica donde actúa una fuerza eléctrica sobre otras cargas."));
    t1->agregarApunte(new Apunte("Ley de Ampère","Relación matemática que describe la circulación de un campo magnético alrededor de un conductor por el cual fluye una corriente eléctrica."));
    t1->agregarApunte(new Apunte("Ley de Faraday","Principio que establece que un cambio en el flujo magnético a través de una espira induce una fuerza electromotriz (EMF) en la espira."));
    t1->agregarApunte(new Apunte("Bobina","Dispositivo formado por varias vueltas de alambre conductor, utilizado para generar un campo magnético o para inducir corriente."));
    t1->agregarApunte(new Apunte("Ley de Gauss","Principio que relaciona el flujo magnético a través de una superficie cerrada con la suma de las corrientes magnéticas que la atraviesan."));
    Tema *t2 = new Tema("Óptica");
    t2->agregarApunte(new Apunte("Luz","Radiación electromagnética visible por el ojo humano, que se propaga en forma de ondas."));
    t2->agregarApunte(new Apunte("Reflexión","Cambio en la dirección de propagación de la luz al pasar de un medio a otro con diferente índice de refracción."));
    t2->agregarApunte(new Apunte("Refracción","Cambio de dirección de un rayo de luz cuando incide sobre una superficie."));
    t2->agregarApunte(new Apunte("Prisma","Objeto óptico transparente con superficies planas que separa la luz en sus componentes de diferentes longitudes de onda."));
    t2->agregarApunte(new Apunte("Lente","Dispositivo óptico que enfoca o dispersa la luz mediante su curvatura, utilizado en cámaras, anteojos, microscopios, y telescopios."));
    Asignatura *a1 = new Asignatura("Fisica");
    a1->agregarTema(t1);
    a1->agregarTema(t2);
    t1 = new Tema("Ecología");
    t1->agregarApunte(new Apunte("Ecosistema", "Sistema formado por seres vivos y su entorno físico, donde interactúan entre sí y con el ambiente."));
    t1->agregarApunte(new Apunte("Biodiversidad", "Variedad de vida en la Tierra, que incluye la diversidad genética, de especies y de ecosistemas."));
    t1->agregarApunte(new Apunte("Cadena alimentaria", "Serie de organismos interconectados, donde cada uno se alimenta del anterior y es alimento para el siguiente."));
    t1->agregarApunte(new Apunte("Ciclo del agua", "Proceso continuo de circulación del agua entre la atmósfera, la tierra y los cuerpos de agua, que incluye evaporación, condensación y precipitación."));
    t1->agregarApunte(new Apunte("Bioma", "Gran área geográfica con características climáticas similares que alberga una comunidad específica de plantas y animales."));
    t2 = new Tema("Genética");
    t2->agregarApunte(new Apunte("ADN","Ácido desoxirribonucleico, la molécula que contiene la información genética hereditaria en los organismos."));
    t2->agregarApunte(new Apunte("Gen","Unidad de información hereditaria que codifica una característica específica, y que se encuentra en el ADN."));
    t2->agregarApunte(new Apunte("Cromosoma","Estructura compuesta por ADN y proteínas que transporta genes y se encuentra en el núcleo de las células."));
    t2->agregarApunte(new Apunte("Mutación","Cambio en la secuencia de ADN que puede dar lugar a variaciones genéticas."));
    t2->agregarApunte(new Apunte("Herencia","Transmisión de características genéticas de padres a descendencia a través de la reproducción."));
    Asignatura *a2 = new Asignatura("Ciencias naturales");
    a2->agregarTema(t1);
    a2->agregarTema(t2);
    m_asignaturas.append(a1);
    m_asignaturas.append(a2);
}

void Askme::on_actionNuevo_triggered()
{
    ApunteForm *w = new ApunteForm(this);
    w->setAsignaturas(m_asignaturas);
    w->cargarAsignaturas();
    connect(w, SIGNAL(nuevaAsignaturaCreada(Asignatura*)), this, SLOT(on_nuevaAsignaturaCreada(Asignatura*)));
    connect(w, SIGNAL(apunteTomado(Apunte*)), this, SLOT(on_apunteTomado(Apunte*)));
    cargarSubVentana(w);


}

void Askme::on_actionLista_triggered()
{
    listaForm *w = new listaForm(this);

    w->setAsignaturas(&m_asignaturas);

    w->cargarAsignaturas();

    cargarSubVentana(w);
    w->show();
}

void Askme::on_actionGenerar_triggered()
{
    CuestionarioForm *w = new CuestionarioForm(this);
    w->setAsignaturas(m_asignaturas);
    w->cargarAsignaturas();
    connect(w, SIGNAL(cuestionarioCreado(Cuestionario*)), this, SLOT(on_cuestionarioCreado(Cuestionario*)));
    // connect(w, SIGNAL(preguntasContestadas()), this, SLOT(on_preguntasContestadas(Pregunta*)));
    cargarSubVentana(w);
}


void Askme::on_actionCreditos_triggered()
{
    CreditosForm *w = new CreditosForm(this);
    cargarSubVentana(w);
}


void Askme::on_actionSalir_triggered()
{
    int opcion = QMessageBox::question(this, "Salir del programa", "¿Estas seguro de que quieres salir del programa?", QMessageBox::Yes | QMessageBox::No);
    if(opcion == QMessageBox::Yes)
    {
        qApp->quit();
    }
}

