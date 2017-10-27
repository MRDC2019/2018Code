#include "Drive.h"

Drive::Drive(DriveMode _mode){
	mode = _mode;
	modeBut = false;
	autoMode = false;
	gyroCCWBut = false;
	gyroCWBut = false;
}

void Drive::periodic(const RobotIn& rIn, RobotOut& rOut){
	bool isPressed = CTRL_TOGGLE_MODE;
	if (isPressed && !modeBut){
		mode = (DriveMode)(mode + 1);
		if(mode == autonomous){
			mode = fieldCentric;
		}
		std::cout << "Mode changed to " << mode << std::endl;
	}
	modeBut = isPressed;

	bool autoBut = CTRL_AUTO_MODE;
	if (autoBut && !autoMode){
		if(mode == autonomous){
			robotCentricControl(rOut, 0, 0, 0);
			mode = prevMode;
		} else{
			prevMode = mode;
			mode = autonomous;
			directionState = front;
			std::cout << "Mode changed to autonomous" << std::endl;
		}
	}
	autoMode = autoBut;
	
	if (CTRL_COMP_ON){
		rOut.compressor = false;
	}
	if (CTRL_COMP_OFF){
		rOut.compressor = true;
	}

	//std::cout << "comp=" << rOut.compressor << std::endl;
	switch (mode){
	case fieldCentric: {
		if (CTRL_GYRO_RESET){
			gyroOffset = rIn.gyroAngle;
		}
		isPressed = CTRL_GYRO_ROT_CCW;
		if (isPressed && !gyroCCWBut){
			gyroOffset += PI / 2.0f;
		}
		gyroCCWBut = isPressed;
		isPressed = CTRL_GYRO_ROT_CW;
		if (isPressed && !gyroCWBut){
			gyroOffset -= PI / 2.0f;
		}
		gyroCWBut = isPressed;

		float gyroAngle = PMod(rIn.gyroAngle - gyroOffset, PI*2.0f);
		fieldCentricControl(rOut, CTRL_TRANS_X, CTRL_TRANS_Y, CTRL_ROT, gyroAngle);
		rOut.omni = true;
		break; }
	case robotCentric:
		robotCentricControl(rOut, CTRL_TRANS_X, CTRL_TRANS_Y, CTRL_ROT);
		rOut.omni = true;
		break;
	case tank:
		rOut.driveBL = SOut(CTRL_TANK_LEFT);
		rOut.driveFL = SOut(CTRL_TANK_LEFT);
		rOut.driveBR = Rev(SOut(CTRL_TANK_RIGHT));
		rOut.driveFR = Rev(SOut(CTRL_TANK_RIGHT));
		rOut.omni = false;
		break;
	case autonomous:
		autonomousControl(rIn, rOut);
		rOut.omni = true;
		break;
	}
}

void Drive::fieldCentricControl(RobotOut& rOut, float transX, float transY, float rot, float gyro){
	float robX = 0.0f;
	float robY = 0.0f;

	if (transX != 0.0f && transY != 0.0f){
		float transAngle = PMod(atan2(transY, transX) - gyro, PI*2.0f);
		float transMag = (fabs(transX) > fabs(transY)) ? fabs(transX) : fabs(transY);

		if (transAngle < PI / 4.0f || transAngle > 7.0f*PI / 4.0f){ // positive X is max
			robX = transMag;
			robY = robX*tan(transAngle);
		}
		else if (transAngle < 3.0f*PI / 4.0f){ // positive Y is max
			robY = transMag;
			robX = robY / tan(transAngle);
		}
		else if (transAngle < 5.0f*PI / 4.0f){ // negative X is max
			robX = -transMag;
			robY = robX*tan(transAngle);
		}
		else{ // negative Y is max
			robY = -transMag;
			robX = robY / tan(transAngle);
		}
	}

	robotCentricControl(rOut, robX, robY, rot);
}

void Drive::robotCentricControl(RobotOut& rOut, float transX, float transY, float rot){
	float backLeft = transY + transX + rot;
	float backRight = transY - transX - rot;
	float frontLeft = transY - transX + rot;
	float frontRight = transY + transX - rot;

	rOut.driveBL = SOut(Trunc(backLeft));
	rOut.driveBR = Rev(SOut(Trunc(backRight)));
	rOut.driveFL = SOut(Trunc(frontLeft));
	rOut.driveFR = Rev(SOut(Trunc(frontRight)));
}


void Drive::autonomousControl(const RobotIn& rIn, RobotOut& rOut){
	switch (directionState){
	case front:
		if(rIn.sonicDistanceF < BLOCK_DISTANCE){
			if(rIn.sonicDistanceL > rIn.sonicDistanceR){
				directionState = left;
			} else {
				directionState = right;
			}
		}
		robotCentricControl(rOut, 0, AUTO_SPEED, 0);
		break;
	case left:
		if(rIn.sonicDistanceL < BLOCK_DISTANCE){
			directionState = backLeft;
		}
		robotCentricControl(rOut, -AUTO_SPEED, 0, 0);
		break;
	case right:
		if(rIn.sonicDistanceR < BLOCK_DISTANCE){
			directionState = backRight;
		}
		robotCentricControl(rOut, AUTO_SPEED, 0, 0);
		break;
	case backLeft:
		if(rIn.sonicDistanceB < BLOCK_DISTANCE){
			directionState = exitLeft;
			exitTime = clock();
		}
		robotCentricControl(rOut, 0, -AUTO_SPEED, 0);
		break;
	case backRight:
		if(rIn.sonicDistanceB < BLOCK_DISTANCE){
			directionState = exitRight;
			exitTime = clock();
		}
		robotCentricControl(rOut, 0, -AUTO_SPEED, 0);
		break;
	case exitLeft:
		if ((clock() - exitTime)/CLOCKS_PER_SEC > EXIT_DELAY){
			robotCentricControl(rOut, 0, 0, 0);
			mode = prevMode;
		} else {
			robotCentricControl(rOut, -AUTO_SPEED, 0, 0);
		}
		break;
	case exitRight:
		if((clock() - exitTime) / CLOCKS_PER_SEC > EXIT_DELAY){
			robotCentricControl(rOut, 0, 0, 0);
			mode = prevMode;
		} else {
			robotCentricControl(rOut, AUTO_SPEED, 0, 0);
		}
		break;
	}
}
