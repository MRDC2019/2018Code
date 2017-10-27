#ifndef GYRO_H
#define GYRO_H

#include <Arduino.h>

class Gyro {
public:
  Gyro(int gyroPin);
  void setup();
  
  float getAngle();

private:
  // Positive Modulus helper function (n%i)
  static float PMod(float n, float i) { return n-i*floor(n/i); }
  
  int pin;
  unsigned long lastGyroRead;
  int gyroSpeed;
  float gyroAngle;
  float gyroOffset;
};

#endif /* GYRO_H */
