


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "UART.h"

#define UART_CONTROL *(uint32_t *)0xE0001000
#define UART_MODE *(uint32_t *)0xE0001004
#define UART_BAUD_GEN *(uint32_t *)0xE0001018
#define UART_BAUD_DIV *(uint32_t *)0xE0001034
#define UART_INT_EN *(uint32_t *)0xE000100C
#define UART_FIFO *(uint32_t *)0xE0001030
#define UART_Tx_STA *(uint32_t *)0xE000102C

/*
Reset the UART Controller by setting the appropriate bits in the Control Register
Set the BAUDGEN clock divider (a baud rate of 115200 works well, and a 0x7C is a workable divider value)
Set the Buad_Rate_Divider value to define the bit-clock (again for 115200, 0x6 works)
Set bits in the Control Register to enable software resets for the RX and TX data paths, enable the transmitter and receiver, and enable Stop Transmitter Break
Set bits in the UART mode register to set the channel mode to normal, stop bits to 1, parity to no parity, character length to 8 bits, and clock source to UART reference clock
Set bits in the RXTOUT register to set the timeout value to 1
Disable all interrupts by setting bits in the IDR register
*/

void setup_UART(){
	// Clearing the REG's
	UART_CONTROL = 0x0128;
	UART_BAUD_GEN = 0;
	UART_BAUD_DIV = 0; //ignored value 0-3
	UART_MODE = 0; // resets whole register
	// Set the REG's
	UART_CONTROL = 0x14; /* RX_EN = 1, TX_EN = 1 */
	UART_BAUD_GEN = 0x7C; // baud rate of 115200
	UART_BAUD_DIV = 0x6; //baud rate divider value of 6
	UART_MODE = 0x00000020;  //forced to 0 parity (space)

}

void UART_POLLING(){

	int uart_RX = 0;
	int uart_Tx_sta = 0x2;
	int uart_Rx_sta = 0;
	UART_Tx_STA = 0;
	int i = 0;
//	int uart_Tx_sta;
	// Need to check for the STATUS REG to check if
	// something came in.
	//checking the FIFO Tx STA sub_REG Bit 3 from the UART_C_Status REG

	while(uart_Tx_sta == 0x2){
		uart_Tx_sta = UART_Tx_STA & 0x2;
		}
	//When it gets out of the while loop then
	//check the RX_FIFO reg for what came in.
	//uart_RX = UART_FIFO;

}
