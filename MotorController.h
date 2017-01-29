
#ifndef _MOTORCOLTROLLER_H_
#define _MOTORCOLTROLLER_H_ 

#include "FlowRegDefine.h"
#include "FlowSerial/FlowSerial.hpp" 

class MotorController: public FlowRegDefine{
public:
	MotorController(FlowSerial::UsbSocket& iflowSerialInterface);
	~MotorController();
	void startMotors();
	void syncRegisters();
private:
	FlowSerial::UsbSocket& flowSerialInterface;
};

#endif
