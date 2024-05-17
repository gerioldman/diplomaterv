#include "test_run.h"
#include "boot.h"
#include "flash.h"
#include "opentestloader_struct.h"
#include "stm32f4xx_ll_gpio.h"


static const uint4_to_hex[16] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

static void print_hex(uint32_t value)
{
  __io_putchar(uint4_to_hex[((value) & 0xF0000000) >> 28]); __io_putchar(uint4_to_hex[((value) & 0x0F000000) >> 24]);
  __io_putchar(uint4_to_hex[((value) & 0x00F00000) >> 20]); __io_putchar(uint4_to_hex[((value) & 0x000F0000) >> 16]);
  __io_putchar(uint4_to_hex[((value) & 0x0000F000) >> 12]); __io_putchar(uint4_to_hex[((value) & 0x00000F00) >>  8]);
  __io_putchar(uint4_to_hex[((value) & 0x000000F0) >>  4]); __io_putchar(uint4_to_hex[((value) & 0x0000000F)      ]);
  __io_putchar('\r');
  __io_putchar('\n');
}

static void print_string(const char *ch)
{
  while (*ch != '\0')
  {
    __io_putchar(*ch);
    ch++;
  }
}

static blt_bool test_ran = 0;

void TestTask(void)
{
    uint32_t input = LL_GPIO_ReadInputPort(GPIOC);
    if (!((input & GPIO_PIN_13) == GPIO_PIN_13) && test_ran == 0)
    {
        opentestloader_struct *descriptor = FlashGetUserProgBaseAddress();
        print_string("checksum: \0"); print_hex( descriptor->checksum);
        print_string("version: \0"); print_hex( descriptor->version);
        print_string("send_char: \0"); print_hex( descriptor->send_char);
        print_string("run_test: \0"); print_hex( descriptor->run_test);
        print_string("bss_start: \0"); print_hex( descriptor->bss_start);
        print_string("bss_end: \0"); print_hex( descriptor->bss_end);
        print_string("data_start: \0"); print_hex( descriptor->data_start);
        print_string("data_end: \0"); print_hex( descriptor->data_end);
        print_string("init_start: \0"); print_hex( descriptor->init_start);
        __io_putchar('\r');__io_putchar('\n');

        print_string("Writing pointer for sending char to struct: \0"); print_hex(&__io_putchar);

        print_string("... Init RAM ... \r\n\0");
        for(uint8_t* ptr = descriptor->bss_start; ptr < descriptor->bss_end; ptr++) *ptr = 0x00u;
        for(uint8_t* ptr = descriptor->data_start; ptr < descriptor->data_end; ptr++) *ptr = ((uint8_t*)descriptor->init_start)[ptr - (uint8_t*)descriptor->data_start];

        print_string("... Exectute tests ...\r\n\0");
        descriptor->run_test();
        test_ran = 1;
    }
}