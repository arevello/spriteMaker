#ifndef COLORCHOICEWINDOW_H
#define COLORCHOICEWINDOW_H

#include <QWidget>

namespace Ui {
class ColorChoiceWindow;
}

class ColorChoiceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ColorChoiceWindow(QWidget *parent = 0);
    ~ColorChoiceWindow();
    void setLineEdits();
    void setSliders();

    int xGroupInit;
    int yGroupInit;

protected:
    void paintEvent(QPaintEvent * e);
    void mousePressEvent(QMouseEvent *);

private slots:
    void on_verticalSliderRed_sliderMoved(int position);

    void on_verticalSliderGreen_sliderMoved(int position);

    void on_verticalSliderBlue_sliderMoved(int position);

    void on_lineEditRed_textEdited(const QString &arg1);

    void on_lineEditGreen_textEdited(const QString &arg1);

    void on_lineEditBlue_textEdited(const QString &arg1);

signals:
    void colorSelectionSignal(QColor colorChoice);

private:
    Ui::ColorChoiceWindow *ui;
};

#endif // COLORCHOICEWINDOW_H
