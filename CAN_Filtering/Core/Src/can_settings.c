/*
 * can_settings.c
 *
 *  Created on: Aug 4, 2020
 *      Author: yaceq
 */
#include "can.h"
#include "can_settings.h"

volatile uint32_t canCount;
#define MAKE_CAN_ID_INVERT(src, dst, cmd)   ((cmd)+((src)<<8)+((dst)<<16))//Jeżeli adres nadawcy w MSB
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan->Instance==CAN1){
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
	  {
 	    Error_Handler();
	  }

	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING); //enable interrupts


	}
}

uint8_t CAN_Transmit(uint8_t dst,uint8_t cmd,uint8_t *Dane,uint8_t DLC,uint8_t Rtr_Data)
{
	if(Rtr_Data==REMOTE)
	{
		TxHeader.ExtId=MAKE_CAN_ID_INVERT(0x01,dst,cmd);
			TxHeader.RTR=CAN_RTR_REMOTE;
			TxHeader.IDE=IDE_;
			TxHeader.TransmitGlobalTime=DISABLE;
	}
	else if(Rtr_Data==DATA)
	{
		TxHeader.ExtId=MAKE_CAN_ID_INVERT(0x01,dst,cmd);
					TxHeader.RTR=CAN_RTR_DATA;
					TxHeader.DLC=DLC;
					TxHeader.IDE=IDE_;
					TxHeader.TransmitGlobalTime=DISABLE;
	}
	if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader, Dane, &TxMailbox)!=HAL_OK)
	{
		return 1;
		Error_Handler();
	}
	while(HAL_CAN_IsTxMessagePending(&hcan1, TxMailbox));  //!!!UWAGA
	return 0;
}
 void CAN_Starting(CAN_HandleTypeDef *canHandle)
{
	uint32_t filter_id=0x500000;
	uint32_t filter_mask=0x7fff00;

	 CAN_FilterTypeDef  sFilterConfig;
	 	   sFilterConfig.FilterBank = 0;
	 	   sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	 	   sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	 	   sFilterConfig.FilterIdHigh = filter_id >> 13 & 0xFFFF;
	 	   sFilterConfig.FilterIdLow = filter_id << 3 & 0xFFF8;
	 	   sFilterConfig.FilterMaskIdHigh = filter_mask >> 13 & 0xFFFF;
	 	   sFilterConfig.FilterMaskIdLow = filter_mask << 3 & 0xFFF8;
	 	   sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	 	   sFilterConfig.FilterActivation = ENABLE;
	 	   sFilterConfig.SlaveStartFilterBank = 14;

	 	   if (HAL_CAN_ConfigFilter(canHandle, &sFilterConfig) != HAL_OK)
	 	   {
	 	    	     Error_Handler();
	 	   }
	 	   if (HAL_CAN_Start(canHandle) != HAL_OK)
	 	   {
	 	     Error_Handler();
	 	   }
	 	   if (HAL_CAN_ActivateNotification(canHandle, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	 	   {
	 	     Error_Handler();
	 	   }
	 }

