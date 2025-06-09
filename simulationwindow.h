#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QWidget>

namespace Ui {
class SimulationWindow;
}

class SimulationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationWindow(int passengers, int floors, int elevators, QWidget *parent = nullptr);
    ~SimulationWindow();

    // Elevator Simulation
    void assignElevator(int floor, QString direction);
    void logEvent(QString message);
    void moveElevator(int targetFloor);
    void updateFloorVisibility();


    // Doors
    void openDoor();
    void closeDoor();

    // Safety Functions
    void activateFireProtocol();
    void triggerEmergencyHelp();
    void handlePowerOutage();
    void detectObstruction();

    // Timer
    void updateSimulationTime();
    QTimer *simulationTimer;
    int simulationTime;

private slots:
    // Event Buttons
    void on_floor1Up_clicked();

    void on_floor2Up_clicked();

    void on_floor2Down_clicked();

    void on_floor3Up_clicked();

    void on_floor3Down_clicked();

    void on_floor4Up_clicked();

    void on_floor5Down_clicked();

    void on_destFloor1_clicked();

    void on_destFloor2_clicked();

    void on_destFloor3_clicked();

    void on_destFloor4_clicked();

    void on_destFloor5_clicked();

    void on_btnOpenDoor_clicked();

    void on_btnCloseDoor_clicked();

    void on_btnHelp_clicked();

    void on_btnFire_clicked();

    void on_btnDoorObstacle_clicked();

    void on_btnPowerOutage_clicked();

    void on_floor4Down_clicked();

private:
    Ui::SimulationWindow *ui;

    // Declaring Variables
    int numPassengers;
    int numFloors;
    int numElevators;
};

#endif // SIMULATIONWINDOW_H
