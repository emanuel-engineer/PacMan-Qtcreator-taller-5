#include "pacman.h"
#include <QGraphicsEllipseItem>
#include <QBrush>

Pacman::Pacman(QWidget *parent)
    : QMainWindow(parent), direction(0)
{
    //ventana principal
    setWindowTitle("PacMan en Qt");
    resize(600, 400);

    //crear y configurar la escena y vista
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    //configurar los limites de la escena
    scene->setSceneRect(0, 0, 580, 380);

    // Crear e inicializar el laberinto
    laberinto = new Laberinto(scene);
    laberinto->crear();

    //timer del juego
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &Pacman::updateGame);
    gameTimer->start(40); // ~60 FPS

    setupGame();
}

void Pacman::setupGame()
{
    //PacMan Sin Sprite
    pacman = scene->addEllipse(0, 0, 17, 17, QPen(Qt::black), QBrush(Qt::yellow));
    pacman->setPos(scene->width()/2, scene->height()/2);
     pacman->setPos(Laberinto::CELL_SIZE * 1, Laberinto::CELL_SIZE * 1);
}



void Pacman::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_D:
        direction = 0;
        break;
    case Qt::Key_S:
        direction = 1;
        break;
    case Qt::Key_A:
        direction = 2;
        break;
    case Qt::Key_W:
        direction = 3;
        break;
    }
}

void Pacman::updateGame()
{
    QPointF pos = pacman->pos();

    // Mover según la dirección
    switch (direction) {
    case 0: // Derecha
        if (pos.x() + STEP < scene->width() - STEP+1)
            pos.setX(pos.x() + STEP);
        break;
    case 1: // Abajo
        if (pos.y() + STEP > scene->height()-STEP+1)//> 0)
            pos.setY(pos.y() + STEP);
        break;
    case 2: // Izquierda
        if (pos.x() - STEP<scene->width()+STEP-1)
            pos.setX(pos.x() - STEP);
        break;
    case 3: // Arriba
        if (pos.y() - STEP >scene->height()+STEP-1)//> 0)
            pos.setY(pos.y() - STEP);
        break;
    }

    // Actualizar la posición de Pac-Man
    pacman->setPos(pos);
    QPointF newPos = pacman->pos();

    switch (direction) {
    case 0: // Derecha
        newPos.setX(newPos.x()-STEP);
        //while(Laberinto::disenoLaberinto[Laberinto::FILAS][Laberinto::COLUMNAS] == 1)
        //{newPos.setX(newPos.x()-STEP-4);}
        break;
    case 1: // Abajo
        newPos.setY(newPos.y() + STEP);
        //while(Laberinto::disenoLaberinto[Laberinto::FILAS][Laberinto::COLUMNAS] == 1)
        //{newPos.setY(newPos.y()-STEP-4);}
        break;
    case 2: // Izquierda NO FUNCIONA
        newPos.setX(newPos.x() + STEP);
        //while(Laberinto::disenoLaberinto[Laberinto::FILAS][Laberinto::COLUMNAS] == 1)
        //{newPos.setX(newPos.x()-STEP-4);}
        break;
    case 3: // Arriba
       newPos.setY(newPos.y() - STEP);
        //while(Laberinto::disenoLaberinto[Laberinto::FILAS][Laberinto::COLUMNAS] == 1)
        //{newPos.setY(newPos.y()-STEP-4);}
        break;
    }

    // Verificar colisión usando la clase Laberinto
    QRectF pacmanRect(newPos, QSizeF(10, 10));
    if (!laberinto->hayColision(pacmanRect)) {
        pacman->setPos(newPos);
    }
}

Pacman::~Pacman()
{
    delete laberinto;
}

