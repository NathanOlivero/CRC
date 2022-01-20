/***************************************************************
* DESCR: Header file for Cycle Redundancy Check (CRC)
****************************************************************
* DATE          AUTHOR              VERSION     COMMENT
* 20170316      Nathan Olivero      1.0.0       Initial Code
****************************************************************/
#ifndef CRC_H_INCLUDED
#define CRC_H_INCLUDED

#include <string.h>
#include <stdbool.h>

//define crc struct with CRC, reflection, poly, XOR, ect
typedef struct
{
    char crc_name[256];
    char crc_size;
    long polynomial;
    long initial_remainder;
    long final_XOR;
    bool reflection_in;
    bool reflection_out;
} crcType;

/* PROTOTYPES */
unsigned long reflectBits(unsigned long data, unsigned char nBits);
crcType defineCRCType(char* crc_name, char crc_size, long polynomial, long initial_remainder, long final_XOR, bool reflection_in, bool reflection_out);
void createCRCTable(crcType crc_type);
unsigned long calculateCRC(crcType crc_type, unsigned char const data[], int nBytes);


#endif // CRC_H_INCLUDED
