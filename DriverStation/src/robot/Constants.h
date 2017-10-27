// Default drive mode
#define DRIVE_MODE              Drive::robotCentric

// Drive Constants
#define PI                      3.14159265358979323846f
#define BLOCK_DISTANCE          3
#define AUTO_SPEED              0.5
#define EXIT_DELAY              5

// Servo positions used in Ball.cpp
#define INTAKE_ON               170
#define INTAKE_OFF              90
#define INTAKE_REV              30
#define SCORE_POSN              false
#define HOLD_POSN               true

// Times used in Ball.cpp
#define HOLD_TIME               5 // seconds

// Key Mechanism Constants
#define SHOULDER_MID			480
#define SHOULDER_RAD			(1.0/(800-SHOULDER_MID) * PI/2.0) // quarter rotation number
#define MAN_SHOULDER_SPEED		0.15
#define MAN_WRIST_SPEED			0.5