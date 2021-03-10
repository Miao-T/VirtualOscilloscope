////////////////////////////////////////////////////////////////////////////////
/// @file     BSP_UART.C
/// @author   QR Wang
/// @version  v2.0.0
/// @date     2019-03-13
/// @brief    THIS FILE PROVIDES ALL THE UART BSP LAYER FUNCTIONS.
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
#define _BSP_UART_C_

// Files includes  -------------------------------------------------------------
#include "hal_gpio.h"
#include "hal_uart.h"

#include "bsp.h"
#include "bsp_uart.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Board_Support_Package
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup UART_BSP
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup UART_Exported_Functions
/// @{

/* -----------------------------------------------------------------------------
----------  P e r i p h e r a l s    i n i t i a l i z a t i o n   -------------
----------------------------------------------------------------------------- */
////////////////////////////////////////////////////////////////////////////////
/// @brief  UART GPIO Config
/// @param  UARTx: Select the UART or the UART peripheral.
/// @param  reampEn: Select the remap status.
/// @param  remap: Select the AFIO status.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
#if defined(__MM32_MB032) || defined(__MM32_MB033)
void BSP_UART_GPIO_Configure(UART_TypeDef* UARTx, bool remapEn, u8 remapIdx)
{
    switch(*(u32*)&UARTx) {
        case (u32)UART1:
        if(remapEn){
            //MB032/033
            GPIO_Mode_AF_PP_50MHz_Init(GPIOA,  GPIO_Pin_12, NO_REMAP, GPIO_AF_1);
            GPIO_Mode_IPU_Init        (GPIOA,  GPIO_Pin_0,  NO_REMAP, GPIO_AF_1);
        }
        else{
            
        }
        break;
        case (u32)UART2:
        if(remapEn){
            //MB032/033
            GPIO_Mode_AF_PP_50MHz_Init(GPIOA,  GPIO_Pin_1,  NO_REMAP, GPIO_AF_2);
            GPIO_Mode_IPU_Init        (GPIOA,  GPIO_Pin_13, NO_REMAP, GPIO_AF_2);
        }
        else{
            
        }
        break;
        default:break;
    }
}
#else
void BSP_UART_GPIO_Configure(UART_TypeDef* UARTx, bool remapEn, u8 remapIdx)
{
    GPIO_InitTypeDef 	GPIO_InitStructure;
    
    switch (*(u32*)&UARTx) {
        case (u32)UART1:
        if (!remapEn) {
            GPIOA_ClockEnable();
            GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_9,  NO_REMAP, 		GPIO_AF_1);
            GPIO_Mode_IPU_Init        (GPIOA, GPIO_Pin_10, NO_REMAP, 		GPIO_AF_1);
        }
        else {
            if (remapIdx == 0) {
                GPIOB_ClockEnable();
                GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_6, EXTI_MAPR_UART1, 	GPIO_AF_0);
                GPIO_Mode_IPU_Init		  (GPIOB, GPIO_Pin_7, EXTI_MAPR_UART1, 	GPIO_AF_0);
            }
            
#if (__CORTEX_M == 0)
            else if (remapIdx == 1) {
                GPIOA_ClockEnable();
                GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_10, NO_REMAP, 		GPIO_AF_3);
                GPIO_Mode_IPU_Init	      (GPIOA, GPIO_Pin_9,  NO_REMAP, 		GPIO_AF_3);
            }
#endif
        }
        break;
		case (u32)UART2:
        if (!remapEn) {
            GPIOA_ClockEnable();
            GPIO_SetBits(GPIOA, GPIO_Pin_2);
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_20MHz;
            GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            exGPIO_PinAFConfig(GPIOA, GPIO_Pin_2, NO_REMAP, GPIO_AF_1);
            //GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_2, NO_REMAP, 		GPIO_AF_1);
            GPIO_Mode_IPU_Init		  (GPIOA, GPIO_Pin_3, NO_REMAP, 		GPIO_AF_1);
        }
        else {
#if (__CORTEX_M == 0)
            if (remapIdx == 0) {
                GPIOA_ClockEnable();
                GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_14, NO_REMAP, 		GPIO_AF_1);
                GPIO_Mode_IPU_Init		  (GPIOA, GPIO_Pin_15, NO_REMAP, 		GPIO_AF_1);
            }
#endif
#if (__CORTEX_M == 0) && !defined(__MZ306)
            else if (remapIdx == 1) {
                GPIOC_ClockEnable();
                GPIO_Mode_AF_PP_20MHz_Init(GPIOC, GPIO_Pin_4, NO_REMAP, 		GPIO_AF_3);
                GPIO_Mode_IPU_Init		  (GPIOC, GPIO_Pin_5, NO_REMAP, 		GPIO_AF_3);
            }
#endif
        }
        break;
#if defined(__MT304)
        case (u32)UART3:
        if (!remapEn) {
            GPIOB_ClockEnable();
            GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_10, NO_REMAP, 		NO_FUNCAF);
            GPIO_Mode_IPU_Init		  (GPIOB, GPIO_Pin_11, NO_REMAP, 		NO_FUNCAF);
        }
        else {
            if (remapIdx == 0) {
                GPIOC_ClockEnable();
                GPIO_Mode_AF_PP_20MHz_Init(GPIOC, GPIO_Pin_10, EXTI_MAPR_UART3, NO_FUNCAF);
                GPIO_Mode_IPU_Init		  (GPIOC, GPIO_Pin_11, EXTI_MAPR_UART3, NO_FUNCAF);
            }
        }
        break;
#endif
		default: break;
	}
}
#endif

////////////////////////////////////////////////////////////////////////////////
void BSP_UART_GPIO_CONFIGURE(UART_TypeDef* UARTx)
{
    GPIOA_ClockEnable();
    GPIOB_ClockEnable();
    if (UART1 == UARTx) {
        UART1_TX_CONFIGURE;
        UART1_RX_CONFIGURE;
    }
    else if (UART2 == UARTx) {
        UART2_TX_CONFIGURE;
        UART2_RX_CONFIGURE;
    }
#if defined(UART3)
    else if (UART3 == UARTx) {
        
        
    }
#endif
}
/// @}

/// @}

/// @}
