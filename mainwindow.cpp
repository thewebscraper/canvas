#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imgproc = new ImgProc ();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_brightness_valueChanged(int value)
{
    QImage img;
    img = imgproc->adjust_contrast_brightness (1, value);

    int width  = ui->canvas->width ();
    int height = ui->canvas->height ();

    QPixmap pixmap = QPixmap::fromImage(img).scaled(
            QSize(width, height),
            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui->canvas->setScaledContents(false);
    ui->canvas->setPixmap(pixmap);
}

void MainWindow::on_contrast_valueChanged(int value)
{
    QImage img;

    // contrast is 1 - 1.5, step is 0.05
    // TODO: step value for contrast
    img = imgproc->adjust_contrast_brightness ((value * 5) / 100, 1);

    int width  = ui->canvas->width ();
    int height = ui->canvas->height ();

    QPixmap pixmap = QPixmap::fromImage(img).scaled(
            QSize(width, height),
            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui->canvas->setScaledContents(false);
    ui->canvas->setPixmap(pixmap);
}

void MainWindow::on_saturation_valueChanged(int value)
{
    QImage img;

    img = imgproc->adjust_saturation (value);

    int width  = ui->canvas->width ();
    int height = ui->canvas->height ();

    QPixmap pixmap = QPixmap::fromImage(img).scaled(
            QSize(width, height),
            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui->canvas->setScaledContents(false);
    ui->canvas->setPixmap(pixmap);
}


void MainWindow::on_hue_valueChanged(int value)
{
    QImage img;

    img = imgproc->adjust_hue (value);

    int width  = ui->canvas->width ();
    int height = ui->canvas->height ();

    QPixmap pixmap = QPixmap::fromImage(img).scaled(
            QSize(width, height),
            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui->canvas->setScaledContents(false);
    ui->canvas->setPixmap(pixmap);
}

void MainWindow::on_zoom_valueChanged(int value)
{
    QImage img;
    double width  = (ui->canvas->width  () * value) / 100;
    double height = (ui->canvas->height () * value) / 100;

    img = imgproc->get ();

    QPixmap pixmap = QPixmap::fromImage(img).scaled(
            QSize(width, height),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->canvas->setScaledContents(false);
    ui->canvas->setPixmap(pixmap);
}
