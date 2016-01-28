#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "qpainter.h"
#include <QMouseEvent>

int newWidth = 0, newHeight = 0;
std::vector<pixelBlock> pixels;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    selectedCol = QColor(0,0,0,255);

    newChoiceWindow = new NewSizeChoice;
    connect(newChoiceWindow,SIGNAL(sizeSelectionSignal(int,int)),this,SLOT(changeSize(int,int)));

    newColorWindow = new ColorChoiceWindow;
    newColorWindow->setVisible(true);
    connect(newColorWindow,SIGNAL(colorSelectionSignal(QColor)),this,SLOT(changeColor(QColor)));
    //TODO change where

    this->changeSize(30,30);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Open_triggered()
{

}

void MainWindow::on_action_New_triggered()
{
    newChoiceWindow->setVisible(true);
    newChoiceWindow->setFocus();
}

void MainWindow::changeSize(int width, int height){
    //set up grid lines
    QRect winSize = this->geometry();
    winHeight = winSize.height();
    winWidth = winSize.width();
    widthSpace = (winWidth) / width;
    heightSpace = (winHeight) / height;
    if(widthSpace > heightSpace)
        widthSpace = heightSpace;
    else if (heightSpace > widthSpace)
        heightSpace = widthSpace;

    pixels.clear();
    for (int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            pixelBlock temp;
            temp.color = QColor(0,0,0,0);
            temp.xStart = i*this->widthSpace;
            temp.yStart = j*this->heightSpace;
            temp.xLength = this->widthSpace;
            temp.yLength = this->heightSpace;

            pixels.push_back(temp);
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    painter.setPen(Qt::black);
    if(widthSpace > 0 && heightSpace > 0){
        for(int i = 0; i < pixels.size(); i++){
            pixelBlock temp = pixels[i];
            painter.fillRect(QRect(temp.xStart,temp.yStart,temp.xLength,temp.yLength),temp.color);
            painter.drawRect(QRect(temp.xStart,temp.yStart,temp.xLength,temp.yLength));
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    this->rectCollision(e->x(),e->y());
}

int MainWindow::rectCollision(int x, int y){
    if(widthSpace > 0 && heightSpace > 0){
        for(int i = 0; i < pixels.size(); i++){
            if(x > pixels[i].xStart && x <= pixels[i].xStart + pixels[i].xLength && y > pixels[i].yStart && y <= pixels[i].yStart + pixels[i].yLength){
                    pixels[i].color = selectedCol;
                    break;
            }
        }
    }
    this->update();
}

void MainWindow::changeColor(QColor color){
    selectedCol = color;
}
