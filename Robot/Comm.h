#ifndef COMM_H
#define COMM_H

#include <stdint.h>
#include <Arduino.h>
#include "RobotIO.h"
#include "Config.h"

/**
 * The packet format:
 * -- To PC:              Data
 *          |0xff|    |    |    |    |CRC |0xee|0xdd|
 * -- From PC:
 *          |0xff| FL | BL | FR | BR   |omni|CRC |0xdd|
 * -- Any length:
 *          |0xff| --- data --- |CRC |len |0xdd|
 */
class Comm {
private:
  RobotIn *_in_struct;
  RobotOut *_out_struct;
  unsigned char read_buf[128];
  unsigned char outBuf[26];
  int bufferIndex;
  long failures;
  long resetStart;
  
public:
  Comm(RobotIn *in_struct, RobotOut *out_struct) : _in_struct(in_struct), 
                                                   _out_struct(out_struct){}
  // time out is measured in frames
  void begin(long baud_rate);

  void checkReset();
  /**
   * Basically, write out to PC through serial,
   * and read from serial, update the internal servo values.
   */
  void write();
  bool read();

  int write(unsigned char * msg, int len);
  int read(unsigned char * buf, int bufsize);
  
  void setOutBuf();
  long getFailures() { return failures; }
  ~Comm();

private:
  void _set_timer(uint32_t rate);
  void _rm_timer();
  uint8_t _crc8(uint8_t *data, int len);
};

#endif /* COMM_H */
