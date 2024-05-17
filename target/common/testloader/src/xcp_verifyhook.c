#include "boot.h"
#include "com.h"
#include "opentestloader_struct.h"
#include <stdint.h>

// User command code as per XCP 1.0 - Part 2 Protocol Layer Specification: page 69(nice!)
#define USER_CMD ((blt_int8u)0xF1u)

// Custom sub commands for the testloader
#define RUN_TEST_SUBCMD ((blt_int8u) 0x00)
#define READ_TEST_SUBCMD ((blt_int8u) 0x01)

// READ_TEST subcommand results
#define MORE_DATA_LEFT ((blt_int8u) 0x01)
#define NO_MORE_DATA ((blt_int8u) 0x00)

static uint8_t test_output_buffer[512] = {};
static uint16_t test_output_len = 0;
static uint16_t test_output_read = 0;

void __io_putchar(char c);
blt_bool XcpPacketReceivedHook(blt_int8u *data, blt_int8u len);

void __io_putchar(char c)
{
    test_output_buffer[test_output_len++] = c;
}

blt_bool XcpPacketReceivedHook(blt_int8u *data, blt_int8u len){
    blt_bool processed = BLT_FALSE;

    if (data[0] == USER_CMD)
    {
        blt_int8u response[XCP_DTO_PACKET_LEN];
        blt_int8u response_len;
        
        processed = BLT_TRUE;
        if (len != 2)
        {
            response[0] = XCP_PID_ERR;
            response[1] = XCP_ERR_CMD_UNKNOWN;
            response_len = 2;
        }


        switch (data[1])
        {
        case RUN_TEST_SUBCMD:
            opentestloader_struct *descriptor = FlashGetUserProgBaseAddress();
            for(uint8_t* ptr = descriptor->bss_start; ptr < descriptor->bss_end; ptr++) *ptr = 0x00u;
            for(uint8_t* ptr = descriptor->data_start; ptr < descriptor->data_end; ptr++) *ptr = ((uint8_t*)descriptor->init_start)[ptr - (uint8_t*)descriptor->data_start];
            descriptor->run_test();
            response[0] = XCP_PID_RES;
            response_len = 1;
            break;
        
        case READ_TEST_SUBCMD:
            response[0] = XCP_PID_RES;
            response[1] = (test_output_len > test_output_read) ? MORE_DATA_LEFT : NO_MORE_DATA;

            uint32_t data_to_copy = test_output_len > (XCP_DTO_PACKET_LEN - 2) ? (XCP_DTO_PACKET_LEN - 2) : (test_output_len - test_output_read);
            response_len = 2 + data_to_copy;

            for (blt_int32u i = 0; i < data_to_copy; i++)
            {
                response[i + 2] = test_output_buffer[test_output_read + i];
            }

            test_output_read += data_to_copy;
            break;
        
        default:
            response[0] = XCP_PID_ERR;
            response[1] = XCP_ERR_CMD_UNKNOWN;
            response_len = 2;
            break;
        }

        ComTransmitPacket(response,response_len);
    }

    return processed;
}