#pragma once
class CRC8
{
public:
    CRC8();
    ~CRC8();
    unsigned char crc8_table[256];
    // compute the crc of an array
    unsigned char compute(unsigned char * data, int length);
};

