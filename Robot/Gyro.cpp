#include <SPI.h>
#include "Gyro.h"

Gyro::Gyro(int gyroPin){
  pin = gyroPin;
  lastGyroRead = 0;
  gyroSpeed = 0;
  gyroAngle = 0.0;
  gyroOffset = 0.0;
}

void Gyro::setup(){
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16); 
  SPI.setDataMode(SPI_MODE0);
}

float Gyro::getAngle(){
  unsigned long readTime = micros();
  if(lastGyroRead == 0)
    lastGyroRead = readTime;
  
  digitalWrite(pin, LOW);
  int result = SPI.transfer(0x20);
  result = result << 8 | SPI.transfer(0x00);
  int result2 = SPI.transfer(0x00) >>2;
  SPI.transfer(0x00);
  result = result << 6 | result2;
  digitalWrite(pin, HIGH);

  // low pass filter
  gyroSpeed = (gyroSpeed)*0.5 + result*(1 - 0.5);
  // gyro returns in units of 80 LSB/deg/sec

  if(abs(gyroSpeed) > 40){
    gyroAngle += gyroSpeed/80.0*(readTime-lastGyroRead)/1000000.0;
    //Serial.println(gyroSpeed);
  }
  lastGyroRead = readTime;
  
  return PMod(gyroAngle - gyroOffset, PI*2.0);
}
