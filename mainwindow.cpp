#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simulationwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() {
    int numPassengers = ui->spinBoxPassengers->value();
    int numFloors = ui->spinBoxFloors->value();
    int numElevators = ui->spinBoxElevators->value();

    SimulationWindow *simWindow = new SimulationWindow(numPassengers, numFloors, numElevators);
    simWindow->show();
    this->hide();
}

