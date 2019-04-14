#include "hole.h"
#include "game.h"

Hole::Hole(QVector<QPoint> points)
{
    x= points.first().x();
    y= points.first().y();
    setPolygon(QPolygonF(points));
    filled = false;
    ballNumber = 0;
}

bool Hole::isFilled()
{
    return filled;
}

int Hole::getBallNumber()
{
    return ballNumber;
}

int Hole::getX()
{
    return x;
}

int Hole::getY()
{
    return y;
}

void Hole::fill(int num)
{
    ballNumber = num;
    filled = true;
    Game::getInstance()->updateNumbers();
}

void Hole::unFill()
{
    ballNumber = 0;
    filled = false;
}
