/*
 * uart_com.h
 *
 *  Created on: Dec 2, 2024
 *      Author: HP
 */

#ifndef INC_UART_COM_H_
#define INC_UART_COM_H_
#include "main.h"
#define MAX_BUFFER_SIZE 30
#define MAX_STRING 50
#define CALLBACK_PERIOD 3000
typedef enum {
	STOP = 0,
	START
}CMD_FLAG;

extern uint8_t temp;
extern uint8_t buffer_flag;
void User_Init(UART_HandleTypeDef *UART_pointer, ADC_HandleTypeDef* ADC_pointer);
void uart_communiation_fsm(void);
#endif /* INC_UART_COM_H_ */
