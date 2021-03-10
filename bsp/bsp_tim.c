////////////////////////////////////////////////////////////////////////////////
/// @file     BSP_TIM.C
/// @author   D Chen
/// @version  v2.0.0
/// @date     2019-03-13
/// @brief    THIS FILE PROVIDES ALL THE TIM BSP LAYER FUNCTIONS.
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
#define _BSP_TIM_C_

// Files includes  -------------------------------------------------------------
#include "hal_gpio.h"

#include "bsp.h"
#include "bsp_tim.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Board_Support_Package
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup TIM_BSP
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup TIM_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
// TIM1 CH1
//      remapEn false:   PA8
//      remapEn true:
//      remapIdx 0:      PA8
//------------------------------------------------------------------------------
// TIM2 CH1
//      remapEn false:   PA0
//      remapEn true:
//      remapIdx 0:      PA15
//      remapIdx 1:      PA0
//      remapIdx 2:      PA15
//------------------------------------------------------------------------------
// TIM3 CH1
//      remapEn false:   PA6
//      remapEn true:
//      remapIdx 0:      PB4
//      remapIdx 1:      PC6
//------------------------------------------------------------------------------
// TIM4 CH1
//      remapEn false/true:   PB6
//------------------------------------------------------------------------------
// TIM14 CH1
//      remapEn false:   PB1
//      remapEn true:
//      remapIdx 0:      PA4
//      remapIdx 1:      PA7
//      remapIdx 2:      PA0
//------------------------------------------------------------------------------
// TIM16 CH1
//      remapEn false:   PB8
//      remapEn true:
//      remapIdx 0:      PA6
//      remapIdx 1:      PA10
//------------------------------------------------------------------------------
// TIM17 CH1
//      remapEn false:   PB9
//      remapEn true:
//      remapIdx 0:      PA7
//      remapIdx 1:      PD7
//------------------------------------------------------------------------------
// TIM8 CH1
//      remapEn false:   PC6
//      remapEn true:
//      remapIdx 0:      PC0

////////////////////////////////////////////////////////////////////////////////
//  @brief  Timer Channel-1 GPIO Configure
//  @param  TIMx: where x can be 1, 2, 3, 4, 8, 14, 16 or 17 to select the TIM peripheral.
//  @param  remapEn:  true or false to select remap function.
//  @param  remapIdx: select Pin remap source.
//  @param  inoutMode: 0 is config as input-pin, 1 is config as output-pin
//  @retval None.
////////////////////////////////////////////////////////////////////////////////
#if defined(__MM32_MB032) || defined(__MM32_MB033)
void BSP_TIM_CH1_GPIO_Configure(TIM_TypeDef* tim, bool remapEn, u8 remapIdx, bool inoutMode)
{
    switch (*(u32*)&tim) {
        case (u32)TIM1:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_6, NO_REMAP, GPIO_AF_1) :\
                GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_6, 	NO_REMAP, GPIO_AF_1);
        }
        else {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_9, NO_REMAP, GPIO_AF_2) :\
                GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_9, NO_REMAP, GPIO_AF_2);
        }
        break;
        case (u32)TIM3:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_8, NO_REMAP, GPIO_AF_4) :\
                GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_8, 	NO_REMAP, GPIO_AF_4);
        }
        else {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_11, NO_REMAP, GPIO_AF_4) :\
                GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_11, NO_REMAP, GPIO_AF_4);
        }
        break;
        case (u32)TIM14:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_9, NO_REMAP, GPIO_AF_3) :\
                GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_9, NO_REMAP, GPIO_AF_3);
        }
        else {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_11, NO_REMAP, GPIO_AF_3) :\
                GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_11, NO_REMAP, GPIO_AF_3);
        }
        break;
        default: break;
    }
}
#else
////////////////////////////////////////////////////////////////////////////////
void BSP_TIM_CH1_GPIO_Configure(TIM_TypeDef* tim, bool remapEn, u8 remapIdx, bool inoutMode)
{
    switch (*(u32*)&tim) {
#if defined(TIM1)        
        case (u32)TIM1:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_8, NO_REMAP, GPIO_AF_2) :\
                GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_8, 	NO_REMAP, GPIO_AF_2);
        }
        else {
            if (remapIdx == 0) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_8, EXTI_MAPR_TIM1_PARTIAL, GPIO_AF_2) :\
                    GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_8, 	EXTI_MAPR_TIM1_PARTIAL, GPIO_AF_2);
            }
        }
        break;
