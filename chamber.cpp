#include "chamber.h"
#include <QGraphicsScene>
#include "ball.h"
#include <QTimer>

Chamber::Chamber()
{
    chamber = new QPixmap(":/images/chamber.png");
    QPixmap  chamberScaled = chamber->scaled(800,800);
    setPixmap(chamberScaled);
    centerX = 400;
    centerY = 400;
    chamberTimer = new QTimer();

}

Chamber::~Chamber()
{
    for(int i=0; i< balls.size();i++)
    {
       delete balls[i];
    }
}

void Chamber::spawn()
{
    int ballIterator = 1;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j< 5; j++)
        {
            Ball * ball = new Ball(300+i*60,50+j*60,20,20,ballIterator);
            scene()->addItem(ball);
            balls.append(ball);
            connect(chamberTimer,SIGNAL(timeout()),ball,SLOT(move()));
            ballIterator++;
        }

    }

}

double Chamber::getCenterX()
{
    return centerX;
}

double Chamber::getCenterY()
{
    return centerY;
}

void Chamber::start()
{
    chamberTimer->start(50);
}

void Chamber::pause()
{
    chamberTimer->stop();
}

void Chamber::clear()
{
    pause();
    for(int i=0; i< balls.size();i++)
    {
       scene()->removeItem(balls[i]);
       delete balls[i];
    }
    balls.clear();
}

int Chamber::getBallAxisA(int number)
{
    return balls[number-1]->getSemiAxisX();
}

int Chamber::getBallAxisB(int number)
{
    return balls[number-1]->getSemiAxisY();
}

double Chamber::getBallCoefficient(int number)
{
    return balls[number-1]->getCoefficient();
}

double Chamber::getBallCenter(int number)
{
    return balls[number-1]->getCenterOffset();
}

void Chamber::setBallProperties(int number, int axisA, int axisB, double coefficient, double center)
{
   balls[number-1]->setSemiAxes(axisA,axisB);
   balls[number-1]->setCoefficient(coefficient);
   balls[number-1]->setCenter(center);
}
