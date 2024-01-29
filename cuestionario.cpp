#include "cuestionario.h"

Cuestionario::Cuestionario()
{

}

Cuestionario::Cuestionario(QString asignatura, Tema *tema) : m_tema(tema), m_asignatura(asignatura), m_mostradas(0)
{
    foreach(Apunte *a, m_tema->apuntes())
    {
        m_preguntas.append(new Pregunta(a));
        m_terminos.append(a->termino());
    }
}

Pregunta *Cuestionario::siguiente()
{
    // TO do lanzar preguntas al azar
    QList<Pregunta *> preguntasRespondidas;
    foreach (Pregunta *p, m_preguntas)
    {
        if(!p->respuesta())
        {
            preguntasRespondidas.append(p);
        }
    }
    if(!preguntasRespondidas.isEmpty())
    {
        int indiceAleatorio = QRandomGenerator::global()->bounded(preguntasRespondidas.size());
        Pregunta *preguntaAleatoria = preguntasRespondidas[indiceAleatorio];
        m_mostradas++;
        return preguntaAleatoria;
    }

    return nullptr;


    /*foreach(Pregunta *p, m_preguntas)
    {
        if(!p->respuesta())
        {
            m_mostradas++;
            return p;
        }
    }
    return nullptr;*/
}

const QStringList &Cuestionario::terminos() const
{
    return m_terminos;
}

float Cuestionario::finalizar()
{
    int correcta = 0;
    int respondida = 0;
    foreach(Pregunta *p, m_preguntas)
    {
        if(p->respuesta())
        {
            respondida++;
            if(p->correcto())
            {
                correcta++;
            }
        }
    }
    if(respondida > 0)
    {
        return m_score = (correcta * 100.0) / respondida;
    }
    else
    {
        return m_score = 0;
    }

}

float Cuestionario::score() const
{
    return m_score;
}

const QList<Pregunta *> &Cuestionario::preguntas() const
{
    return m_preguntas;
}

QString Cuestionario::nombreTema() const
{
    return m_tema->nombre();
}

int Cuestionario::totalPreguntas() const
{
    return m_preguntas.size();
}

bool Cuestionario::hayMasPreguntas()
{
    return (m_mostradas < totalPreguntas());
}

int Cuestionario::mostradas() const
{
    return m_mostradas;
}

const QString &Cuestionario::asignatura() const
{
    return m_asignatura;
}

void Cuestionario::setAsignatura(const QString &newAsignatura)
{
    m_asignatura = newAsignatura;
}