#endif
#if defined(TIM2)
        case (u32)TIM2:      
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_0, NO_REMAP, GPIO_AF_2) :\
                GPIO_Mode_FLOATING_Init(	 GPIOA, GPIO_Pin_0, NO_REMAP, GPIO_AF_2);
        }
        else {
            if (remapIdx == 0) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_15, EXTI_MAPR_TIM2_PARTIAL1, GPIO_AF_2) :\
                    GPIO_Mode_FLOATING_Init(	 GPIOA, GPIO_Pin_15, EXTI_MAPR_TIM2_PARTIAL1, GPIO_AF_2);
            }
            if (remapIdx == 1) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_0, EXTI_MAPR_TIM2_PARTIAL2, GPIO_AF_2) :\
                    GPIO_Mode_FLOATING_Init(	 GPIOA, GPIO_Pin_0, EXTI_MAPR_TIM2_PARTIAL2, GPIO_AF_2);
            }
            if (remapIdx == 2) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_15, EXTI_MAPR_TIM2, GPIO_AF_2) :\
                    GPIO_Mode_FLOATING_Init(	 GPIOA, GPIO_Pin_15, EXTI_MAPR_TIM2, GPIO_AF_2);
            }
        }
        break;
#endif
#if defined(TIM3)        
        case (u32)TIM3:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_6, NO_REMAP, GPIO_AF_1) :\
                GPIO_Mode_FLOATING_Init(	 GPIOA, GPIO_Pin_6, NO_REMAP, GPIO_AF_1);
        }
        else {
            if (remapIdx == 0) {
                GPIOB_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_4, EXTI_MAPR_TIM3_PARTIAL, GPIO_AF_1) :\
                    GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_4, EXTI_MAPR_TIM3_PARTIAL, GPIO_AF_1);
            }
            if (remapIdx == 1) {
                GPIOC_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOC, GPIO_Pin_6, EXTI_MAPR_TIM3, GPIO_AF_1) :\
                    GPIO_Mode_FLOATING_Init(	 GPIOC, GPIO_Pin_6, EXTI_MAPR_TIM3, GPIO_AF_1);
            }
        }
        break;
#endif
#if defined(TIM4)
        case (u32)TIM4:
        GPIOB_ClockEnable();
        (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_6, NO_REMAP, NO_FUNCAF) :\
            GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_6, NO_REMAP, NO_FUNCAF);
        break;
#endif
#if defined(TIM8)
        case (u32)TIM8:
        if (!remapEn) {
            GPIOC_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOC, GPIO_Pin_6, NO_REMAP, GPIO_AF_3) :\
                GPIO_Mode_FLOATING_Init(	 GPIOC, GPIO_Pin_6, NO_REMAP, GPIO_AF_3);
        }
        else {
            if (remapIdx == 0) {
                GPIOC_ClockEnable();
                    (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOC, GPIO_Pin_0, NO_REMAP, GPIO_AF_6) :\
                        GPIO_Mode_FLOATING_Init(   GPIOC, GPIO_Pin_0, NO_REMAP, GPIO_AF_6);
            }
        }
        break;
#endif
#if defined(TIM14)
        case (u32)TIM14:
        if (!remapEn) {
            GPIOB_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_1, NO_REMAP, GPIO_AF_0) :\
                GPIO_Mode_FLOATING_Init(   GPIOB, GPIO_Pin_1, NO_REMAP, GPIO_AF_0);
        }
        else {
            if (remapIdx == 0) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_4, NO_REMAP, GPIO_AF_4) :\
                    GPIO_Mode_FLOATING_Init(   GPIOA, GPIO_Pin_4, NO_REMAP, GPIO_AF_4);
            }
            if (remapIdx == 1) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_7, NO_REMAP, GPIO_AF_4) :\
                    GPIO_Mode_FLOATING_Init(   GPIOA, GPIO_Pin_7, NO_REMAP, GPIO_AF_4);
            }
            if (remapIdx == 2) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_0, NO_REMAP, GPIO_AF_6) :\
                    GPIO_Mode_FLOATING_Init(   GPIOA, GPIO_Pin_0, NO_REMAP, GPIO_AF_6);
            }
        }
        break;
