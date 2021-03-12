////////////////////////////////////////////////////////////////////////////////
/// @file     BSP_CAN.C
/// @author
/// @version
/// @date
/// @brief    THIS FILE PROVIDES ALL THE CAN BSP LAYER FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT 2018-2019 MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion  --------------------------------------
#define _BSP_CAN_C_

// Files includes  -------------------------------------------------------------
#include <string.h>

#include "HAL_gpio.h"
#include "HAL_can.h"

#include "bsp.h"
#include "bsp_can.h"


#if defined (CAN1)
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Board_Support_Package
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup CAN_BSP
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup CAN_Exported_Functions
/// @{

/* -----------------------------------------------------------------------------
----------  P e r i p h e r a l s    i n i t i a l i z a t i o n   -------------
----------------------------------------------------------------------------- */
////////////////////////////////////////////////////////////////////////////////
/// @brief  CAN GPIO Config
/// @param  CANx:where x can be 1 to select the CAN peripheral.
/// @param  reampEn: Select the remap status.
/// @param  remap: Select the AFIO status.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BSP_CAN_GPIO_Configure(CAN_Peli_TypeDef* CANx, bool remapEn, u8 remapIdx)
{
	if (!remapEn) {
			GPIOA_ClockEnable();
			GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_12,  NO_REMAP, 		GPIO_AF_4);
			GPIO_Mode_IPU_Init        (GPIOA, GPIO_Pin_11, NO_REMAP, 		GPIO_AF_4);
	}
	else {
		if (remapIdx == 0) {
			GPIOB_ClockEnable();
            GPIO_Mode_AF_PP_50MHz_Init(GPIOB, GPIO_Pin_9, EXTI_MAPR_CAN, 	GPIO_AF_4);
			GPIO_Mode_FLOATING_Init	  (GPIOB, GPIO_Pin_8, EXTI_MAPR_CAN, 	GPIO_AF_4);
        }
	}
	RCC->APB2ENR |= RCC_APB2ENR_EXTI;
#if defined(__MM3N1)
	EXTI->MAPR   |= EXTI_MAPR_CAN;							// 1 << 2;
#endif
}
/// @}

/// @}

/// @}
#endif
