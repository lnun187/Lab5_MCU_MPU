/*
 * uart_com.c
 *
 *  Created on: Dec 2, 2024
 *      Author: HP
 */
#include "uart_com.h"

UART_HandleTypeDef *huart;
ADC_HandleTypeDef *hadc;
uint8_t temp = 0;
char buffer[MAX_BUFFER_SIZE];
char str[MAX_STRING];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;

CMD_FLAG command_flag = 0;
int command_data = 0;

void User_Init(UART_HandleTypeDef *UART_pointer, ADC_HandleTypeDef *ADC_pointer) {
	huart = UART_pointer;
	hadc = ADC_pointer;
	HAL_UART_Receive_IT(huart, &temp, 1);
	HAL_ADC_Start(hadc);
	setTimer(0, CALLBACK_PERIOD);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM2) {
		timerRun();
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART2) {
		if (index_buffer == 0)
			for (int i = 0; i < MAX_BUFFER_SIZE; i++)
				buffer[i] = 0;

		if (temp != 13) {	// enter key
			buffer[index_buffer++] = temp;
			if (index_buffer >= MAX_BUFFER_SIZE)
				index_buffer = 0;
		} else {
			index_buffer = 0;
			buffer_flag = 1;
		}
		HAL_UART_Receive_IT(huart, &temp, 1);
		HAL_UART_Transmit(huart, &temp, 1, 100);
	}
}


void send_data(void) {
	HAL_UART_Transmit(huart, (void*) str,
			sprintf(str, "!ADC=%d#\r\n", command_data), 1000);
}
void uart_communiation_fsm(void) {
	switch (command_flag) {
	case START:
		if (is_avail(0)) {
			send_data();
			setTimer(0, CALLBACK_PERIOD);
		}
		if(buffer_flag) buffer_flag = 0;
		else return;
		if (!strcmp(buffer, "!OK#")) {
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 0);
			command_flag = STOP;
			command_data = 0; //reset value
		}
		break;
	case STOP:
		if(buffer_flag) buffer_flag = 0;
		else return;
		if (!strcmp(buffer, "!RST#")) {
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 1);
			command_flag = START;
			command_data = HAL_ADC_GetValue(hadc);
		}
		break;
	default:
		break;
	}
}
