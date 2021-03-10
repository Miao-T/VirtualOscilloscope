////////////////////////////////////////////////////////////////////////////////
/// @file     BSP_UART.H
/// @author   QR Wang
/// @version  v2.0.0
/// @date     2019-03-13
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE UART
///           BSP LAYER.
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

#ifndef __BSP_UART_H
#define __BSP_UART_H


////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Board_Support_Package
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup UART_BSP
/// @brief UART BSP modules
/// @{
///


////////////////////////////////////////////////////////////////////////////////
/// @defgroup UART_Exported_Types
/// @{

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup UART_Exported_Variables
/// @{


#if defined(__MM32_MB032) || defined(__MM32_MB033)

#define UART1_IDX  1
#define UART2_IDX  1

#else

#define UART1_IDX  0
#define UART2_IDX  0

#endif


/* Configure */
#if (UART1_IDX == 0)

#define UART1_TX_PORT   GPIOA
#define UART1_TX_PIN    GPIO_Pin_9
#define UART1_TX_AF     GPIO_AF_1

#define UART1_RX_PORT   GPIOA
#define UART1_RX_PIN    GPIO_Pin_10
#define UART1_RX_AF     GPIO_AF_1

#else

#define UART1_TX_PORT   GPIOA
#define UART1_TX_PIN    GPIO_Pin_12
#define UART1_TX_AF     GPIO_AF_1

#define UART1_RX_PORT   GPIOA
#define UART1_RX_PIN    GPIO_Pin_0
#define UART1_RX_AF     GPIO_AF_1

#endif

#if (UART2_IDX == 0)

#define UART2_TX_PORT   GPIOA
#define UART2_TX_PIN    GPIO_Pin_2
#define UART2_TX_AF     GPIO_AF_1

#define UART2_RX_PORT   GPIOA
#define UART2_RX_PIN    GPIO_Pin_3
#define UART2_RX_AF     GPIO_AF_1

#else

#define UART2_TX_PORT   GPIOA
#define UART2_TX_PIN    GPIO_Pin_1
#define UART2_TX_AF     GPIO_AF_2

#define UART2_RX_PORT   GPIOA
#define UART2_RX_PIN    GPIO_Pin_13
#define UART2_RX_AF     GPIO_AF_2

#endif


#define UART1_TX_CONFIGURE {GPIO_Mode_AF_PP_50MHz_Init(UART1_TX_PORT,  UART1_TX_PIN,  NO_REMAP, UART1_TX_AF); }
#define UART1_RX_CONFIGURE {GPIO_Mode_IPU_Init        (UART1_RX_PORT,  UART1_RX_PIN,  NO_REMAP, UART1_RX_AF); }

#define UART2_TX_CONFIGURE {GPIO_Mode_AF_PP_50MHz_Init(UART2_TX_PORT,  UART2_TX_PIN,  NO_REMAP, UART2_TX_AF); }
#define UART2_RX_CONFIGURE {GPIO_Mode_IPU_Init        (UART2_RX_PORT,  UART2_RX_PIN,  NO_REMAP, UART2_RX_AF); }














////////////////////////////////////////////////////////////////////////////////
#ifdef _BSP_UART_C_

#define GLOBAL
#else
#define GLOBAL extern

#endif

#undef GLOBAL
////////////////////////////////////////////////////////////////////////////////
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup UART_Exported_Functions
/// @{

// old FDS
void BSP_UART_GPIO_Configure(UART_TypeDef* UARTx, bool remapEn, u8 remapIdx);

// FDS SE
void BSP_UART_GPIO_CONFIGURE(UART_TypeDef* UARTx);

/// @}


/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif /*__BSP_UART_H */
////////////////////////////////////////////////////////////////////////////////
