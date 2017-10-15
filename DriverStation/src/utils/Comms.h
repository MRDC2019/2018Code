#pragma once

#define BAUD_RATE	9600
#define TIMEOUT		500
#define BUF_SIZE    2048

#include "../robot/RobotIO.h"
#include "CRC8.h"
#include <serial/serial.h>
#include <iostream>
#include <cmath>
#include <windows.h>
using namespace serial;

class Comms {
public:
    // Public functions should not call each other. Otherwise deadlock
	Comms();

    bool read();
    bool write();

    int read(unsigned char * buf, int bufsize);
    int write(unsigned char * buf, int len);

    void begin();
    void end();

    const RobotIn& getRobotIn();
    RobotOut& getRobotOut();
    void setRobotOut(const RobotOut &newStruct);

	bool maintainConnection();
    bool isEnded();
private:
    // private functions should not take lock
	Serial* serial;
    RobotOut out;
    RobotIn in;
    CRC8 crc8;

	unsigned char outBuf[15];
	uint8_t readBuf[BUF_SIZE];
	size_t bufferIndex;
	void setOutBuf();

	void enumerate_ports();
};
