#include "colorchoicewindow.h"
#include "ui_colorchoicewindow.h"
#include <iostream>
#include "qpainter.h"
#include <QMouseEvent>
#include "mainwindow.h"
#include <vector>

std::vector<pixelBlock> colorChoices;
pixelBlock displayBlock;

ColorChoiceWindow::ColorChoiceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorChoiceWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    colorChoices.clear();
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 6; j++){
            pixelBlock temp;
            temp.xStart = 10+i*20;
            temp.yStart = 10+j*20;
            temp.xLength = 20;
            temp.yLength = 20;
            temp.color = QColor(255,0,0,255); //TODO find gradient
            colorChoices.push_back(temp);
        }
    }

    displayBlock.xStart = 60;
    displayBlock.yStart = 150;
    displayBlock.xLength = 60;
    displayBlock.yLength = 60;
    displayBlock.color = QColor(0,0,0,255);

    ui->verticalSliderRed->setValue(0);
    ui->verticalSliderGreen->setValue(0);
    ui->verticalSliderBlue->setValue(0);

    ui->lineEditRed->setText("0");
    ui->lineEditRed->setValidator(new QIntValidator(0,255,this));
    ui->lineEditGreen->setText("0");
    ui->lineEditGreen->setValidator(new QIntValidator(0,255,this));
    ui->lineEditBlue->setText("0");
    ui->lineEditBlue->setValidator(new QIntValidator(0,255,this));
}

ColorChoiceWindow::~ColorChoiceWindow()
{
    delete ui;
}

void ColorChoiceWindow::setLineEdits(){
    ui->lineEditRed->setText(QString::number(displayBlock.color.red()));
    ui->lineEditGreen->setText(QString::number(displayBlock.color.green()));
    ui->lineEditBlue->setText(QString::number(displayBlock.color.blue()));
}

void ColorChoiceWindow::setSliders(){
    ui->verticalSliderRed->setValue((float)(displayBlock.color.red()/255)*100);
    ui->verticalSliderGreen->setValue((float)(displayBlock.color.green()/255)*100);
    ui->verticalSliderBlue->setValue((float)(displayBlock.color.blue()/255)*100);
}

void ColorChoiceWindow::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    painter.setPen(Qt::black);

    //color choice blocks
    for(int i = 0; i < colorChoices.size(); i++){
        pixelBlock temp = colorChoices[i];
        painter.fillRect(QRect(temp.xStart,temp.yStart,temp.xLength,temp.yLength),temp.color);
        painter.drawRect(QRect(temp.xStart,temp.yStart,temp.xLength,temp.yLength));
    }

    painter.fillRect(QRect(displayBlock.xStart,displayBlock.yStart,displayBlock.xLength,displayBlock.yLength),displayBlock.color);
}

void ColorChoiceWindow::mousePressEvent(QMouseEvent *e){
    for(int i = 0; i < colorChoices.size(); i++){
        if(e->x() > colorChoices[i].xStart && e->x() <= colorChoices[i].xStart + colorChoices[i].xLength && e->y() > colorChoices[i].yStart && e->y() <= colorChoices[i].yStart + colorChoices[i].yLength){
                //change display color
                displayBlock.color = colorChoices[i].color;

                //change sliders and textboxes
                setSliders();
                setLineEdits();

                //set choice as new color in main
                emit colorSelectionSignal(displayBlock.color);
                break;
        }
    }
    this->update();
}

void ColorChoiceWindow::on_verticalSliderRed_sliderMoved(int position)
{
    displayBlock.color = QColor(((float)position/100)*255,displayBlock.color.green(),displayBlock.color.blue(),255);
    emit colorSelectionSignal(displayBlock.color);
    this->update();
    setLineEdits();
}

void ColorChoiceWindow::on_verticalSliderGreen_sliderMoved(int position)
{
    displayBlock.color = QColor(displayBlock.color.red(),((float)position/100)*255,displayBlock.color.blue(),255);
    emit colorSelectionSignal(displayBlock.color);
    this->update();
    setLineEdits();
}

void ColorChoiceWindow::on_verticalSliderBlue_sliderMoved(int position)
{
    displayBlock.color = QColor(displayBlock.color.red(),displayBlock.color.green(),((float)position/100)*255,255);
    emit colorSelectionSignal(displayBlock.color);
    this->update();
    setLineEdits();
}

void ColorChoiceWindow::on_lineEditRed_textEdited(const QString &arg1)
{
    int temp = arg1.toInt();
    displayBlock.color = QColor(temp,displayBlock.color.green(),displayBlock.color.blue());
    emit colorSelectionSignal(displayBlock.color);
    this->update();
    setSliders();
}

void ColorChoiceWindow::on_lineEditGreen_textEdited(const QString &arg1)
{
    int temp = arg1.toInt();
    displayBlock.color = QColor(displayBlock.color.red(),temp,displayBlock.color.blue());
    emit colorSelectionSignal(displayBlock.color);
    this->update();
    setSliders();
}

void ColorChoiceWindow::on_lineEditBlue_textEdited(const QString &arg1)
{
    int temp = arg1.toInt();
    displayBlock.color = QColor(displayBlock.color.red(),displayBlock.color.green(),temp);
    emit colorSelectionSignal(displayBlock.color);
    this->update();
    setSliders();
}
