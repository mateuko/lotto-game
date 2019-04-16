#include "ball.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <QtDebug>
#include <QMediaPlayer>
#include <math.h>
#include "chamber.h"
#include "hole.h"
#include "game.h"
Q_DECLARE_METATYPE(Ball)
Q_DECLARE_METATYPE(Ball*)
Ball::Ball(int x, int y, int axisX, int axisY, int number)
{
    collisionsound = new QMediaPlayer();
    collisionsound->setMedia(QUrl("qrc:/sounds/pop_sound.wav"));

    //set position
    setPos(x,y);

    immobilized = false;
    this->number = number;
    speedx=0;
    speedy=0;
    semiAxisX = axisX;
    semiAxisY = axisY;
    elasticityCoefficient = 1;
    centerOffset=0;

   ball = new QPixmap(":/images/ball.png");
   QPixmap  ballscaled = ball->scaled(2*semiAxisX,2*semiAxisY);
   setPixmap(ballscaled);

}

Ball::Ball(const Ball &en2)
{
    speedx=en2.speedx;
    speedy=en2.speedy;
    semiAxisX=en2.semiAxisX;
    semiAxisY=en2.semiAxisY;
}

double Ball::getSpeedX()
{
    return speedx;
}

double Ball::getSpeedY()
{
    return speedy;
}

int Ball::getSemiAxisX()
{
    return semiAxisX;
}

int Ball::getSemiAxisY()
{
    return semiAxisY;
}

int Ball::getNumber()
{
    return number;
}


void Ball::immobilize()
{
    immobilized=true;
}

double Ball::getCoefficient()
{
    return elasticityCoefficient;
}

double Ball::getCenterOffset()
{
    return centerOffset;
}

void Ball::setSpeed(double velocityx, double velocityy)
{
   speedx = velocityx;
   speedy = velocityy;
}

void Ball::setSemiAxes(int axisA, int axisB)
{
    QPixmap  ballscaled = ball->scaled(2*axisA,2*axisB);
    setPixmap(ballscaled);
}

void Ball::setCoefficient(double coefficient)
{
    elasticityCoefficient=coefficient;
}

void Ball::setCenter(double center)
{
    centerOffset=center;
}


void Ball::move()
{

    QList<QGraphicsItem  *> colliding_items = collidingItems();
    double xC = x()*(1+centerOffset/100);
    double yC = y()*(1+centerOffset/100);
    for (int i=0, n=colliding_items.size(); i<n; ++i ){

          double dx = xC-colliding_items[i]->x();
          double dy = yC-colliding_items[i]->y();
          double initialV1X = speedx;
          double initialV1Y = speedy;
          double initialAngle1 = atan(speedy/speedx);
          double speedCalculationx = 0;
          double speedCalculationy = 0;
          double dotProduct1 = 0;
          double dotProduct2 = 0;

          if(typeid(*(colliding_items[i])) == typeid(Ball))
          {
            /*  Ball * collidingBall = dynamic_cast<Ball *>(colliding_items[i]);
              dx = xC+semiAxisX-(collidingBall->x()+collidingBall->semiAxisX);
              dy = yC+semiAxisY-(collidingBall->y()+collidingBall->semiAxisY);
              dotProduct1 = (speedx - collidingBall->speedx)*dx + (speedy - collidingBall->speedy)*dy;
              dotProduct2 = (collidingBall->speedx-initialV1X)*(-dx) + (collidingBall->speedy-initialV1Y)*(-dy);
              speedCalculationx = collidingBall->speedx - dotProduct2/pow(sqrt(pow(dx,2)+pow(dy,2)),2) * (-dx);
              speedCalculationy = collidingBall->speedy - dotProduct2/pow(sqrt(pow(dx,2)+pow(dy,2)),2) * (-dy);
              collidingBall->setSpeed(collidingBall->getCoefficient()*speedCalculationx, collidingBall->getCoefficient()*speedCalculationy);

              speedCalculationx = speedx - dotProduct1/pow(sqrt(pow(dx,2)+pow(dy,2)),2) * dx;
              speedCalculationy = speedy - dotProduct1/pow(sqrt(pow(dx,2)+pow(dy,2)),2) * dy;
              setSpeed(getCoefficient()*speedCalculationx, getCoefficient()*speedCalculationy);*/

          }
          else if(typeid(*(colliding_items[i])) == typeid(Chamber)){
              Chamber * collidingChamber = dynamic_cast<Chamber *>(colliding_items[i]);
              dx = xC+semiAxisX - collidingChamber->getCenterX();
              dy = yC+semiAxisY - collidingChamber->getCenterY();
              double distance = sqrt(pow(dx,2)+pow(dy,2));
              double normalX = dx/distance;
              double normalY = dy/distance;
              speedCalculationx = speedx - 2*normalX*(speedx*normalX+speedy*normalY);
              speedCalculationy = speedy - 2*normalY*(speedx*normalX+speedy*normalY);
              setSpeed(getCoefficient()*speedCalculationx, getCoefficient()*speedCalculationy);

          }
          else if(typeid(*(colliding_items[i])) == typeid(Hole)){
              Hole * collidingHole = dynamic_cast<Hole *>(colliding_items[i]);
              if(collidingHole->isFilled())
              {
                  dx = xC+semiAxisX - 400;
                  dy = yC+semiAxisY - 400;
                  double distance = sqrt(pow(dx,2)+pow(dy,2));
                  double normalX = dx/distance;
                  double normalY = dy/distance;
                  speedCalculationx = speedx - 2*normalX*(speedx*normalX+speedy*normalY);
                  speedCalculationy = speedy - 2*normalY*(speedx*normalX+speedy*normalY);
                  setSpeed(getCoefficient()*speedCalculationx, getCoefficient()*speedCalculationy);
              }
              else {
                  collidingHole->fill(this->getNumber());
                  setSpeed(0,0);
                  this->immobilize();
                  qDebug()<<collidingHole->getX()<<" y:"<<colliding_items[i]->y();
                  this->setPos(collidingHole->getX(), collidingHole->getY());
              }
          }
          else {
              dotProduct1 = (speedx - (-speedx))*dx + (speedy - (-speedy))*dy;

              speedCalculationx = speedx - dotProduct1/pow(sqrt(pow(dx,2)+pow(dy,2)),2) * dx;
              speedCalculationy = speedy - dotProduct1/pow(sqrt(pow(dx,2)+pow(dy,2)),2) * dy;
              setSpeed(getCoefficient()*speedCalculationx, getCoefficient()*speedCalculationy);
          }



        //play sound
        if(collisionsound->state() == QMediaPlayer::PlayingState){
            collisionsound->setPosition(0);
        }
        else if(collisionsound->state() == QMediaPlayer::StoppedState){
            collisionsound->play();
        }
    }

    //move ball
    if(!immobilized)
    {
     setPos(x()+speedx,y()+speedy);
    }

    //add gravity
    setSpeed(speedx, speedy+0.5);
}