#endif
#if defined(TIM16)
        case (u32)TIM16:
        if (!remapEn) {
            GPIOB_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_8, NO_REMAP, GPIO_AF_2) :\
                GPIO_Mode_FLOATING_Init(   GPIOB, GPIO_Pin_8, NO_REMAP, GPIO_AF_2);
        }
        else {
            if (remapIdx == 0) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_6, NO_REMAP, GPIO_AF_5) :\
                    GPIO_Mode_FLOATING_Init(   GPIOA, GPIO_Pin_6, NO_REMAP, GPIO_AF_5);
            }
            if (remapIdx == 1) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_10, NO_REMAP, GPIO_AF_6) :\
                    GPIO_Mode_FLOATING_Init(   GPIOA, GPIO_Pin_10, NO_REMAP, GPIO_AF_6);
            }
        }
        break;
#endif
#if defined(TIM17)
        case (u32)TIM17:
        if (!remapEn) {
            GPIOB_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_9, NO_REMAP, GPIO_AF_2) :\
                GPIO_Mode_FLOATING_Init(   GPIOB, GPIO_Pin_9, NO_REMAP, GPIO_AF_2);
        }
        else {
            if (remapIdx == 0) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_7, NO_REMAP, GPIO_AF_5) :\
                    GPIO_Mode_FLOATING_Init(   GPIOA, GPIO_Pin_7, NO_REMAP, GPIO_AF_5);
            }
            if (remapIdx == 1) {
                GPIOD_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOD, GPIO_Pin_7, NO_REMAP, GPIO_AF_6) :\
                    GPIO_Mode_FLOATING_Init(   GPIOD, GPIO_Pin_7, NO_REMAP, GPIO_AF_6);
            }
        }
        break;
#endif
        default: break;
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////
// TIM1 CH2
//      remapEn false:   PA9
//      remapEn true:
//      remapIdx 0:      PA9
//------------------------------------------------------------------------------
// TIM2 CH2
//      remapEn false:   PA1
//      remapEn true:
//      remapIdx 0:      PB3
//      remapIdx 1:      PA1
//      remapIdx 2:      PB3
//------------------------------------------------------------------------------
// TIM3 CH2
//      remapEn false:   PA7
//      remapEn true:
//      remapIdx 0:      PB5
//      remapIdx 1:      PC7
//------------------------------------------------------------------------------
// TIM4 CH2
//      remapEn false/true:   PB7
//------------------------------------------------------------------------------
// TIM8 CH2
//      remapEn false:   PC7
//      remapEn true:
//      remapIdx 0:      PC1
////////////////////////////////////////////////////////////////////////////////
//  @brief  Timer Channel-2 GPIO Configure
//  @param  tim: where x can be 1, 2, 3, 4 or 8 to select the TIM peripheral.
//  @param  remapEn:  true or false to select remap function.
//  @param  remapIdx: select Pin remap source.
//  @param  inoutMode: 0 is config as input-pin, 1 is config as output-pin
//  @retval None.
////////////////////////////////////////////////////////////////////////////////
#if defined(__MM32_MB032) || defined(__MM32_MB033)
void BSP_TIM_CH2_GPIO_Configure(TIM_TypeDef* tim, bool remapEn, u8 remapIdx, bool inoutMode)
{
    switch (*(u32*)&tim) {
        case (u32)TIM1:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_8, NO_REMAP, GPIO_AF_1) :\
                GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_8, 	NO_REMAP, GPIO_AF_1);
        }
        else {
            if (remapIdx == 0) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_10, NO_REMAP, GPIO_AF_2) :\
                    GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_10, NO_REMAP, GPIO_AF_2);
            }
            if (remapIdx == 1) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_11, NO_REMAP, GPIO_AF_2) :\
                    GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_11, NO_REMAP, GPIO_AF_2);
            }
        }
        break;
        case (u32)TIM3:
        GPIOA_ClockEnable();
        (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_2, NO_REMAP, GPIO_AF_4) :\
            GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_2, NO_REMAP, GPIO_AF_4);
        break;
        default: break;
    }
}
#else
////////////////////////////////////////////////////////////////////////////////
void BSP_TIM_CH2_GPIO_Configure(TIM_TypeDef* tim, bool remapEn, u8 remapIdx, bool inoutMode)
{
    switch (*(u32*)&tim) {
#if defined(TIM1)
        case (u32)TIM1:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_9, NO_REMAP, GPIO_AF_2) :
                    	  GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_9, 	NO_REMAP, GPIO_AF_2);
        }
        else {
            if (remapIdx == 0) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_9, EXTI_MAPR_TIM1_PARTIAL, GPIO_AF_2) :
                        	  GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_9, 	EXTI_MAPR_TIM1_PARTIAL, GPIO_AF_2);
            }
        }
        break;
