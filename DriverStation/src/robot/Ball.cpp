#include "Ball.h"

Ball::Ball() {
	scoring = false;
	lastGrabDoorOutKey = false;
	lastGrabDoorUpKey = false;
}

void Ball::periodic(const RobotIn& rIn, RobotOut& rOut) {

	// If ball intake button is pressed (create in Controls.h), toggle intake motor
	if (CTRL_INTAKE) {
		rOut.intake = INTAKE_ON;
	} else if (CTRL_INTAKE_REV){
		rOut.intake = INTAKE_REV;
	} else {
		rOut.intake = INTAKE_OFF;
	}
	//rOut.intake = uint8_t((CTRL_MAN_WRIST + 1) * 90);

	// If raise door button is pressed, toggle solenoid
	if (CTRL_DOOR_OUT && !lastGrabDoorOutKey && !(!rOut.doorOut && !rOut.doorUp)) {
		rOut.doorOut = !rOut.doorOut;
	}
	lastGrabDoorOutKey = CTRL_DOOR_OUT;

	if(CTRL_DOOR_UP && !lastGrabDoorUpKey) {
		rOut.doorUp = !rOut.doorUp;
	}
	lastGrabDoorUpKey = CTRL_DOOR_UP;

	// If score button, toggle score motor for some period of time
	if (CTRL_SCORE && !scoring) {
		rOut.score = !rOut.score;
	}
	scoring = CTRL_SCORE;


}
