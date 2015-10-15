#include "colorchoicewindow.h"
#include "ui_colorchoicewindow.h"

ColorChoiceWindow::ColorChoiceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorChoiceWindow)
{
    ui->setupUi(this);
}

ColorChoiceWindow::~ColorChoiceWindow()
{
    delete ui;
}