#endif
#if defined(TIM2)
        case (u32)TIM2:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_1, NO_REMAP, GPIO_AF_2) :
                          GPIO_Mode_FLOATING_Init(	 GPIOA, GPIO_Pin_1, NO_REMAP, GPIO_AF_2);
        }
        else {
            if (remapIdx == 0) {
                GPIOB_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_3, EXTI_MAPR_TIM2_PARTIAL1, GPIO_AF_2) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_3, EXTI_MAPR_TIM2_PARTIAL1, GPIO_AF_2);
            }
            if (remapIdx == 1) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_1, EXTI_MAPR_TIM2_PARTIAL2, GPIO_AF_2) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOA, GPIO_Pin_1, EXTI_MAPR_TIM2_PARTIAL2, GPIO_AF_2);
            }
            if (remapIdx == 2) {
                GPIOB_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_3, EXTI_MAPR_TIM2, GPIO_AF_2) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_3, EXTI_MAPR_TIM2, GPIO_AF_2);
            }
        }
        break;
#endif
#if defined(TIM3)
        case (u32)TIM3:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_7, NO_REMAP, GPIO_AF_1) :
                          GPIO_Mode_FLOATING_Init(	 GPIOA, GPIO_Pin_7, NO_REMAP, GPIO_AF_1);
        }
        else {
            if (remapIdx == 0) {
                GPIOB_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_5, EXTI_MAPR_TIM3_PARTIAL, GPIO_AF_1) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_5, EXTI_MAPR_TIM3_PARTIAL, GPIO_AF_1);
            }           
            if (remapIdx == 1) {
                GPIOC_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOC, GPIO_Pin_7, EXTI_MAPR_TIM3, GPIO_AF_1) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOC, GPIO_Pin_7, EXTI_MAPR_TIM3, GPIO_AF_1);
            }
        }
        break;
#endif
#if defined(TIM4)
        case (u32)TIM4:
        GPIOB_ClockEnable();
        (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_7, NO_REMAP, NO_FUNCAF) :
                	  GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_7, NO_REMAP, NO_FUNCAF);
        break;
#endif
#if defined(TIM8)
        case (u32)TIM8:
        if (!remapEn) {
            GPIOC_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOC, GPIO_Pin_7, NO_REMAP, GPIO_AF_3) :
                          GPIO_Mode_FLOATING_Init(	 GPIOC, GPIO_Pin_7, NO_REMAP, GPIO_AF_3);
        }
        else {
            if (remapIdx == 0) {
                GPIOC_ClockEnable();
                    (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOC, GPIO_Pin_1, NO_REMAP, GPIO_AF_6) :
                            	  GPIO_Mode_FLOATING_Init(   GPIOC, GPIO_Pin_1, NO_REMAP, GPIO_AF_6);
            }
        }
        break;
#endif
        default: break;
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////
#if defined(__MM32_MB032) || defined(__MM32_MB033)
void BSP_TIM_CH3_GPIO_Configure(TIM_TypeDef* tim, bool remapEn, u8 remapIdx, bool inoutMode)
{
    switch (*(u32*)&tim) {
        case (u32)TIM1:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_10, NO_REMAP, GPIO_AF_1) :\
                GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_10, NO_REMAP, GPIO_AF_1);
        }
        else {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_6, NO_REMAP, GPIO_AF_4) :\
                GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_6, NO_REMAP, GPIO_AF_4);
        }
        break;
        case (u32)TIM3:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_0, NO_REMAP, GPIO_AF_4) :\
                GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_0, NO_REMAP, GPIO_AF_4);
        }
        else {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_0, NO_REMAP, GPIO_AF_4) :\
                GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_0, NO_REMAP, GPIO_AF_4);
        }
        break;
        default: break;
    }
}
#else
////////////////////////////////////////////////////////////////////////////////
void BSP_TIM_CH3_GPIO_Configure(TIM_TypeDef* tim, bool remapEn, u8 remapIdx, bool inoutMode)
{
    switch (*(u32*)&tim) {
#if defined(TIM1)
        case (u32)TIM1:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_10, NO_REMAP, GPIO_AF_2) :
                    	  GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_10, 	NO_REMAP, GPIO_AF_2);
        }
        else {
            if (remapIdx == 0) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_10, EXTI_MAPR_TIM1_PARTIAL, GPIO_AF_2) :
                        	  GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_10, 	EXTI_MAPR_TIM1_PARTIAL, GPIO_AF_2);
            }
        }
        break;
