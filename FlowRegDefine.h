#include <stdint.h>
#include <stddef.h>

class FlowRegDefine{
public:
	FlowRegDefine(){flowReg[0] = 0; flowReg[1] = 0;}
	uint8_t flowReg[4];
	static const size_t flowRegSize = sizeof(flowReg) / sizeof(flowReg[0]);
	inline uint8_t getMotorFront(){return flowReg[0];}
	inline void setMotorFront(uint8_t motorFront){flowReg[0] = motorFront;}
	inline uint8_t getMotorBack(){return flowReg[1];}
	inline void setMotorBack(uint8_t motorBack){flowReg[1] = motorBack;}
	inline uint8_t getRotationFront(){return flowReg[2];}
	inline void setRotationFront(uint8_t rotationFront){flowReg[2] = rotationFront;}
	inline uint8_t getRotationBack(){return flowReg[3];}
	inline void setRotationBack(uint8_t rotationBack){flowReg[3] = rotationBack;}
};
