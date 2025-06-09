#include "simulationwindow.h"
#include "ui_simulationwindow.h"
#include <QTimer>

SimulationWindow::SimulationWindow(int passengers, int floors, int elevators, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationWindow),
    numPassengers(passengers),
    numFloors(floors),
    numElevators(elevators)
{
    ui->setupUi(this);
    updateFloorVisibility();

    logEvent("Simulation initialized with " + QString::number(numPassengers) + " passengers, " +
    QString::number(numFloors) + " floors, and " + QString::number(numElevators) + " elevators.");

    // Time Initialized
    simulationTime = 0;
    simulationTimer = new QTimer(this);
    connect(simulationTimer, &QTimer::timeout, this, &SimulationWindow::updateSimulationTime);
    // Update every second
    simulationTimer->start(1000);

}

SimulationWindow::~SimulationWindow()
{
    delete ui;
}


// ELEVATOR SIMULATION FUNCTIONS //

void SimulationWindow::logEvent(QString message) {
    ui->eventLog->append(message);
}

void SimulationWindow::updateFloorVisibility() {
    // Disable all floors greater than the selected number of floors
    if (numFloors < 5) {
        ui->floor5Down->setEnabled(false);
    }
    if (numFloors < 4) {
        ui->floor4Up->setEnabled(false);
        ui->floor4Down->setEnabled(false);
    }
    if (numFloors < 3) {
        ui->floor3Up->setEnabled(false);
        ui->floor3Down->setEnabled(false);
    }
    if (numFloors < 2) {
        ui->floor2Up->setEnabled(false);
        ui->floor2Down->setEnabled(false);
    }

    // Disable floors if simulation number of floors is less than the selected
       ui->destFloor3->setEnabled(numFloors >= 3);
       ui->destFloor4->setEnabled(numFloors >= 4);
       ui->destFloor5->setEnabled(numFloors >= 5);
}


void SimulationWindow::assignElevator(int floor, QString direction) {
    logEvent("Assigning an elevator to Floor " + QString::number(floor) + " (" + direction + ").");

    // Find the closest elevator
    int closestElevator = 1;
    int minDistance = abs(ui->elevator1Floor->text().toInt() - floor);

    if (abs(ui->elevator2Floor->text().toInt() - floor) < minDistance) {
        closestElevator = 2;
        minDistance = abs(ui->elevator2Floor->text().toInt() - floor);
    }

    if (abs(ui->elevator3Floor->text().toInt() - floor) < minDistance) {
        closestElevator = 3;
    }

    logEvent("Elevator " + QString::number(closestElevator) + " is moveing to Floor " + QString::number(floor) + ".");

    // Update UI for the selected elevator
    if (closestElevator == 1) {
        ui->elevator1Status->setText("Status: Moving");
        ui->elevator1Floor->setText("Floor: " + QString::number(floor));
    } else if (closestElevator == 2) {
        ui->elevator2Status->setText("Status: Moving");
        ui->elevator2Floor->setText("Floor: " + QString::number(floor));
    } else if (closestElevator == 3) {
        ui->elevator3Status->setText("Status: Moving");
        ui->elevator3Floor->setText("Floor: " + QString::number(floor));
    }
}


void SimulationWindow::moveElevator(int targetFloor) {
    logEvent("Elevator is moving to Floor " + QString::number(targetFloor) + ".");

    // Get  the current floor
    int currentFloor = ui->elevator1Floor->text().split(": ")[1].toInt();

    // Setup QTimer to display seconds past
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (currentFloor < targetFloor) {
            currentFloor++;
        } else if (currentFloor > targetFloor) {
            currentFloor--;
        }

        // Update floor display
        ui->elevator1Floor->setText("Floor: " + QString::number(currentFloor));

        // Stop timer when it reaches the target
        if (currentFloor == targetFloor) {
            timer->stop();
          // Clean up timer memory
            timer->deleteLater();
            ui->elevator1Status->setText("Status: Idle");
            logEvent("Elevator arrived at Floor " + QString::number(targetFloor) + ".");
        }
    });

    // Move floor by floor every 1 second
    timer->start(1000);
}

void SimulationWindow::openDoor() {
    logEvent("Elevator doors are opening.");
    ui->elevator1Doors->setText("Doors: Open");

    // Keep doors open for 3 seconds before automatically closing
    QTimer::singleShot(3000, this, [=]() {
        closeDoor();
    });
}


