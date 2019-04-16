#ifndef CHAMBER_H
#define CHAMBER_H
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QVector>
#include <ball.h>
//!  Klasa komory
/*!
  Komora odpowiada za generowanie kulek i dostarczanie informacji o nich
*/

class Chamber: public QObject,public QGraphicsPixmapItem
{
Q_OBJECT
public:
    //! Konstruktor
    Chamber();
    //! Destruktor
    ~Chamber();
    //! Powoduje pojawienie się kulek
    void spawn();
    //! Zwraca współrzędną X środka komory
    double getCenterX();
    //! Zwraca współrzędną Y środka komory
    double getCenterY();
    QTimer * chamberTimer;
    //! Uruchamia przebieg czasu
    void start();
    //! Zatrzymuje czas
    void pause();
    //! Usuwa kulki
    void clear();
    //! Zwraca półoś X kulki o wybranym numerze
    int getBallAxisA(int);
    //! Zwraca półoś Y kulki o wybranym numerze
    int getBallAxisB(int);
    //! Zwraca współczynnik odbicia kulki o wybranym numerze
    double getBallCoefficient(int);
    //! Zwraca przesunięcie środka ciężkości kulki o wybranym numerze
    double getBallCenter(int);
    //! Ustawia długości półosi, współczynnik odbicia oraz przesunięcie środka ciężkości kulki o wybranym numerze
    void setBallProperties(int,int,int,double,double);
public slots:
    void collide();
private:
    QVector<Ball*> balls;
    QPixmap * chamber;
    double centerX;
    double centerY;
};

#endif // CHAMBER_H
