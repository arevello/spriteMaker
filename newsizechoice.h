#ifndef NEWSIZECHOICE_H
#define NEWSIZECHOICE_H

#include <QWidget>

namespace Ui {
class NewSizeChoice;
}

class NewSizeChoice : public QWidget
{
    Q_OBJECT

public:
    explicit NewSizeChoice(QWidget *parent = 0);
    ~NewSizeChoice();

private slots:
    void on_btnConfirm_clicked();

    void on_btnCancel_clicked();

signals:
    void done(int width, int height);

private:
    Ui::NewSizeChoice *ui;
};

#endif // NEWSIZECHOICE_H
