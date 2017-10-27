#include "Comm.h"
#include <util/crc16.h>

void Comm::begin(long baud_rate) {
  Serial2.begin(baud_rate);
  Serial1.begin(9600);
  pinMode(COMMS_RESET_PIN, OUTPUT);
  digitalWrite(COMMS_RESET_PIN, HIGH);
  failures = 0;
  resetStart = 0;
  bufferIndex = 0;
}

void Comm::checkReset(){
  if(millis()-resetStart > 500 && resetStart != 0){
    Serial1.println("Reset");
    digitalWrite(COMMS_RESET_PIN, HIGH);
    resetStart = 0;
  }else if(Serial1.available()){
    char cmd = Serial1.read();
    if(cmd == '1'){
      Serial1.println("Received");
      digitalWrite(COMMS_RESET_PIN, LOW);
      resetStart = millis();
      failures = 100;
    }
  }
}

bool Comm::read(){
  //Serial.println(Serial2.available());
  if (Serial2.available() < READ_LEN-bufferIndex){
    failures++;
    return false;
  }
  
  if(Serial2.readBytes(read_buf + bufferIndex, READ_LEN-bufferIndex) < READ_LEN-bufferIndex){
    bufferIndex = 0;
    failures++;
    return false;
  }
  bufferIndex = 0;
  
  // if the start byte is not first we have a problem
  while(read_buf[0] != 0xdd || read_buf[READ_LEN-1] != _crc8(&read_buf[1], READ_LEN-2)){
    // attempt to recover
    int i;
    for(i=1; i<READ_LEN; i++)
      if(read_buf[i] == 0xdd)
        break;
    if(i >= READ_LEN){
      // recovery failed, attempt another read in case we have more bytes in the buffer
      return Comm::read();
    }else{
      // found possible start byte, attempt to read rest of message
      for(int j=i; j<READ_LEN; j++){
        read_buf[j-i] = read_buf[j];
      }
      if(Serial.available() >= i){
        // rest of message available
        if(Serial.readBytes(&read_buf[READ_LEN-i], i) < i){
          //Serial.println("didn't read rest of READ_LEN");
          failures++;
          return false;
        }
      }else{
        // wait for rest of message
        // we have to check next function call because this function cannot be blocking
        bufferIndex = READ_LEN - i;
        //Serial.println("wait for rest of message");
        failures++;
        return false;
      }
    }
  }

  _out_struct->driveFL   = read_buf[1];     //TODO: potential race condition. No synchronization primitives
  _out_struct->driveBL   = read_buf[2];
  _out_struct->driveFR   = read_buf[3];
  _out_struct->driveBR   = read_buf[4];
  _out_struct->omni      = read_buf[5];
  _out_struct->shoulder  = read_buf[6];
  _out_struct->wrist     = read_buf[7];
  _out_struct->keyGrabber= read_buf[8];
  _out_struct->intake    = read_buf[9];
  _out_struct->score     = read_buf[10];
  _out_struct->doorOut   = read_buf[11];
  _out_struct->doorUp    = read_buf[12];
  _out_struct->compressor= read_buf[13];
  
  failures = 0;
  return true;
}

void Comm::write(){
  setOutBuf();
  if(failures == 0){
    while(Serial2.available() > 0) {
      char t = Serial2.read();
    }
  }
  Serial2.write(outBuf, 26);
}

int Comm::write(unsigned char * msg, int len) {
  return Serial2.write(msg, len);
}

int Comm::read(unsigned char * buf, int bufsize) {
  int bytes_avail = Serial2.available();
  if(bytes_avail < 4){
    failures++;
    return false;
  }
  Serial2.readBytes(read_buf, bytes_avail);
  for (int i = bytes_avail - 1; i >= 3; i --) {
    if (buf[i] == 0xdd) {
      unsigned char len = read_buf[i - 1];
      if ((len + 3) <= i && read_buf[i - len - 3] == 0xff && read_buf[ - 2] == _crc8(&read_buf[i - len - 2], len)) {
        memcpy(buf, read_buf, bufsize > 128 ? 128 : bufsize);
        return bufsize > 128 ? 128 : bufsize;
      }
    }
  }
  return -1;
}

void Comm::setOutBuf(){
  outBuf[0] = 0xdd;
  float *tmp = (float *)(outBuf + 1);
  *tmp = _in_struct->gyroAngle;
  *(tmp+1) = _in_struct->sonicDistanceF;
  *(tmp+2) = _in_struct->sonicDistanceL;
  *(tmp+3) = _in_struct->sonicDistanceR;
  *(tmp+4) = _in_struct->sonicDistanceB;
  uint16_t *tmp2 = (uint16_t *)(outBuf + 21);
  *tmp2 = _in_struct->shoulder;
  *(tmp2+1) = _in_struct->wrist;
  outBuf[25] = _crc8(&outBuf[1], 24);
}

Comm::~Comm() {
}

uint8_t Comm::_crc8(uint8_t *data, int len) {
  uint8_t crc = 0x00;
  for (int i = 0; i < len; i++) {
    crc = _crc8_ccitt_update(crc, data[i]);
  }
  return crc;
}

