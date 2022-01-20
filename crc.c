/****************************************************************
* DATE          AUTHOR              VERSION     COMMENT
* 20170316      Nathan Olivero      1.0.0       Initial Code
****************************************************************/

#include "crc.h"

long crcTable[256];

/***************************************************************
* DESCR: defines type of CRC
*
* INPUTS:   crc_name            Name of CRC type
*           crc_size            Data length of CRC
*           polynomial          General polynomial used in CRC
*                               calculation
*           initial_remainder   Initial remainder value
*           final_XOR           Final value to XOR with remainder
*           reflection_in       Whether to reflect byte initially
*           reflection_out      Whether to reflect byte at end
*
* OUTPUT:   crcType             Type of CRC
*
* NOTE:     The input parameter "crc_name" will define all other
*           input parameters if it is a CRC name found below
****************************************************************/
crcType defineCRCType(char crc_name[], char crc_size, long polynomial, long initial_remainder, long final_XOR, bool reflection_in, bool reflection_out)
{
    crcType crc;

        /******************************************
        *               32 Bit CRCs
        *******************************************/
    if(!strcmp(crc_name,"CRC32"))
    {
        strcpy(crc.crc_name, "CRC32");
        crc.crc_size = 32;
        crc.polynomial = 0x04C11DB7;
        crc.initial_remainder = 0xFFFFFFFF;
        crc.final_XOR = 0xFFFFFFFF;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC32_BZIP2"))
    {
        strcpy(crc.crc_name, "CRC32_BZIP2");
        crc.crc_size = 32;
        crc.polynomial = 0x04C11DB7;
        crc.initial_remainder = 0xFFFFFFFF;
        crc.final_XOR = 0xFFFFFFFF;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC32_C"))
    {
        strcpy(crc.crc_name, "CRC32_C");
        crc.crc_size = 32;
        crc.polynomial = 0x1EDC6F41;
        crc.initial_remainder = 0xFFFFFFFF;
        crc.final_XOR = 0xFFFFFFFF;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC32_D"))
    {
        strcpy(crc.crc_name, "CRC32_D");
        crc.crc_size = 32;
        crc.polynomial = 0xA833982B;
        crc.initial_remainder = 0xFFFFFFFF;
        crc.final_XOR = 0xFFFFFFFF;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC32_MPEG2"))
    {
        strcpy(crc.crc_name, "CRC32_MPEG2");
        crc.crc_size = 32;
        crc.polynomial = 0x04C11DB7;
        crc.initial_remainder = 0xFFFFFFFF;
        crc.final_XOR = 0x00000000;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC32_POSIX"))
    {
        strcpy(crc.crc_name, "CRC32_POSIX");
        crc.crc_size = 32;
        crc.polynomial = 0x04C11DB7;
        crc.initial_remainder = 0x00000000;
        crc.final_XOR = 0xFFFFFFFF;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC32_Q"))
    {
        strcpy(crc.crc_name, "CRC32_Q");
        crc.crc_size = 32;
        crc.polynomial = 0x814141AB;
        crc.initial_remainder = 0x00000000;
        crc.final_XOR = 0x00000000;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC32_JAMCRC"))
    {
        strcpy(crc.crc_name, "CRC32_JAMCRC");
        crc.crc_size = 32;
        crc.polynomial = 0x04C11DB7;
        crc.initial_remainder = 0xFFFFFFFF;
        crc.final_XOR = 0x00000000;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC32_XFER"))
    {
        strcpy(crc.crc_name, "CRC32_XFER");
        crc.crc_size = 32;
        crc.polynomial = 0x000000AF;
        crc.initial_remainder = 0x00000000;
        crc.final_XOR = 0x00000000;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
        /******************************************
        *               16 Bit CRCs
        *******************************************/
    else if(!strcmp(crc_name,"CRC16_CCITT_FALSE"))
    {
        strcpy(crc.crc_name, "CRC16_CCITT_FALSE");
        crc.crc_size = 16;
        crc.polynomial = 0x1021;
        crc.initial_remainder = 0xFFFF;
        crc.final_XOR = 0x0000;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC16_ARC"))
    {
        strcpy(crc.crc_name, "CRC16_ARC");
        crc.crc_size = 16;
        crc.polynomial = 0x8005;
        crc.initial_remainder = 0x0000;
        crc.final_XOR = 0x0000;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC16_AUG_CCITT"))
    {
        strcpy(crc.crc_name, "CRC16_AUG_CCITT");
        crc.crc_size = 16;
        crc.polynomial = 0x1021;
        crc.initial_remainder = 0x1D0F;
        crc.final_XOR = 0x0000;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC16_BUYPASS"))
    {
        strcpy(crc.crc_name, "CRC16_BUYPASS");
        crc.crc_size = 16;
        crc.polynomial = 0x8005;
        crc.initial_remainder = 0x0000;
        crc.final_XOR = 0x0000;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC16_CDMA2000"))
    {
        strcpy(crc.crc_name, "CRC16_CDMA2000");
        crc.crc_size = 16;
        crc.polynomial = 0xC867;
        crc.initial_remainder = 0xFFFF;
        crc.final_XOR = 0x0000;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC16_DDS_110"))
    {
        strcpy(crc.crc_name, "CRC16_DDS_110");
        crc.crc_size = 16;
        crc.polynomial = 0x8005;
        crc.initial_remainder = 0x800D;
        crc.final_XOR = 0x0000;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC16_DECT_R"))
    {
        strcpy(crc.crc_name, "CRC16_DECT_R");
        crc.crc_size = 16;
        crc.polynomial = 0x0589;
        crc.initial_remainder = 0x0000;
        crc.final_XOR = 0x0001;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC16_DECT_X"))
    {
        strcpy(crc.crc_name, "CRC16_DECT_X");
        crc.crc_size = 16;
        crc.polynomial = 0x0589;
        crc.initial_remainder = 0x0000;
        crc.final_XOR = 0x0000;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC16_DNP"))
    {
        strcpy(crc.crc_name, "CRC16_DNP");
        crc.crc_size = 16;
        crc.polynomial = 0x3D65;
        crc.initial_remainder = 0x0000;
        crc.final_XOR = 0xFFFF;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC16_EN_13757"))
    {
        strcpy(crc.crc_name, "CRC16_EN_13757");
        crc.crc_size = 16;
        crc.polynomial = 0x3D65;
        crc.initial_remainder = 0x0000;
        crc.final_XOR = 0xFFFF;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC16_GENIBUS"))
    {
        strcpy(crc.crc_name, "CRC16_GENIBUS");
        crc.crc_size = 16;
        crc.polynomial = 0x1021;
        crc.initial_remainder = 0xFFFF;
        crc.final_XOR = 0xFFFF;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC16_MAXIM"))
    {
        strcpy(crc.crc_name, "CRC16_MAXIM");
        crc.crc_size = 16;
        crc.polynomial = 0x8005;
        crc.initial_remainder = 0x0000;
        crc.final_XOR = 0xFFFF;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC16_MCRF4XX"))
    {
        strcpy(crc.crc_name, "CRC16_MCRF4XX");
        crc.crc_size = 16;
        crc.polynomial = 0x1021;
        crc.initial_remainder = 0xFFFF;
        crc.final_XOR = 0x0000;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC16_RIELLO"))
    {
        strcpy(crc.crc_name, "CRC16_RIELLO");
        crc.crc_size = 16;
        crc.polynomial = 0x1021;
        crc.initial_remainder = 0xB2AA;
        crc.final_XOR = 0x0000;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC16_T10_DIF"))
    {
        strcpy(crc.crc_name, "CRC16_T10_DIF");
        crc.crc_size = 16;
        crc.polynomial = 0x8BB7;
        crc.initial_remainder = 0x0000;
        crc.final_XOR = 0x0000;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC16_TELEDISK"))
    {
        strcpy(crc.crc_name, "CRC16_TELEDISK");
        crc.crc_size = 16;
        crc.polynomial = 0xA097;
        crc.initial_remainder = 0x0000;
        crc.final_XOR = 0x0000;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC16_TMS37157"))
    {
        strcpy(crc.crc_name, "CRC16_TMS37157");
        crc.crc_size = 16;
        crc.polynomial = 0x1021;
        crc.initial_remainder = 0x89EC;
        crc.final_XOR = 0x0000;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC16_USB"))
    {
        strcpy(crc.crc_name, "CRC16_USB");
        crc.crc_size = 16;
        crc.polynomial = 0x8005;
        crc.initial_remainder = 0xFFFF;
        crc.final_XOR = 0xFFFF;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC16_A"))
    {
        strcpy(crc.crc_name, "CRC16_A");
        crc.crc_size = 16;
        crc.polynomial = 0x1021;
        crc.initial_remainder = 0xC6C6;
        crc.final_XOR = 0x0000;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC16_KERMIT"))
    {
        strcpy(crc.crc_name, "CRC16_KERMIT");
        crc.crc_size = 16;
        crc.polynomial = 0x1021;
        crc.initial_remainder = 0x0000;
        crc.final_XOR = 0x0000;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC16_MODBUS"))
    {
        strcpy(crc.crc_name, "CRC16_MODBUS");
        crc.crc_size = 16;
        crc.polynomial = 0x8005;
        crc.initial_remainder = 0xFFFF;
        crc.final_XOR = 0x0000;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC16_X25"))
    {
        strcpy(crc.crc_name, "CRC16_X25");
        crc.crc_size = 16;
        crc.polynomial = 0x1021;
        crc.initial_remainder = 0xFFFF;
        crc.final_XOR = 0xFFFF;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC16_XMODEM"))
    {
        strcpy(crc.crc_name, "CRC16_XMODEM");
        crc.crc_size = 16;
        crc.polynomial = 0x1021;
        crc.initial_remainder = 0x0000;
        crc.final_XOR = 0x0000;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
        /******************************************
        *               8 Bit CRCs
        *******************************************/
    else if(!strcmp(crc_name,"CRC8"))
    {
        strcpy(crc.crc_name, "CRC8");
        crc.crc_size = 8;
        crc.polynomial = 0x07;
        crc.initial_remainder = 0x00;
        crc.final_XOR = 0x00;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC8_CDMA2000"))
    {
        strcpy(crc.crc_name, "CRC8_CDMA2000");
        crc.crc_size = 8;
        crc.polynomial = 0x9B;
        crc.initial_remainder = 0xFF;
        crc.final_XOR = 0x00;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC8_DARC"))
    {
        strcpy(crc.crc_name, "CRC8_DARC");
        crc.crc_size = 8;
        crc.polynomial = 0x39;
        crc.initial_remainder = 0x00;
        crc.final_XOR = 0x00;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC8_DVB_S2"))
    {
        strcpy(crc.crc_name, "CRC8_DVB_S2");
        crc.crc_size = 8;
        crc.polynomial = 0xD5;
        crc.initial_remainder = 0x00;
        crc.final_XOR = 0x00;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC8_EBU"))
    {
        strcpy(crc.crc_name, "CRC8_EBU");
        crc.crc_size = 8;
        crc.polynomial = 0x1D;
        crc.initial_remainder = 0xFF;
        crc.final_XOR = 0x00;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC8_ICODE"))
    {
        strcpy(crc.crc_name, "CRC8_ICODE");
        crc.crc_size = 8;
        crc.polynomial = 0x1D;
        crc.initial_remainder = 0xFD;
        crc.final_XOR = 0x00;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC8_ITU"))
    {
        strcpy(crc.crc_name, "CRC8_ITU");
        crc.crc_size = 8;
        crc.polynomial = 0x07;
        crc.initial_remainder = 0x00;
        crc.final_XOR = 0x55;
        crc.reflection_in = false;
        crc.reflection_out = false;
    }
    else if(!strcmp(crc_name,"CRC8_MAXIM"))
    {
        strcpy(crc.crc_name, "CRC8_MAXIM");
        crc.crc_size = 8;
        crc.polynomial = 0x31;
        crc.initial_remainder = 0x00;
        crc.final_XOR = 0x00;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC8_ROHC"))
    {
        strcpy(crc.crc_name, "CRC8_ROHC");
        crc.crc_size = 8;
        crc.polynomial = 0x07;
        crc.initial_remainder = 0xFF;
        crc.final_XOR = 0x00;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
    else if(!strcmp(crc_name,"CRC8_WCDMA"))
    {
        strcpy(crc.crc_name, "CRC8_WCDMA");
        crc.crc_size = 8;
        crc.polynomial = 0x9B;
        crc.initial_remainder = 0x00;
        crc.final_XOR = 0x00;
        crc.reflection_in = true;
        crc.reflection_out = true;
    }
        /******************************************
        *               DEFAULT
        *******************************************/
    else
    {
        strcpy(crc.crc_name, crc_name);
        crc.crc_size = crc_size;
        crc.polynomial = polynomial;
        crc.initial_remainder = initial_remainder;
        crc.final_XOR = final_XOR;
        crc.reflection_in = reflection_in;
        crc.reflection_out = reflection_out;
    }

    return crc;
}

/***************************************************************
* DESCR: Reflects the bits of the given data around the middle
*
* INPUTS:   data                Data to reflect
*           nBits               Number of bits in given data
*
* OUTPUTS:  reflectedBits       Reflected data
****************************************************************/
unsigned long reflectBits(unsigned long data, unsigned char nBits)
{
    unsigned long  reflection = 0x00000000;
	unsigned char  bit;

	/*
	 * Reflect the data about the center bit.
	 */
	for (bit = 0; bit < nBits; bit++)
	{
		/*
		 * If the LSB bit is set, set the reflection of it.
		 */
		if (data & 0x00000001)
		{
			reflection |= (1 << ((nBits - 1) - bit));
		}

		data = (data >> 1);
	}

	return (reflection);
}

/***************************************************************
* DESCR: Creates a reference table of CRC remainder values
*
* INPUTS: crc_type              Type of CRC
*
* OUTPUTS: N/A
****************************************************************/
void createCRCTable(crcType crc_type)
{
    unsigned long  remainder;
	int			   dividend;
	unsigned char  bit;


    /*Compute the remainder of each possible dividend*/
    for (dividend = 0; dividend < 256; ++dividend)
    {
        /*Start with the dividend followed by zeros*/
        remainder = dividend << (crc_type.crc_size - 8);

        /*Perform modulo-2 division, a bit at a time*/
        for (bit = 8; bit > 0; bit--)
        {
            /*Try to divide the current data bit*/
            if (remainder & (1 << (crc_type.crc_size - 1)))
            {
                remainder = (remainder << 1) ^ crc_type.polynomial;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
        crcTable[dividend] = remainder;
    }
}

/***************************************************************
* DESCR: Calculates Cycle Redundancy Check (CRC)
*
* INPUTS:   crcType             Type of CRC
*           data                Array of individual bytes to
*                               calculate CRC for
*           nBytes              Number of bytes of data
*
* OUTPUTS:  CRC                 CRC value of the data input
****************************************************************/
unsigned long calculateCRC(crcType crc_type, unsigned char const data[], int nBytes)
{
    int i;
    unsigned char  byte;
    unsigned long remainder = crc_type.initial_remainder;

    /*Divide each byte of data*/
    for (i=0; i<nBytes; i++)
    {
        if(crc_type.reflection_in)
        {
            byte = (unsigned char) reflectBits(data[i], 8);
        }
        else
        {
            byte = data[i];
        }
        byte = (byte ^ (remainder >> (crc_type.crc_size - 8)));
  		remainder = crcTable[byte] ^ (remainder << 8);
    }
    if(crc_type.reflection_out)
    {
        remainder = reflectBits(remainder, crc_type.crc_size);
    }

    return (remainder ^ crc_type.final_XOR);
}
