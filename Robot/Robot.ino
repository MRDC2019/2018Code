#include "Config.h"

#include "RobotIO.h"
#include "Comm.h"

#include <Servo.h>
#include <SPI.h>
#include "Gyro.h"
#include <NewPing.h>

// Robot input and output structs
RobotIn in;
RobotOut out;
Comm comm(&in, &out);

// Drivetrain IO
Gyro gyro(GYRO_PIN);
Servo driveFL;
Servo driveBL;
Servo driveFR;
Servo driveBR;
int jumpPin = JUMP_PIN;
NewPing sonicFront(SONIC_T_F_PIN, SONIC_E_F_PIN) ;
NewPing sonicLeft(SONIC_T_L_PIN, SONIC_E_L_PIN);
NewPing sonicRight(SONIC_T_R_PIN, SONIC_E_R_PIN);
NewPing sonicBack(SONIC_T_B_PIN, SONIC_E_B_PIN);

// Key IO
Servo shoulderMotor;
Servo wristMotor;
int shoulderPotPin = SHOULDER_POT_PIN;
int wristPotPin = WRIST_POT_PIN;
int keyGrabberPin = KEY_GRABBER_PIN;

// Ball IO
Servo intake;
int scorePin = SCORE_PIN;
int doorOutPin = DOOR_OUT_PIN;
int doorUpPin = DOOR_UP_PIN;

int compressorPin = COMPRESSOR_PIN;

// timing vars
unsigned long cycle;
unsigned long start;

void setup() {
  // init Drivetrain IO
  gyro.setup();
  driveFL.attach(DRIVE_FL_PIN);
  driveBL.attach(DRIVE_BL_PIN);
  driveFR.attach(DRIVE_FR_PIN);
  driveBR.attach(DRIVE_BR_PIN);
  pinMode(jumpPin, OUTPUT);
  digitalWrite(jumpPin, HIGH);
  
  // init Key IO
  shoulderMotor.attach(SHOULDER_MOTOR_PIN);
  wristMotor.attach(WRIST_MOTOR_PIN);
  pinMode(keyGrabberPin, OUTPUT);
  digitalWrite(keyGrabberPin, HIGH);

  // init Ball IO
  intake.attach(INTAKE_PIN);
  pinMode(scorePin, OUTPUT);
  digitalWrite(scorePin, HIGH);
  pinMode(doorOutPin, OUTPUT);
  digitalWrite(doorOutPin, HIGH);
  pinMode(doorUpPin, OUTPUT);
  digitalWrite(doorUpPin, HIGH);
  
  pinMode(compressorPin, OUTPUT);
  digitalWrite(compressorPin, HIGH);

  cycle = 0;
  start = millis();
  
  comm.begin(BAUD_RATE);
  Serial.begin(9600);
}

void loop() {
  // Get Robot input values and assign then to RobotIn
  //write distances to in struct in inches
  switch(cycle%4){
  case 0:
    in.sonicDistanceF = sonicFront.ping_in(100);
    break;
  case 1:
    in.sonicDistanceL = sonicLeft.ping_in(100);
    break;
  case 2:
    in.sonicDistanceR = sonicRight.ping_in(100);
    break;
  case 3:
    in.sonicDistanceB = sonicBack.ping_in(100);
    break;
  }
  
  in.gyroAngle = gyro.getAngle();
  
  in.shoulder = analogRead(shoulderPotPin);
  //Serial.println(in.shoulder);
  in.wrist = analogRead(wristPotPin);

  // Write inputs to PC
  comm.write();
  int delayTime = 16 - (millis() - start);
  if(delayTime<0)
    delayTime = 0;
  delay(delayTime);
  //Serial.print("cycle time = "); Serial.println(millis()-start);
  start = millis();

  comm.checkReset();

  // Read output values to IO struct
  if(comm.read()){
    // Write RobotOut values to outputs
    driveFL.write(out.driveFL);
    driveBL.write(out.driveBL);
    driveFR.write(out.driveFR);
    driveBR.write(out.driveBR);
    digitalWrite(jumpPin, out.omni);

    shoulderMotor.write(out.shoulder);
    wristMotor.write(out.wrist);
    digitalWrite(keyGrabberPin, out.keyGrabber);
    
    intake.write(out.intake);
    digitalWrite(scorePin, out.score);
    digitalWrite(doorOutPin, out.doorOut);
    digitalWrite(doorUpPin, out.doorUp);
    digitalWrite(compressorPin, out.compressor);
  }else if(comm.getFailures() > 6){
    driveFL.write(90);
    driveBL.write(90);
    driveFR.write(90);
    driveBR.write(90);
    shoulderMotor.write(90);
    wristMotor.write(90);
    intake.write(90);
  }

  cycle++;
}

