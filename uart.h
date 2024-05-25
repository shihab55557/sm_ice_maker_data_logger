

#include "stm32g030xx.h"

void    uart_Init(uint32_t Baud_rate);
void    uart_char(char ch);
void    uart_send_char(char *data);
long uart_send_num(long num);
void    uart_send_num_arr(int32_t arr[10]);
void    uart_flush(void);
void    uart_send_num_bin(uint16_t num);
void    uart_send_num_float(float num);