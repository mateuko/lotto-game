#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "game.h"
#include <QMediaPlayer>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chamber.h"
#include <QGraphicsEllipseItem>

Game::Game(QWidget *parent)
{
    scene = new QGraphicsScene(this);
    state = false;

    chamber = new Chamber();

    scene->addItem(chamber);
    chamber->spawn();

    QVector<QPoint> points;
    /*
    points<<QPoint(525,120)<<QPoint(575,120)<<QPoint(575,200)<<QPoint(525,175);
    holes[0] = new Hole(points);
    points.clear();
    points<<QPoint(600,200)<<QPoint(650,200)<<QPoint(650,300)<<QPoint(600,225);
    holes[1] = new Hole(points);
    points.clear();
    points<<QPoint(225,120)<<QPoint(275,120)<<QPoint(275,175)<<QPoint(225,200);
    holes[2] = new Hole(points);
    points.clear();
    points<<QPoint(150,200)<<QPoint(200,200)<<QPoint(200,225)<<QPoint(150,300);
    holes[3] = new Hole(points);
    points.clear();


    for(int i=0; i<4;i++)
    {
      scene->addItem(holes[i]);
    }
    */
}
Game *Game::instance = 0;
Game *Game::getInstance()
{
    if (instance == 0)
        {
            instance = new Game();
        }
        return instance;
}

void Game::start()
{
    chamber->start();
}

void Game::pause()
{
    chamber->pause();
}

void Game::reset()
{
    chamber->clear();
    chamber->spawn();
    for(int i=0; i<4; i++)
    {
        holes[i]->unFill();
    }
}



bool Game::getState()
{
    return state;
}

void Game::switchState()
{
    state = !state;

}

void Game::updateNumbers()
{
    emit update();
    if(holes[0]->isFilled() &&  holes[1]->isFilled() && holes[2]->isFilled() && holes[3]->isFilled())
        pause();
}