#endif
#if defined(TIM2)
        case (u32)TIM2:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_2, NO_REMAP, GPIO_AF_2) :
                          GPIO_Mode_FLOATING_Init(	 GPIOA, GPIO_Pin_2, NO_REMAP, GPIO_AF_2);
        }
        else {
            if (remapIdx == 0) {
                GPIOB_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_2, EXTI_MAPR_TIM2_PARTIAL1, GPIO_AF_2) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOA, GPIO_Pin_2, EXTI_MAPR_TIM2_PARTIAL1, GPIO_AF_2);
            }
            if (remapIdx == 1) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_10, EXTI_MAPR_TIM2_PARTIAL2, GPIO_AF_2) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_10, EXTI_MAPR_TIM2_PARTIAL2, GPIO_AF_2);
            }
            if (remapIdx == 2) {
                GPIOB_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_10, EXTI_MAPR_TIM2, GPIO_AF_2) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_10, EXTI_MAPR_TIM2, GPIO_AF_2);
            }
        }
        break;
#endif
#if defined(TIM3)
        case (u32)TIM3:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_0, NO_REMAP, GPIO_AF_1) :
                          GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_0, NO_REMAP, GPIO_AF_1);
        }
        else {
            if (remapIdx == 0) {
                GPIOB_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_0, EXTI_MAPR_TIM3_PARTIAL, GPIO_AF_1) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_0, EXTI_MAPR_TIM3_PARTIAL, GPIO_AF_1);
            }           
            if (remapIdx == 1) {
                GPIOC_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOC, GPIO_Pin_8, EXTI_MAPR_TIM3, GPIO_AF_1) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOC, GPIO_Pin_8, EXTI_MAPR_TIM3, GPIO_AF_1);
            }
        }
        break;
#endif
#if defined(TIM4)
        case (u32)TIM4:
        GPIOB_ClockEnable();
        (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_8, NO_REMAP, NO_FUNCAF) :
                	  GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_8, NO_REMAP, NO_FUNCAF);
        break;
#endif
#if defined(TIM8)
        case (u32)TIM8:
        if (!remapEn) {
            GPIOC_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOC, GPIO_Pin_8, NO_REMAP, GPIO_AF_3) :
                          GPIO_Mode_FLOATING_Init(	 GPIOC, GPIO_Pin_8, NO_REMAP, GPIO_AF_3);
        }
        else {
            if (remapIdx == 0) {
                GPIOC_ClockEnable();
                    (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOC, GPIO_Pin_2, NO_REMAP, GPIO_AF_6) :
                            	  GPIO_Mode_FLOATING_Init(   GPIOC, GPIO_Pin_2, NO_REMAP, GPIO_AF_6);
            }
        }
        break;
