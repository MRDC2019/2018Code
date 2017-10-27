#pragma once

#include "RobotIO.h"
#include "Controls.h"
#include "Constants.h"

#include <ctime>

class Ball {
public:
	Ball();
	void periodic(const RobotIn& rIn, RobotOut& rOut);

private:
	bool scoring;
	bool lastGrabDoorOutKey;
	bool lastGrabDoorUpKey;
};
