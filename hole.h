#ifndef HOLE_H
#define HOLE_H
#include <QGraphicsPolygonItem>
//!  Klasa dołka
/*!
  Komora odpowiada za unieruchamianie kulek, które wpadły do dołka
*/

class Hole: public QGraphicsPolygonItem
{
public:
    //! Konstruktor - tworzy dołek jako wielokąt na podstawie punktów
    Hole(QVector<QPoint>);
    //! Sprawdza czy w dołku jest już kulka
    bool isFilled();
    //! Zwraca numer kulki, która znajduje się w dołku
    int getBallNumber();
    //! Zwraca współrzędną x dołka
    int getX();
    //! Zwraca współrzędną y dołka
    int getY();
    //! Umieszcza w dołku kulkę z danym numerem
    void fill(int);
    //! Usuwa kulkę z dołka
    void unFill();
signals:
    void updateNumbers(QString);
private:
    bool filled;
    int ballNumber;
    int number;
    int x;
    int y;
};

#endif // HOLE_H
