#include "newsizechoice.h"
#include "ui_newsizechoice.h"
extern int newWidth, newHeight;

NewSizeChoice::NewSizeChoice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewSizeChoice)
{
    ui->setupUi(this);
    this->setVisible(false);
}

NewSizeChoice::~NewSizeChoice()
{
    delete ui;
}

void NewSizeChoice::on_btnConfirm_clicked()
{
    if(ui->txtHeight->text().toInt() < 200){
        newHeight = ui->txtHeight->text().toInt();
    }
    if(ui->txtWidth->text().toInt() < 200){
        newWidth = ui->txtWidth->text().toInt();
    }
    emit done(newWidth,newHeight);
    ui->txtHeight->setText("");
    ui->txtWidth->setText("");
    this->setVisible(false);
}

void NewSizeChoice::on_btnCancel_clicked()
{
    ui->txtHeight->setText("");
    ui->txtWidth->setText("");
    this->setVisible(false);
}
