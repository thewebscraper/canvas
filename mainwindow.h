#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "imgproc.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_brightness_valueChanged (int value);
    void on_contrast_valueChanged   (int value);
    void on_saturation_valueChanged (int value);
    void on_hue_valueChanged        (int value);
    void on_zoom_valueChanged       (int value);

private:
    Ui::MainWindow *ui;
    ImgProc * imgproc;
};

#endif // MAINWINDOW_H
