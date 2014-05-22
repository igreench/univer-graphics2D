#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->actionSave_Image, SIGNAL(triggered()), this, SLOT(saveImage()));
    connect(ui->actionClear, SIGNAL(triggered()), ui->widget, SLOT(clear()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::saveImage() {
    ui->widget->getImage(width(), height()).save("out.png");
}
