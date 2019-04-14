#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

//!  Klasa głównego okna
/*!
  Odpowiada za wyświetlanie przebiegu gry, możliwość zmiany parametrów kulek
*/

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   // QGraphicsScene *scene;

private slots:
    void startButton();
    void resetButton();
    void saveButton();
    void updateNumbers();
private:
    Ui::MainWindow *ui;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;

};

#endif // MAINWINDOW_H
