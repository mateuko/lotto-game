#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "game.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set game in graphics view
    ui->graphicsView->setScene(Game::getInstance()->scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(800,600);

    //connect slots with signals
    connect(Game::getInstance(), SIGNAL(update()), this, SLOT(updateNumbers()));
    connect(ui->resetButton, SIGNAL (released()), this, SLOT (resetButton()));
    connect(ui->startButton, SIGNAL (released()), this, SLOT (startButton()));
    connect(ui->saveButton, SIGNAL (released()), this, SLOT (saveButton()));

    Game * game = Game::getInstance();
    ui->numberEdit->setPlainText("1");
    ui->axisAEdit->setPlainText(QString::number(game->chamber->getBallAxisA(1)));
    ui->axisBEdit->setPlainText(QString::number(game->chamber->getBallAxisB(1)));
    ui->coefficientEdit->setPlainText(QString::number(game->chamber->getBallCoefficient(1)));
    ui->centerEdit->setPlainText(QString::number(game->chamber->getBallCenter(1)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateNumbers()
{
      if(Game::getInstance()->holes[0]->isFilled())
      ui->drawnIndicator1->setText(QString::number(Game::getInstance()->holes[0]->getBallNumber()));
      if(Game::getInstance()->holes[1]->isFilled())
      ui->drawnIndicator2->setText(QString::number(Game::getInstance()->holes[1]->getBallNumber()));
      if(Game::getInstance()->holes[2]->isFilled())
      ui->drawnIndicator3->setText(QString::number(Game::getInstance()->holes[2]->getBallNumber()));
      if(Game::getInstance()->holes[3]->isFilled())
      ui->drawnIndicator4->setText(QString::number(Game::getInstance()->holes[3]->getBallNumber()));
}

void MainWindow::startButton()
{

    Game::getInstance()->switchState();
    if(Game::getInstance()->getState())
    {
        ui->startButton->setText("PAUSE");
        Game::getInstance()->start();
    }
    else {
        ui->startButton->setText("START");
        Game::getInstance()->pause();
    }
}

void MainWindow::resetButton()
{
    Game::getInstance()->reset();
    ui->startButton->setText("START");
    ui->drawnIndicator1->setText("");
    ui->drawnIndicator2->setText("");
    ui->drawnIndicator3->setText("");
    ui->drawnIndicator4->setText("");
}

void MainWindow::saveButton()
{
    Game::getInstance()->chamber->setBallProperties(ui->numberEdit->toPlainText().toInt(),ui->axisAEdit->toPlainText().toInt(),ui->axisBEdit->toPlainText().toInt()
                                                    ,ui->coefficientEdit->toPlainText().toDouble(),ui->centerEdit->toPlainText().toDouble());
}
