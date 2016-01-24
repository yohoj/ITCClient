#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include<QWidget>
#include"widget.h"

namespace Ui {
class config;
}

class config : public QDialog
{
    Q_OBJECT

public:
//    explicit config(Widget *m, QWidget *parent = 0);
//    Widget*main;
    explicit config(Widget *m, QWidget *parent = 0);
    Widget *main;
    ~config();

private slots:
    void on_pushButton_clicked();

private:
    Ui::config *ui;
};

#endif // CONFIG_H
