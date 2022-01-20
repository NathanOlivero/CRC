/***************************************************************
* DESCR: Main for Cycle Redundancy Check (CRC)
*
* INPUTS:
*
* OUTPUT: Prints CRC value calculated
*
****************************************************************
* DATE          AUTHOR              VERSION     COMMENT
* 20170316      Nathan Olivero      1.0.0       Initial Code
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crc.h"

#define BASE10 10
#define BASE16 16

char *readLine(char *buffer, size_t length, FILE *fp)
{
    char *ptr = fgets(buffer,length,fp);
    if(NULL != ptr)
    {
        size_t last_index = strlen(buffer) - 1;
        if('\n' == buffer[last_index])
        {
            buffer[last_index] = '\0';
        }
        else
        {
            fscanf(fp, "%*[^\n]");
            (void) fgetc(fp);
        }
    }
    return ptr;
}

int main(int argc, char **argv)
{
    typedef enum
    {
        MAIN_MENU,
        CRC_8BIT,
        CRC_16BIT,
        CRC_32BIT,
        CRC_OTHER,
        EXIT
    } menuType;

    int i;
    char user_input[256];

    int num_8bit_crc_names = 10;
    const char *crc_type_8bit_names[] = {"CRC8","CRC8_CDMA2000","CRC8_DARC","CRC8_DVB_S2","CRC8_EBU","CRC8_ICODE","CRC8_ITU","CRC8_MAXIM","CRC8_ROHC","CRC8_WCDMA"};

    int num_16bit_crc_names = 23;
    const char *crc_type_16bit_names[] = {"CRC16_CCITT_FALSE","CRC16_ARC","CRC16_AUG_CCITT","CRC16_BUYPASS","CRC16_CDMA2000","CRC16_DDS_110","CRC16_DECT_R"
                                        ,"CRC16_DECT_X","CRC16_DNP","CRC16_EN_13757","CRC16_GENIBUS","CRC16_MAXIM","CRC16_MCRF4XX","CRC16_RIELLO","CRC16_T10_DIF"
                                        ,"CRC16_TELEDISK","CRC16_TMS37157","CRC16_USB","CRC16_A","CRC16_KERMIT","CRC16_MODBUS","CRC16_X25","CRC16_XMODEM"};

    int num_32bit_crc_names = 9;
    const char *crc_type_32bit_names[] = {"CRC32","CRC32_BZIP2","CRC32_C","CRC32_D","CRC32_MPEG2","CRC32_POSIX","CRC32_Q","CRC32_JAMCRC","CRC32_XFER"};

    /*Input variables*/
    char crc_name[256];
    char crc_size;
    long polynomial;
    long initial_remainder;
    long final_XOR;
    bool reflection_in;
    bool reflection_out;

    /*Parse Inputs*/
    if(argc < 2)
    {
        long user_choice;
        char *eptr;
        menuType next_menu_state = MAIN_MENU;
        menuType prev_menu_state = MAIN_MENU;

        while(next_menu_state != EXIT)
        {
            switch(next_menu_state)
            {
            case MAIN_MENU:
                prev_menu_state = MAIN_MENU;
                printf("Please select a CRC option:\n1: 8Bit CRC\n2: 16Bit CRC\n3: 32Bit CRC\n4: User Defined CRC\n5: Exit\n");
                printf("\nSelection: ");
                while(next_menu_state == prev_menu_state)
                {
                    readLine(user_input,256,stdin);
                    user_choice = strtol(user_input, &eptr, BASE10);
                    /* Determine next_state */
                    switch(user_choice)
                    {
                    case 1:
                        next_menu_state = CRC_8BIT;
                        break;
                    case 2:
                        next_menu_state = CRC_16BIT;
                        break;
                    case 3:
                        next_menu_state = CRC_32BIT;
                        break;
                    case 4:
                        next_menu_state = CRC_OTHER;
                        break;
                    case 5:
                        return 0;
                        break;
                    default :
                        printf("Invalid Input!\n");
                        next_menu_state = prev_menu_state;
                    }
                }
                break;

            case CRC_8BIT:
                prev_menu_state = CRC_8BIT;
                printf("Please select one of the following 8bit CRCs:\n");
                for(i=0; i<num_8bit_crc_names; i++)
                {
                    printf("%d: %s\n",(i+1),crc_type_8bit_names[i]);
                }
                printf("%d: Back\n",(num_8bit_crc_names+1));
                printf("\nSelection: ");
                while(next_menu_state == prev_menu_state)
                {
                    readLine(user_input,256,stdin);
                    user_choice = strtol(user_input, &eptr, BASE10);
                    /* Determine next_state */
                    if((0 < user_choice) && ((num_8bit_crc_names+1) > user_choice))
                    {
                        strcpy(crc_name, crc_type_8bit_names[user_choice-1]);
                        next_menu_state = EXIT;
                    }
                    else if((num_8bit_crc_names+1) == user_choice)
                    {
                        next_menu_state = MAIN_MENU;
                    }
                    else
                    {
                        printf("Invalid Input!\n");
                        next_menu_state = prev_menu_state;
                    }
                }
                break;

            case CRC_16BIT:
                prev_menu_state = CRC_16BIT;
                printf("Please select one of the following 16bit CRCs:\n");
                for(i=0; i<num_16bit_crc_names; i++)
                {
                    printf("%d: %s\n",(i+1),crc_type_16bit_names[i]);
                }
                printf("%d: Back\n",(num_16bit_crc_names+1));
                printf("\nSelection: ");
                while(next_menu_state == prev_menu_state)
                {
                    readLine(user_input,256,stdin);
                    user_choice = strtol(user_input, &eptr, BASE10);
                    /* Determine next_state */
                    if((0 < user_choice) && ((num_16bit_crc_names+1) > user_choice))
                    {
                        strcpy(crc_name, crc_type_16bit_names[user_choice-1]);
                        next_menu_state = EXIT;
                    }
                    else if((num_16bit_crc_names+1) == user_choice)
                    {
                        next_menu_state = MAIN_MENU;
                    }
                    else
                    {
                        printf("Invalid Input!\n");
                        next_menu_state = prev_menu_state;
                    }
                }
                break;

            case CRC_32BIT:
                prev_menu_state = CRC_32BIT;
                printf("Please select one of the following 32bit CRCs:\n");
                for(i=0; i<num_32bit_crc_names; i++)
                {
                    printf("%d: %s\n",(i+1),crc_type_32bit_names[i]);
                }
                printf("%d: Back\n",(num_32bit_crc_names+1));
                printf("\nSelection: ");
                while(next_menu_state == prev_menu_state)
                {
                    readLine(user_input,256,stdin);
                    user_choice = strtol(user_input, &eptr, BASE10);
                    /* Determine next_state */
                    if((0 < user_choice) && ((num_32bit_crc_names+1) > user_choice))
                    {
                        strcpy(crc_name, crc_type_32bit_names[user_choice-1]);
                        next_menu_state = EXIT;
                    }
                    else if((num_32bit_crc_names+1) == user_choice)
                    {
                        next_menu_state = MAIN_MENU;
                    }
                    else
                    {
                        printf("Invalid Input!\n");
                        next_menu_state = prev_menu_state;
                    }
                }
                break;

            case CRC_OTHER:
                    /*
                    char crc_size;
                    long polynomial;
                    long initial_remainder;
                    long final_XOR;
                    bool reflection_in;
                    bool reflection_out;
                    */
                prev_menu_state = CRC_OTHER;
                printf("Please provide the following CRC info:\n");

                /*crc_size*/
                int valid_input = 0;
                while(valid_input == 0)
                {
                    printf("CRC size (8-64): ");
                    readLine(user_input,256,stdin);
                    user_choice = strtol(user_input, &eptr, BASE10);
                    if(user_choice < 8 || user_choice > 64)
                    {
                        printf("Invalid Input!\n");
                    }
                    else
                    {
                        crc_size = (char) user_choice;
                        valid_input = 1;
                    }
                }
                /*polynomial*/
                valid_input = 0;
                while(valid_input == 0)
                {
                    printf("General polynomial (hex): 0x");
                    readLine(user_input,256,stdin);
                    user_choice = strtol(user_input, &eptr, BASE16);
                    polynomial = user_choice;
                    printf("Polynomial entered: 0x%lx\n", user_choice);
                    printf("Is this value correct?\n1: Yes\n2: No\n");
                    printf("\nSelection: ");
                    readLine(user_input,256,stdin);
                    user_choice = strtol(user_input, &eptr, BASE10);
                    if(user_choice == 1)
                    {
                        valid_input = 1;
                    }
                }
                /*initial_remainder*/
                valid_input = 0;
                while(valid_input == 0)
                {
                    printf("Initial remainder value (hex): 0x");
                    readLine(user_input,256,stdin);
                    user_choice = strtol(user_input, &eptr, BASE10);
                    initial_remainder = user_choice;
                    printf("Initial remainder entered: 0x%lx\n", user_choice);
                    printf("Is this value correct?\n1: Yes\n2: No\n");
                    readLine(user_input,256,stdin);
                    user_choice = strtol(user_input, &eptr, BASE10);
                    if(user_choice == 1)
                    {
                        valid_input = 1;
                    }
                }
                /*final_XOR*/
                valid_input = 0;
                while(valid_input == 0)
                {
                    printf("Final XOR value (hex): 0x");
                    readLine(user_input,256,stdin);
                    user_choice = strtol(user_input, &eptr, BASE10);
                    final_XOR = user_choice;
                    printf("Final XOR entered: 0x%lx\n", user_choice);
                    printf("Is this value correct?\n1: Yes\n2: No\n");
                    readLine(user_input,256,stdin);
                    user_choice = strtol(user_input, &eptr, BASE10);
                    if(user_choice == 1)
                    {
                        valid_input = 1;
                    }
                }
                /*reflection_in*/
                valid_input = 0;
                while(valid_input == 0)
                {
                    printf("Reflection_in:\n1: True\n2: False\n");
                    readLine(user_input,256,stdin);
                    user_choice = strtol(user_input, &eptr, BASE10);
                    if(user_choice == 1)
                    {
                        reflection_in = true;
                        valid_input = 1;
                    }
                    else if(user_choice == 2)
                    {
                        reflection_in = false;
                        valid_input = 1;
                    }
                    else
                    {
                        printf("Invalid Input!\n");
                    }
                }
                    /* Determine next_state */
                next_menu_state = EXIT;
                break;

            default :
                next_menu_state = MAIN_MENU;

            }
            /* Clear the screen for readability */
            if(prev_menu_state != next_menu_state)
            {
                system("cls"); /*Not Portable at all, but does the job*/
            }
        }
    }
    else if(argc < 3)
    {
        printf("No CRC type provided, Default type of CRC32 used\n");
        strcpy(crc_name, "CRC32");
    }
    else
    {
        if(argc != 9)
        {
            /*Prompt for missing args, give choice of default*/
            printf("Please provided the following CRC parameters: \n");
//            fgets(container,numOfChars,stdin);
        }
        else
        {
//            data = argv[1]
//            crc_name = argv[2];
//            crc_size = argv[3];
//            polynomial = argv[4];
//            initial_remainder = argv[5];
//            final_XOR = argv[6];
//            reflection_in = argv[7];
//            reflection_out = argv[8];
        }
    }

//    for(i=0; i<argc; i++)
//    {
//        /*Parse out inputs*/
//        printf("Argv[%i]: %c", i, argv[i]);
//    }

    unsigned char const data[] = "123456789";
    int nBytes = 9;

    /*Calculating CRC*/
    crcType crc_type;
    long crc_value;

    crc_type = defineCRCType(crc_name, crc_size, polynomial, initial_remainder, final_XOR, reflection_in, reflection_out);
    createCRCTable(crc_type);
    crc_value = calculateCRC(crc_type, data, nBytes);

    printf("The calculated CRC value: 0x%lx\n", crc_value);


    return 0;
}
