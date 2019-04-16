#include "chamber.h"
#include <QGraphicsScene>
#include "ball.h"
#include <QTimer>
#include "hole.h"
#include <math.h>

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
    connect(chamberTimer,SIGNAL(timeout()),this,SLOT(collide()));
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

void Chamber::collide()
{
    for(int i=0;i<balls.size();i++)
    {
        double xC1 = (1 + balls[i]->getCenterOffset()/100)*(balls[i]->x()+balls[i]->getSemiAxisX());
        double yC1 = (1 + balls[i]->getCenterOffset()/100)*(balls[i]->y()+balls[i]->getSemiAxisY());
        for(int j=i+1; j<balls.size();j++)
        {
            double xC2 = (1 + balls[j]->getCenterOffset()/100)*(balls[j]->x()+balls[j]->getSemiAxisX());
            double yC2 = (1 + balls[j]->getCenterOffset()/100)*(balls[j]->y()+balls[j]->getSemiAxisY());
            double distance = sqrt(pow(xC1-xC2,2)+pow(yC1-yC2,2));
            if(distance <= (balls[i]->getSemiAxisX()+balls[j]->getSemiAxisY())){
                balls[i]->setSpeed(-balls[i]->getSpeedX(),-balls[i]->getSpeedY());
                balls[j]->setSpeed(-balls[j]->getSpeedX(),-balls[j]->getSpeedY());
                qDebug()<<"odl";
            }
        }
    }
}
