#include <avr/io.h>
#include "uart0.h"

void UART0_init(void){
	// 표 9-9(p.219)
	UBRR0H = 0x00;
	UBRR0L = 207; //9600bps설정하는것임
	//data는 8bit고 non parity설정을하자 : UCSRnA레지스터
	
	UCSR0A |= 1 << U2X0; //2배속 통신
	UCSR0C |= 0x06; // ASYNC(비동기) / data8bit / none parity
	
	// RXEN0 : UART0로 부터 수신이 가능하도록 설정
	// TXEN0 : UART0로 부터 송신이 가능하도록 설정
	// RXCIEN0 : UART0로 부터 1byte가 들어오면(stopbit까지 수신완료된 상황)이면,
	// rx 인터럽트(수신 UART0인터럽트)를 발생시킨다.
	UCSR0B |= 1 << RXEN0 | 1 << TXEN0 | 1 << RXCIE0;
	// shift연산자가 5번 우선순위고, |가 우선순위가 10번이므로 ()치지마라.
	
}

void UART0_transmit(uint8_t data){
	while(!(UCSR0A & 1 << UDRE0));
	// 우선순위가 << : 5, & : 8
	//UDRE0는 5비트위치
	//데이터가 전송중이면 전송이 끝날때 까지 기다린다.
	// no operation : NOP
	UDR0 = data; //UDR은 Uart Data Register
}

unsigned char UART0_receive(){
	while(!(UCSR0A & 1 << RXC0)); //UDR에 값이 들어왔는지 아닌지(UDR 수신확인)
	//수신되면 1로 while문 탈출
	return UDR0;
}