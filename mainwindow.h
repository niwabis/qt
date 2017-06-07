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
signals:
    void tatk(int);
public slots:
    virtual void keyPressEvent(QKeyEvent *e);
private slots:
    void heroshealth();
    void herobeattack();
    void changecard(int);
    void atk(int);
    void manaplus();
    void gamestatus();
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
    void on_x05_clicked();
    void on_x075_clicked();
    void on_x1_clicked();
    void on_x15_clicked();
    void on_x2_clicked();

    void on_easy_clicked();

    void on_norml_clicked();

    void on_hard_clicked();

private:
    int card;
    int t;
    static int mana;
    static int herohealth;
    ChooseCard *choose;
    Ui::MainWindow *ui;
    tower *Tower;
    minion *Minion;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *bg;
    QGraphicsPixmapItem *hero;
    QGraphicsPixmapItem *end;
    QGraphicsPixmapItem *wall;
    QTimer *timer;
};

#endif // MAINWINDOW_H














