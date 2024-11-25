#ifndef LABERINTO_H
#define LABERINTO_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVector>

class Laberinto {
public:
    Laberinto(QGraphicsScene *scene);
    void crear();
    bool hayColision(const QRectF &rect) const;
    static const int CELL_SIZE = 20;

private:
    QGraphicsScene *scene;
    QVector<QGraphicsRectItem*> paredes;

    // Matriz que define el diseño del laberinto
    static const int FILAS = 22;
    static const int COLUMNAS = 28;
    static const int disenoLaberinto[FILAS][COLUMNAS];
};

#endif
