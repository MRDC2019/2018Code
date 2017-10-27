#pragma once
#include <stdint.h>

struct RobotIn {
	float gyroAngle;
  float sonicDistanceF;
  float sonicDistanceL;
  float sonicDistanceR;
  float sonicDistanceB;

  uint16_t shoulder;
  uint16_t wrist;

	RobotIn() :
		gyroAngle(0.0f),
    sonicDistanceF(0.0f),
    sonicDistanceL(0.0f),
    sonicDistanceR(0.0f),
    sonicDistanceB(0.0f),
    shoulder(0),
    wrist(0)
	{}
};

struct RobotOut {
	uint8_t driveFL;
	uint8_t driveBL;
	uint8_t driveFR;
	uint8_t driveBR;
	bool omni;

  uint8_t shoulder;
  uint8_t wrist;
  bool keyGrabber;

  uint8_t intake;
  bool score;
  bool doorOut;
  bool doorUp;

  bool compressor;

	RobotOut() :
		driveFL(90),
		driveBL(90),
		driveFR(90),
		driveBR(90),
		omni(true),
    shoulder(90),
    wrist(90),
    keyGrabber(true),
    intake(90),
    score(true),
    doorOut(true),
    doorUp(true),
    compressor(true)
	{}
};

