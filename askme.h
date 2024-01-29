#ifndef ASKME_H
#define ASKME_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

#include <apunteform.h>
#include <asignatura.h>
#include <listaform.h>
#include <cuestionarioform.h>
#include <preguntaform.h>
#include <resultadosform.h>
#include <creditosform.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Askme; }
QT_END_NAMESPACE

class Askme : public QMainWindow
{
    Q_OBJECT

public:
    Askme(QWidget *parent = nullptr);
    ~Askme();

public slots:
    void on_apunteTomado(Apunte *apunte);
    void on_cuestionarioCreado(Cuestionario *cuestionario);
    void on_preguntasContestadas(Cuestionario *cuestionario);

private:
    Ui::Askme *ui;
    QList<Asignatura *> m_asignaturas;

    void cargarSubVentana(QWidget *ventana);
    void guardar();
    void cargar();
    void valiarDirectorio();
    void datosPrueba();

    bool m_normal = true;
    QString m_path;
    QString m_archivo;

private slots:
    void on_actionNuevo_triggered();
    void on_actionLista_triggered();
    void on_actionGenerar_triggered();
    void on_actionCreditos_triggered();
    void on_actionSalir_triggered();
};

#endif // ASKME_H