#endif
        default: break;
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////
#if defined(__MM32_MB032) || defined(__MM32_MB033)
void BSP_TIM_CH4_GPIO_Configure(TIM_TypeDef* tim, bool remapEn, u8 remapIdx, bool inoutMode)
{
    switch (*(u32*)&tim) {
        case (u32)TIM1:
        GPIOA_ClockEnable();
        (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_7, NO_REMAP, GPIO_AF_4) :\
            GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_7, NO_REMAP, GPIO_AF_4);
        break;
        default: break;
    }
}
#else
////////////////////////////////////////////////////////////////////////////////
void BSP_TIM_CH4_GPIO_Configure(TIM_TypeDef* tim, bool remapEn, u8 remapIdx, bool inoutMode)
{
    switch (*(u32*)&tim) {
        case (u32)TIM1:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_11, NO_REMAP, GPIO_AF_2) :
                    	  GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_11, 	NO_REMAP, GPIO_AF_2);
        }
        else {
            if (remapIdx == 0) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_11, EXTI_MAPR_TIM1_PARTIAL, GPIO_AF_2) :
                        	  GPIO_Mode_FLOATING_Init(GPIOA, GPIO_Pin_11, 	EXTI_MAPR_TIM1_PARTIAL, GPIO_AF_2);
            }
        }
        break;
        case (u32)TIM2:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_3, NO_REMAP, GPIO_AF_2) :
                          GPIO_Mode_FLOATING_Init(	 GPIOA, GPIO_Pin_3, NO_REMAP, GPIO_AF_2);
        }
        else {
            if (remapIdx == 0) {
                GPIOB_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_3, EXTI_MAPR_TIM2_PARTIAL1, GPIO_AF_2) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOA, GPIO_Pin_3, EXTI_MAPR_TIM2_PARTIAL1, GPIO_AF_2);
            }
            if (remapIdx == 1) {
                GPIOA_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_11, EXTI_MAPR_TIM2_PARTIAL2, GPIO_AF_2) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_11, EXTI_MAPR_TIM2_PARTIAL2, GPIO_AF_2);
            }
            if (remapIdx == 2) {
                GPIOB_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_11, EXTI_MAPR_TIM2, GPIO_AF_2) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_11, EXTI_MAPR_TIM2, GPIO_AF_2);
            }
        }
        break;
        case (u32)TIM3:
        if (!remapEn) {
            GPIOA_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_1, NO_REMAP, GPIO_AF_1) :
                          GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_1, NO_REMAP, GPIO_AF_1);
        }
        else {
            if (remapIdx == 0) {
                GPIOB_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_1, EXTI_MAPR_TIM3_PARTIAL, GPIO_AF_1) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_1, EXTI_MAPR_TIM3_PARTIAL, GPIO_AF_1);
            }
#if defined(GPIOC)            
            if (remapIdx == 1) {
                GPIOC_ClockEnable();
                (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOC, GPIO_Pin_9, EXTI_MAPR_TIM3, GPIO_AF_1) :
                        	  GPIO_Mode_FLOATING_Init(	 GPIOC, GPIO_Pin_9, EXTI_MAPR_TIM3, GPIO_AF_1);
            }
#endif            
        }
        break;
#if defined(TIM4)
        case (u32)TIM4:
        GPIOB_ClockEnable();
        (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_9, NO_REMAP, NO_FUNCAF) :
                	  GPIO_Mode_FLOATING_Init(	 GPIOB, GPIO_Pin_9, NO_REMAP, NO_FUNCAF);
        break;
#endif
#if defined(TIM8)
        case (u32)TIM8:
        if (!remapEn) {
            GPIOC_ClockEnable();
            (inoutMode) ? GPIO_Mode_AF_PP_20MHz_Init(GPIOC, GPIO_Pin_9, NO_REMAP, GPIO_AF_3) :
                          GPIO_Mode_FLOATING_Init(	 GPIOC, GPIO_Pin_9, NO_REMAP, GPIO_AF_3);
        }
        break;
#endif
        default: break;
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////
//  @brief  Timer PWM-Mode GPIO Configure
//  @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 14, 16 or 17 to select the TIM peripheral.
//  @param  remapEn:  true or false to select remap function.
//  @param  remapIdx: select Pin remap source.
//  @retval None.
////////////////////////////////////////////////////////////////////////////////
void BSP_TIM_PWM_GPIO_Configure(TIM_TypeDef* tim, u8 ch, bool remapEn, u8 remapIdx)
{
    if (ch & 0x01)
        BSP_TIM_CH1_GPIO_Configure(tim, remapEn, remapIdx, 1);                         //As output
    if (ch & 0x02)
        BSP_TIM_CH2_GPIO_Configure(tim, remapEn, remapIdx, 1);                         //As output
    if (ch & 0x04)
        BSP_TIM_CH3_GPIO_Configure(tim, remapEn, remapIdx, 1);                         //As output
    if (ch & 0x08)
        BSP_TIM_CH4_GPIO_Configure(tim, remapEn, remapIdx, 1);                         //As output
}

////////////////////////////////////////////////////////////////////////////////
//  @brief  Timer CapturePulse-Mode GPIO Configure
//  @param  TIMx: where x can be 1, 2, 3, 4 or 8 to select the TIM peripheral.
//  @param  remapEn:  true or false to select remap function.
//  @param  remapIdx: select Pin remap source.
//  @retval None.
////////////////////////////////////////////////////////////////////////////////
void BSP_TIM_CapturePulse_GPIO_Configure(TIM_TypeDef* tim, u8 ch, bool remapEn, u8 remapIdx)
{
    BSP_TIM_CH2_GPIO_Configure(tim, remapEn, remapIdx, 0);
}

