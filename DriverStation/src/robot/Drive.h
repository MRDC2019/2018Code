#pragma once

#include "RobotIO.h"
#include "Controls.h"
#include "Constants.h"
#include <iostream>
#include <cmath>
#include <ctime>

class Drive {
public:
	enum DriveMode { fieldCentric, robotCentric, tank, autonomous };
	enum direction { front, left, right, backLeft, backRight, exitLeft, exitRight };
	Drive(DriveMode _mode);
	void periodic(const RobotIn& rIn, RobotOut& rOut);

	// Positive Modulus (n%i)
	static float PMod(float n, float i) { return n - i*floor(n / i); }
	// truncates to [-1.0, 1.0]
	static float Trunc(float out) {
		if (out > 1.0f)  return  1.0f;
		if (out < -1.0f) return -1.0f;
		return out;
	}
	// converts from [-1.0, 1.0] to [0,180] for the arduino
	static char SOut(float out) { return (char)((out + 1.0f)*90.0f); }
	// reverses from [180,0] to [0,180] for the arduino
	static char Rev(char out) { return 180 - out; }

private:
	void fieldCentricControl(RobotOut& rOut, float transX, float transY, float rot, float gyro);
	void robotCentricControl(RobotOut& rOut, float transX, float transY, float rot);
	void autonomousControl(const RobotIn& rIn, RobotOut& rOut);

	DriveMode mode;
	float gyroOffset;

	// button states
	bool modeBut;
	bool autoMode;
	bool gyroCCWBut;
	bool gyroCWBut;

	DriveMode prevMode;
	direction directionState;
	clock_t exitTime;

};
