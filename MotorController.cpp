
#include <unistd.h>   //For usleep specific for this example
#include "MotorController.h"

MotorController::MotorController(FlowSerial::UsbSocket& iflowSerialInterface):
	flowSerialInterface(iflowSerialInterface)
{
	flowSerialInterface.startUpdateThread();
	setMotorFront(0);
	setMotorBack(0);
	setRotationFront(90);
	setRotationBack(90);
	syncRegisters();
}

MotorController::~MotorController(){
	setMotorFront(36);
	setMotorBack(36);
	syncRegisters();
}

void MotorController::startMotors(){
	setMotorFront(180);
	setMotorBack(180);
	syncRegisters();
	usleep(3000000);

	setMotorFront(30);
	setMotorBack(30);
	syncRegisters();
	usleep(3000000);
}

void MotorController::syncRegisters(){
	flowSerialInterface.writeToPeer(0, flowReg, flowRegSize);
}