////////////////////////////////////////////////////////////////////////////////
//  @brief  Timer CapturePWM-Mode GPIO Configure
//  @param  TIMx: where x can be 1, 2, 3, 4 or 8 to select the TIM peripheral.
//  @param  remapEn:  true or false to select remap function.
//  @param  remapIdx: select Pin remap source.
//  @retval None.
////////////////////////////////////////////////////////////////////////////////
void BSP_TIM_CapturePWM_GPIO_Configure(TIM_TypeDef* tim, u8 ch, bool remapEn, u8 remapIdx)
{
    BSP_TIM_CH1_GPIO_Configure(tim, remapEn, remapIdx, 0);
}

////////////////////////////////////////////////////////////////////////////////
//  @brief  Timer Encoder-Mode GPIO Configure
//  @param  TIMx: where x can be 1, 2, 3, 4 or 8 to select the TIM peripheral.
//  @param  remapEn:  true or false to select remap function.
//  @param  remapIdx: select Pin remap source.
//  @retval None.
////////////////////////////////////////////////////////////////////////////////
void BSP_TIM_Encoder_GPIO_Configure(TIM_TypeDef* tim, u8 ch, bool remapEn, u8 remapIdx)
{
    BSP_TIM_CH1_GPIO_Configure(tim, remapEn, remapIdx, 0);
    BSP_TIM_CH2_GPIO_Configure(tim, remapEn, remapIdx, 0);
}

////////////////////////////////////////////////////////////////////////////////
//  @brief  Timer OnePulse-Mode GPIO Configure
//  @param  TIMx: where x can be 1, 2, 3, 4 or 8 to select the TIM peripheral.
//  @param  remapEn:  true or false to select remap function.
//  @param  remapIdx: select Pin remap source.
//  @retval None.
////////////////////////////////////////////////////////////////////////////////
void BSP_TIM_OnePulse_GPIO_Configure(TIM_TypeDef* tim, u8 ch, bool remapEn, u8 remapIdx)
{

    BSP_TIM_CH1_GPIO_Configure(tim, remapEn, remapIdx, 1);
    //BSP_TIM_CH2_GPIO_Configure(tim, remapEn, remapIdx, 0);
}

////////////////////////////////////////////////////////////////////////////////
//  @brief  Timer 6-step Mode GPIO Configure
//  @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
//  @param  remapEn:  true or false to select remap function.
//  @param  remapIdx: select Pin remap source.
//  @retval None.
////////////////////////////////////////////////////////////////////////////////
void BSP_TIM_6Step_GPIO_Configure(TIM_TypeDef* tim, u8 ch, bool remapEn, u8 remapIdx)
{
    //Todo: just config TIM1
    GPIOA_ClockEnable();
    GPIOB_ClockEnable();

#if defined(__MM32_MB032) || defined(__MM32_MB033)
    /* TIM1 CH1 ~ CH3 */
    GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_6,  NO_REMAP, GPIO_AF_1);
    GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_8,  NO_REMAP, GPIO_AF_1);
    GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_10, NO_REMAP, GPIO_AF_1);
    /* TIM1 CH1N ~ CH3N */
    GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_7,  NO_REMAP, GPIO_AF_1);
    GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_9,  NO_REMAP, GPIO_AF_1);
    GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_0,  NO_REMAP, GPIO_AF_2);
    /* TIM1 Brake input */
    //GPIO_Mode_FLOATING_Init   (GPIOA, GPIO_Pin_4,  NO_REMAP, GPIO_AF_2);
#else
    /* TIM1 CH1 ~ CH3 */
    GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_8,  NO_REMAP, GPIO_AF_2);
    GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_9,  NO_REMAP, GPIO_AF_2);
    GPIO_Mode_AF_PP_20MHz_Init(GPIOA, GPIO_Pin_10, NO_REMAP, GPIO_AF_2);
    /* TIM1 CH1N ~ CH3N */
    GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_13, NO_REMAP, GPIO_AF_2);
    GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_14, NO_REMAP, GPIO_AF_2);
    GPIO_Mode_AF_PP_20MHz_Init(GPIOB, GPIO_Pin_15, NO_REMAP, GPIO_AF_2);
    /* TIM1 Brake input */
    //GPIO_Mode_FLOATING_Init   (GPIOB, GPIO_Pin_12, NO_REMAP, GPIO_AF_2);
#endif
}

/// @}

/// @}

/// @}
