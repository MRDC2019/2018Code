#pragma once

#include "RobotIO.h"
#include "Controls.h"
#include "../utils/PID.h"
#include "Constants.h"
#include <iostream>

class Key {
public:
	Key();
	void periodic(const RobotIn& rIn, RobotOut& rOut);

private:
	bool lastGrabKey;
};
