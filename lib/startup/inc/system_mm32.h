////////////////////////////////////////////////////////////////////////////////
/// @file    SYSTEM_MM32.H
/// @author  AE TEAM
/// @version V2.0.0
/// @date    2018-08-01
/// @brief   THIS FILE PROVIDES ALL THE SYSTEM FIRMWARE FUNCTIONS.
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
/// <H2><CENTER>&COPY; COPYRIGHT 2018 MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////


// Define to prevent recursive inclusion  --------------------------------------
#ifndef __SYSTEM_MM32_H
#define __SYSTEM_MM32_H

// Files includes  -------------------------------------------------------------
#include "types.h"

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Example_Layer
/// @brief MM32 Example Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_RESOURCE
/// @brief MM32 Examples resource modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Constants
/// @{


#define IDCODE_DEVID_MASK    	(0x00000FFFU)
#define COREID_MASK				(0x00000070U)
#define MCUID_MM0N1				(0xCC568091U)
#define MCUID_MM0P1				(0xCC56A091U)
#define MCUID_MM0P2             (0xCC56A097U)
#define MCUID_MM0Q1				(0xCC4460B1U)
#define MCUID_MM0M1				(0xCC567071U)
#define MCUID_MM3O1				(0xCC9AA0A1U)
#define MCUID_MM3M1				(0xCC888045U)
#define MCUID_MM3N1				(0xCC888047U)

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Enumeration
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief MCU ID enumerate definition.
/// @anchor EM_MCUID
////////////////////////////////////////////////////////////////////////////////
typedef enum {
	Unknown,
	emMCUID_MM32L073,
	emMCUID_MM32SPIN27,
	emMCUID_MM32F031,
	emMCUID_MM32F031_OLD,
	emMCUID_MM32L395,
	emMCUID_MM32F103_OLD,
	emMCUID_MM32L373
}EM_MCUID;

////////////////////////////////////////////////////////////////////////////////
/// @brief Systick enable enumerate definition.
/// @anchor EM_SYSTICK
////////////////////////////////////////////////////////////////////////////////
typedef enum {
	emSYSTICK_Off,
	emSYSTICK_On = !emSYSTICK_Off
} EM_SYSTICK;


////////////////////////////////////////////////////////////////////////////////
/// @brief  System clock configuration
////////////////////////////////////////////////////////////////////////////////
typedef enum {
#if defined(__MT304) || defined(__MZ306) || defined(__MZ308) || defined(__MZ310)
                                        //  Flash_Latency   Mul Div Sw  Src
    SYSCLK_HSI_6d       = 0x00000,      //	            0   0   0   0   0
    SYSCLK_HSI_12MHz    = 0x00020,      //	            0   0   0   2   0
    SYSCLK_HSI_24MHz    = 0x01020,      //	            0   1   0   2   0
    SYSCLK_HSI_48MHz    = 0x13020,      //	            1   3   0   2   0
    SYSCLK_HSI_72MHz    = 0x25020,      //	            2   5   0   2   0
    SYSCLK_HSI_96MHz    = 0x37020,      //	            3   7   0   2   0
    SYSCLK_HSE_1x       = 0x00011,      //	            0   0   0   1   1
    SYSCLK_HSE_3x       = 0x02021,      //	            0   2   0   2   1
    SYSCLK_HSE_4x       = 0x13021,      //	            1   3   0   2   1
    SYSCLK_HSE_6x       = 0x15021,      //	            1   5   0   2   1
    SYSCLK_HSE_7x       = 0x26021,      //	            2   6   0   2   1
    SYSCLK_HSE_9x       = 0x28021,      //	            2   8   0   2   1
    SYSCLK_HSE_12x      = 0x3B021,      //	            3   1   0   2   1
#endif
#if defined(__MZ309) || defined(__MZ311)
    SYSCLK_HSI_6d       = 0x00000,      //              0   0   0   0   0
    SYSCLK_HSE_1x       = 0x00011,      //              0   0   0   1   1
    SYSCLK_HSI_48MHz    = 0x10020,      //              1   0   0   2   0
    SYSCLK_HSI_72MHz    = 0x20020,      //              2   0   0   2   0
    SYSCLK_LSI_40KHz    = 0x00032,      //              0   0   0   3   2   
#endif
} EM_SystemClock;

typedef void (*AppTick_fun)(void);

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Variables
/// @{
#ifdef _SYSTEM_MM32_C_
#define GLOBAL





GLOBAL int nTimeOutCnt = 0;

GLOBAL bool sysTickFlag1mS = false;
GLOBAL u32 sysTickCnt1mS = 0;

GLOBAL bool sysTickFlag = false;
GLOBAL u32 sysTickCnt = 0;

GLOBAL bool tickFlag = false;
GLOBAL u32 tickCnt = 0;

#else
#define GLOBAL extern

GLOBAL bool sysTickFlag1mS;
GLOBAL u32 sysTickCnt1mS;
GLOBAL int nTimeOutCnt;
GLOBAL bool sysTickFlag;
GLOBAL u32 sysTickCnt;
GLOBAL bool tickFlag;
GLOBAL u32 tickCnt;


GLOBAL u16 g_KEY_buffer[8];




#endif

GLOBAL bool sysTickFlag;
GLOBAL u32 sysTickCnt;
GLOBAL EM_MCUID MCUID;

GLOBAL AppTick_fun AppTickPtr;

#undef GLOBAL

/// @}


////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Functions
/// @{






//void PutKeyBuffer(u8 key);


void SysTickLED(void);

EM_MCUID DBGMCU_GetDEVID(void);
EM_MCUID SystemInit(EM_SystemClock ClockSoucre, EM_SYSTICK enable , AppTick_fun address);
EM_MCUID SetSystemClock(EM_SYSTICK enable , AppTick_fun callbackPtr);

/// @}


/// @}

/// @}


////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
