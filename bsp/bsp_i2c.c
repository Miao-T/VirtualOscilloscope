////////////////////////////////////////////////////////////////////////////////
/// @file     BSP_I2C.C
/// @author   S Yi
/// @version  v2.0.0
/// @date     2019-03-13
/// @brief    THIS FILE PROVIDES ALL THE I2C BSP LAYER FUNCTIONS.
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
#define _BSP_I2C_C_

// Files includes  -------------------------------------------------------------
#include <string.h>
#include "HAL_gpio.h"
#include "HAL_i2c.h"

#include "bsp.h"
#include "bsp_i2c.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Board_Support_Package
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup I2C_BSP
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup I2C_Exported_Functions
/// @{

#if defined(__MZ311)
////////////////////////////////////////////////////////////////////////////////
/// @brief  Configure I2C GPIO.
/// @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BSP_I2C_GPIO_Configure(I2C_TypeDef* I2Cx, bool remapEn, u8 remapIdx)
{
    GPIOA_ClockEnable();
    GPIO_Mode_AF_OD_20MHz_Init(I2C_SCL_PORT, I2C_SCL_PIN, NO_REMAP, I2C_SCL_AF);
    GPIO_Mode_AF_OD_20MHz_Init(I2C_SDA_PORT, I2C_SDA_PIN, NO_REMAP, I2C_SDA_AF);
}
#endif

#if !defined(__MZ311)
////////////////////////////////////////////////////////////////////////////////
/// @brief  Configure I2C GPIO.
/// @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BSP_I2C_GPIO_Configure(I2C_TypeDef* I2Cx, bool remapEn, u8 remapIdx)
{
    switch ((u32)I2Cx) {
    #if defined(I2C1)
		case I2C1_BASE:
			if (!remapEn) {
					GPIOB_ClockEnable();
					GPIO_Mode_AF_OD_20MHz_Init(GPIOB, GPIO_Pin_6, NO_REMAP, GPIO_AF_1);
					GPIO_Mode_AF_OD_20MHz_Init(GPIOB, GPIO_Pin_7, NO_REMAP, GPIO_AF_1);
			}
			else {
				if (remapIdx == 0) {
                    GPIOB_ClockEnable();
                    GPIO_Mode_AF_OD_20MHz_Init(GPIOB, GPIO_Pin_8, EXTI_MAPR_I2C1, GPIO_AF_1);
                    GPIO_Mode_AF_OD_20MHz_Init(GPIOB, GPIO_Pin_9, EXTI_MAPR_I2C1, GPIO_AF_1);
				}
        #if defined (__MZ306) || defined(__MZ308) || defined(__MZ309)
				if (remapIdx == 1) {
					GPIOB_ClockEnable();
					GPIO_Mode_AF_OD_20MHz_Init(GPIOB, GPIO_Pin_10, NO_REMAP, GPIO_AF_1);
					GPIO_Mode_AF_OD_20MHz_Init(GPIOB, GPIO_Pin_11, NO_REMAP, GPIO_AF_1);
				}
        #endif
			}
			break;
    #endif
//------------------------------------------------------------------------------
    #if defined(I2C2)
		case I2C2_BASE:
			if (!remapEn) {
					GPIOB_ClockEnable();
					GPIO_Mode_AF_OD_20MHz_Init(GPIOB, GPIO_Pin_10, NO_REMAP, GPIO_AF_1);
					GPIO_Mode_AF_OD_20MHz_Init(GPIOB, GPIO_Pin_11, NO_REMAP, GPIO_AF_1);
			}
			break;
    #endif
		default: break;
    }
}
#endif

/// @}

/// @}

/// @}
