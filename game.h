#ifndef GAME_H
#define GAME_H
#include "hole.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "chamber.h"
//!  Klasa gry
/*!
  Komora odpowiada za kontrolę przebiegu gry
*/
class Game: public QGraphicsView{
    Q_OBJECT
public:
    //! Zwraca instancję klasy
    static Game* getInstance();
    QGraphicsScene * scene;
    Chamber * chamber;
    Hole * holes[4];
    //! Rozpoczyna grę
    void start();
    //! Wstrzymuje grę
    void pause();
    //! Resetuje grę
    void reset();
    //! Zwraca stan gry (wstrzymany/w trakcie)
    bool getState();
    //! Zmienia stan gry
    void switchState();
    //! Aktualizuje numery wyświetlane w głównym oknie
    void updateNumbers();
signals:
    void update();

private:
    static Game* instance;
    Game(QWidget * parent=0);
    bool state;
};

#endif // GAME_H