void SimulationWindow::closeDoor() {
    logEvent("Elevator doors are closing.");
    ui->elevator1Doors->setText("Doors: Closed");
}

void SimulationWindow::updateSimulationTime() {
    simulationTime++;
    ui->lcdTimer->display(simulationTime);
}

// SAFETY FUNCTIONS //

void SimulationWindow::activateFireProtocol() {
    logEvent("Fire alarm triggered! Moving all elevators to a safe floor.");

    // Move all elevators to Floor 1 (safe floor)
    moveElevator(1);

    logEvent("Passengers are asked to evacuate.");
}

void SimulationWindow::triggerEmergencyHelp() {
    logEvent("Help button pressed. Connecting to building safety...");

    // Simulate delay before connecting
    QTimer::singleShot(5000, this, [=]() {
        logEvent("No response from safety. Calling 911.");
    });
}

void SimulationWindow::handlePowerOutage() {
    logEvent("Power outage detected! Moving all elevators to the nearest safe floor.");

    // Move all elevators to Floor 2 (backup power floor)
    moveElevator(2);

    logEvent("Passengers are advised to exit the elevator.");
}


void SimulationWindow::detectObstruction() {
    logEvent("Door obstacle detected! Reopening doors.");

    openDoor();

    QTimer::singleShot(3000, this, [=]() {
        logEvent("Warning: Repeated door obstruction detected.");
    });
}



// BUTTON EVENTS //

void SimulationWindow::on_floor1Up_clicked()
{
    logEvent("Passenger requested an elevator at Floor 1 (Up).");
    assignElevator(1, "up");
}


void SimulationWindow::on_floor2Up_clicked()
{
    logEvent("Passenger requested an elevator at Floor 2 (Up).");
    assignElevator(2, "up");
}


void SimulationWindow::on_floor2Down_clicked()
{
    logEvent("Passenger requested an elevator at Floor 2 (Down).");
    assignElevator(2, "down");
}


void SimulationWindow::on_floor3Up_clicked()
{
    logEvent("Passenger requested an elevator at Floor 3 (Up).");
    assignElevator(3, "up");
}


void SimulationWindow::on_floor3Down_clicked()
{
    logEvent("Passenger requested an elevator at Floor 3 (Down).");
    assignElevator(3, "down");
}


void SimulationWindow::on_floor4Up_clicked()
{
    logEvent("Passenger requested an elevator at Floor 4 (Up).");
    assignElevator(4, "up");
}

void SimulationWindow::on_floor4Down_clicked()
{
    logEvent("Passenger requested an elevator at Floor 4 (Down).");
    assignElevator(4, "down");
}


void SimulationWindow::on_floor5Down_clicked()
{
    logEvent("Passenger requested an elevator at Floor 5 (Down).");
    assignElevator(5, "down");
}


void SimulationWindow::on_destFloor1_clicked()
{
    logEvent("Passenger inside elevator selected Floor 1.");
    moveElevator(1);
}

void SimulationWindow::on_destFloor2_clicked()
{
    logEvent("Passenger inside elevator selected Floor 2.");
    moveElevator(2);
}


void SimulationWindow::on_destFloor3_clicked()
{
    logEvent("Passenger inside elevator selected Floor 3.");
    moveElevator(3);
}


void SimulationWindow::on_destFloor4_clicked()
{
    logEvent("Passenger inside elevator selected Floor 4.");
    moveElevator(4);
}


void SimulationWindow::on_destFloor5_clicked()
{
    logEvent("Passenger inside elevator selected Floor 5.");
    moveElevator(5);
}


void SimulationWindow::on_btnOpenDoor_clicked()
{
    openDoor();
}


void SimulationWindow::on_btnCloseDoor_clicked()
{
    closeDoor();
}


void SimulationWindow::on_btnHelp_clicked()
{
     triggerEmergencyHelp();
}


void SimulationWindow::on_btnFire_clicked()
{
     activateFireProtocol();
}


void SimulationWindow::on_btnDoorObstacle_clicked()
{
     detectObstruction();
}



void SimulationWindow::on_btnPowerOutage_clicked()
{
    handlePowerOutage();
}




