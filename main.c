/*
 * UART.cpp
 *
 * Created: 2024-05-01 오후 3:01:25
 * Author : me
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart0.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit,NULL, _FDEV_SETUP_WRITE);

int main(void)
{
    UART0_init();
	uint8_t rxData; //한 byte를 읽기
	stdout = &OUTPUT;
	printf("hello AVR!\n");
	
    while (1) 
    {
		rxData = UART0_receive();
		if(rxData = 'a'){
			PORTA = 0xff;
		}else if(rxData = 'b'){
			PORTA = 0x10;
		}
	}
}
