/*
 * UART.cpp
 *
 * Created: 2024-05-01 오후 3:01:25
 * Author : me
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart0.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit,NULL, _FDEV_SETUP_WRITE);

char rxBuff[100] = {0,};
uint8_t rxFlag = 0;

ISR(USART0_RX_vect){
	// 1byte의 값이 들어오면 일로들어옴
	static uint8_t rxHead = 0;
	uint8_t rxData = UDR0;
	if(rxData == '\n' || rxData == '\r'){
		//입력값의 끝이면 null문자 삽입
		rxBuff[rxHead] = '\0';
		rxHead = 0;
		rxFlag = 1; //다 받았따.
	}else{
		rxBuff[rxHead++] = rxData;
	}
}

int main(void)
{
    UART0_init();
	uint8_t rxData; //한 byte를 읽기
	stdout = &OUTPUT;
	printf("hello AVR!\n");
	sei(); // 전역적으로 인터럽트를 허용하겠다
    while (1) 
    {
		if(rxFlag == 1){
			rxFlag = 0;
			printf(rxBuff);
		}
	}
}
