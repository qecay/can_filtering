/*
 * can_settings.h
 *
 *  Created on: Aug 4, 2020
 *      Author: yaceq
 */

#ifndef INC_CAN_SETTINGS_H_
#define INC_CAN_SETTINGS_H_

#include "main.h"
#include "stm32f4xx_hal.h"
#include "can.h"
#define REMOTE 1
#define DATA 0
#define IDE_ CAN_ID_EXT

//CAN_HandleTypeDef hcan;


CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[8];
uint8_t TxData[8];
uint32_t TxMailbox;
volatile uint8_t CAN_RCV_FLAG;
volatile uint8_t Piro_test_FALG;
volatile uint8_t START_INIT_Flag;
int8_t display_Flag; 	//flaga reakcji na żądanie statusu




uint8_t CAN_Transmit(uint8_t dst,uint8_t cmd,uint8_t *Dane,uint8_t DLC,uint8_t Rtr_Data);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
void CAN_Starting(CAN_HandleTypeDef* canHandle);
//void parse_PS_Data(CAN_RxHeaderTypeDef *Header,uint8_t *Datas); //do ewentualnej zmiany gdy przerwania będą podmieniać dane



#endif /* INC_CAN_SETTINGS_H_ */
