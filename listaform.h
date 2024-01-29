#ifndef LISTAFORM_H
#define LISTAFORM_H

#include <QWidget>
#include <QList>
#include "asignatura.h"


namespace Ui {
class listaForm;
}

class listaForm : public QWidget
{
    Q_OBJECT

public:
    explicit listaForm(QWidget *parent = nullptr);
    ~listaForm();

    void setAsignaturas(QList<Asignatura *> *asignaturas);
public slots:
    void cargarAsignaturas();
private slots:
    void cargarTemas();
    void cargarTerminos();
private:
    Ui::listaForm *ui;
    QList<Asignatura *> *m_asignaturas;

};

#endif // LISTAFORM_H
