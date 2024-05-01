/*
 * uart.h
 *
 * Created: 2024-05-01 오후 4:01:22
 *  Author: me
 */ 


#ifndef UART_H_
#define UART_H_

void UART0_init(void);
void UART0_transmit(uint8_t data);
unsigned char UART0_receive();
void UART0_print_string(char *str);

#endif /* UART_H_ */