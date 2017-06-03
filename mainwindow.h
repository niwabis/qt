#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"minion.h"
#include"choosecard.h"
#include"tower.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include "minion.h"

#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void changecard(int);
    void atk(int);
    void on_card1_clicked();
    void on_card2_clicked();
    void on_card3_clicked();
    void on_card4_clicked();
    void on_card5_clicked();
    void on_but1_clicked();
    void on_but2_clicked();
    void on_but3_clicked();
    void on_but4_clicked();
    void on_but5_clicked();
    void on_but6_clicked();
    void on_but7_clicked();
    void on_but8_clicked();

private:
    int card;
    ChooseCard *choose;
    Ui::MainWindow *ui;
    tower *Tower;
    minion *Minion;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *bg;
    QGraphicsPixmapItem *wall;
    QTimer *timer;
};

#endif // MAINWINDOW_H














