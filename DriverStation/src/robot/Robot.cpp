#include "Robot.h"

Robot::Robot() :
	drive(DRIVE_MODE),
	ball(),
	key()
{
	
}

void Robot::periodic(const RobotIn& rIn, RobotOut& rOut){
	drive.periodic(rIn, rOut);
	ball.periodic(rIn, rOut);
	key.periodic(rIn, rOut);
}
