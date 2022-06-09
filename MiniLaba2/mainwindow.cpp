#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include "point.h"
#include <QPaintEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    static int i = 0;
    QPoint newPoint;
    newPoint.setX(event->x());
    newPoint.setY(event->y());
    static bool create = true;
    if(i>0)
        for(int k = 0; k < points.size();k++) {
            if(points[k]->distance2(newPoint)<=5) {
                 delete points[k];
                 points.remove(k);
                 create = false;
             }
        }
    if (create)
    {
        Point *pointPE = new Point(event->x(),event->y());
        pointPE->setSize(pointPE->getSize()+i);
        if (i>4)
            pointPE->setW(2);
        points.append(pointPE);
        i++;
    }
    repaint();
    create = true;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter (this);
        for(int k = 0; k < points.size();k++) {
                points[k]->draw(&painter);
                if(k>0){
                    points[k]->connection(&painter,points[k-1]);
                }
        }
}
