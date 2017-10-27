#include "crc8.h"

#define GP  0x107   /* x^8 + x^2 + x + 1 */
#define DI  0x07

CRC8::CRC8()
{
    int i,j;
    unsigned char crc;
    for (i=0; i<256; i++) {
        crc = i;
        for (j=0; j<8; j++)
            crc = (crc << 1) ^ ((crc & 0x80) ? DI : 0);
        crc8_table[i] = crc & 0xFF;
    }
}


CRC8::~CRC8()
{
}


// compute the crc of an array
unsigned char CRC8::compute(unsigned char * data, int length)
{
    unsigned crc = 0x00;
    for (int i = 0; i < length; i ++) {
        crc = crc8_table[crc ^ data[i]];
        crc &= 0xff;
    }
    return crc;
}
