#include "Key.h"

Key::Key()
{
	lastGrabKey = false;
}

void Key::periodic(const RobotIn& rIn, RobotOut& rOut){
	double shoulder = CTRL_MAN_SHOULDER*MAN_SHOULDER_SPEED;
	if (!CTRL_STOP_HOLD){
		double holdOffset = 0.25*sin((rIn.shoulder - SHOULDER_MID)*SHOULDER_RAD);
		if (holdOffset > 0.2)
			holdOffset = 0.2;
		if (holdOffset < -0.2)
			holdOffset = -0.2;
		shoulder += holdOffset;
	}
	rOut.shoulder = uint8_t((shoulder + 1) * 90);
	//std::cout << "in = " << rIn.shoulder << " out = " << (int)rOut.shoulder << std::endl;
	rOut.wrist = uint8_t((CTRL_MAN_WRIST*MAN_WRIST_SPEED + 1) * 90);
	//std::cout << "wrist = " << (int)rOut.wrist << std::endl;

	// grab key
	bool isPressed = CTRL_GRAB_KEY;
	if(isPressed && !lastGrabKey){
		rOut.keyGrabber = !rOut.keyGrabber;
	}
	lastGrabKey = isPressed;
}
