#ifndef Ball_H
#define Ball_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QGraphicsPixmapItem>

//!  Klasa kulki
/*!
  Klasa odpowiada za przechowywanie danych o kulkach, zmianę ich parametrów, wykrywanie kolizji z innymi elementami.
*/
class Ball: public QObject, public QGraphicsPixmapItem{
Q_OBJECT

private:

    int number;
    double speedx;
    double speedy;
    int semiAxisX;
    int semiAxisY;
    double elasticityCoefficient;
    double centerOffset;
    QMediaPlayer * collisionsound;
    QPixmap * ball;
    bool immobilized;
public:
    //! Konstruktor.
    /*!
      Konstruktor umieszczający kulkę w danym miejscu, ustawiając długości jej półośi oraz jej numer.
    */
    Ball(int x=0, int y=0, int axisX=25, int axisY=25, int number=0);
    Ball(const Ball &en2);

    //! Ustawia wartości prędkości kulki w kierunkach x oraz y
    void setSpeed(double, double);
    //! Ustawia wartości półosi kulki
    void setSemiAxes(int,int);
    //! Ustawia wartość współczynnika odbicia kulki
    void setCoefficient(double);
    //! Ustawia wartość przesunięcia środka ciężkości kulki
    void setCenter(double);
    //! Zwraca prędkość kulki w kierunku x
    double getSpeedX();
    //! Zwraca prędkość kulki w kierunku y
    double getSpeedY();
    //! Zwraca długość poziomej półosi
    int getSemiAxisX();
    //! Zwraca długość pionowej półosi
    int getSemiAxisY();
    //! Zwraca numer kulki
    int getNumber();
    //! Oblicza prędkość kulki po zderzeniu
    void collide(double, double, double, double);
    //! Unieruchamia kulkę
    void immobilize();
    //! Zwraca współczynnik odbicia kulki
    double getCoefficient();
    //! Zwraca przesunięcie środka ciężkości kulki
    double getCenterOffset();
public slots:
    //! Przemieszcza kulkę zgodnie z jej prędkością i sprawdza kolizje z innymi elementami
    void move();

};


#endif // Ball_H
