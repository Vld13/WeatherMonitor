#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "main.h"
#include "DHT.h"

UART_HandleTypeDef huart2;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

void printWelcomeMessage(void);
uint8_t readUserInput(void);
uint8_t processUserInput(uint8_t, DHT_data d);

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART2_UART_Init();
  
  DHT_sensor dht11_sensor = {GPIOB, GPIO_PIN_4, DHT11, GPIO_NOPULL};
  DHT_data data;
  
  uint8_t opt = 0;

  while(1)
  {
	  HAL_Delay(5000);
	  char msg[40];
	  //Получение данных с датчика
	  data = DHT_getData(&dht11_sensor);
	  sprintf(msg, "%d %d***", (uint8_t)data.temp, (uint8_t)data.hum);
	  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFF);

	  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
	  HAL_Delay(300);
	  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  }
}
