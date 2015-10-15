#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "qpainter.h"
int newWidth = 0, newHeight = 0;
std::vector<QRect> rectVect;
std::vector<QColor> colorVect;

class PaintWidget : public QWidget{
public:
    myWidget();
    void setHeightAndWidthSpace(int heightSpace, int widthSpace, int height, int width);

protected:
    void paintEvent(QPaintEvent * e);

private:
    int heightSpace, widthSpace, height, width;
};
PaintWidget * paintWidg;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    newChoiceWindow = new NewSizeChoice;
    connect(newChoiceWindow,SIGNAL(done(int,int)),this,SLOT(changeSize(int,int)));

    paintWidg = new PaintWidget();
    setCentralWidget(paintWidg);

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
}

void MainWindow::changeSize(int width, int height){
    //set up grid lines
    QRect winSize = this->geometry();
    int winHeight = winSize.height();
    int winWidth = winSize.width();
    int widthSpace = (winWidth) / width;
    int heightSpace = (winHeight - 60) / height;
    if(widthSpace > heightSpace)
        widthSpace = heightSpace;
    else if (heightSpace > widthSpace)
        heightSpace = widthSpace;
    paintWidg->setHeightAndWidthSpace(heightSpace,widthSpace,height,width);
}

void PaintWidget::setHeightAndWidthSpace(int heightSpace, int widthSpace, int height, int width){
    this->heightSpace = heightSpace;
    this->widthSpace = widthSpace;
    this->height = height;
    this->width = width;
    rectVect.clear();
    rectVect.resize(height*width);
    colorVect.clear();
    colorVect.resize(height*width);
    for(int i = 0; i < colorVect.size();i++){
        if(i%4==0)
            colorVect[i] = *(new QColor(255,0,0,255));

    }
}

void PaintWidget::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    painter.setPen(Qt::black);
    int colorIndex = 0;
    if(widthSpace > 0 && heightSpace > 0){
        for (int i = 0; i < this->width; i++){
            for(int j = 0; j < this->height; j++){
                QRect temp = QRect(i*this->widthSpace,j*this->heightSpace,widthSpace,heightSpace);
                if(colorVect[colorIndex].red()>251){
                    painter.fillRect(temp,colorVect[colorIndex]);
                    painter.drawRect(temp);
                }
                else{
                    std::cout << colorVect[colorIndex].green() << std::endl;
                    painter.fillRect(temp,Qt::white);
                    painter.drawRect(temp);
                }
                rectVect.push_back(temp);
                colorIndex++;
            }
        }
    }
}

//void MainWindow::mousePressEvent(QMouseEvent *){
//    for(int i = 0; i < rectVect.size(); i++){
//        if(match of rect)
//            colorVect[i] = QColor(255,0,0,255);
//    }
//}
