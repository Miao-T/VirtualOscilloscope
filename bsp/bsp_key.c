////////////////////////////////////////////////////////////////////////////////
/// @file     BSP_KEY.C
/// @author   AE Team
/// @version  v2.0.0
/// @date     2019-03-13
/// @brief    THIS FILE PROVIDES ALL THE KEY BSP LAYER FUNCTIONS.
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
#define _BSP_KEY_C_

// Files includes  -------------------------------------------------------------
#include "string.h"

#include "hal_gpio.h"
#include "hal_nvic.h"
#include "hal_rcc.h"

#include "bsp.h"
#include "bsp_key.h"
#include "common.h"


/* -----------------------------------------------------------------------------
----------  P e r i p h e r a l s    i n i t i a l i z a t i o n   -------------
----------------------------------------------------------------------------- */
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Board_Support_Package
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup KEY_BSP
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup KEY_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initialize KEY.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BSP_KEY_Configure(void)
{
	KEY1_CONFIG;
	KEY2_CONFIG;
	KEY3_CONFIG;
	KEY4_CONFIG;
}

/* -----------------------------------------------------------------------------
------------------   F u n c t i o n     I m p l e m e n t  --------------------
----------------------------------------------------------------------------- */
////////////////////////////////////////////////////////////////////////////////
/// @brief  get key is set or reset.
/// @param  None.
/// @retval bool: 1: key is set
///			0: kei is reset
////////////////////////////////////////////////////////////////////////////////
bool Key1(void)	{ return KEY1_VAL;}
bool Key2(void)	{ return KEY2_VAL;}
bool Key3(void)	{ return KEY3_VAL;}
bool Key4(void)	{ return KEY4_VAL;}

void BSP_KeyTick(void)
{
    for (u8 i = 0; i < 4; i++) {
        if (keyDelayFlag[i] && KeyCurrentStatus[i] != KEY_PRESSING) keyDelayCnt[i]++;
    }
}

void BSP_KeyPressStatusPreemp(void)
{
    for (u8 i = 0; i < 4; i++) {
        if(KeyCurrentStatus[i] == KEY_PRESSING || KeyCurrentStatus[i] == KEY_DOWNED) 
            KeyCurrentStatus[i] = KEY_PRESSED;    
    }
}

void BSP_KeyFuncSet(u8 key, void (*down)(void), void (*pressing)(void))
{
    keyDownFunc[--key]   = down;
    keyPressingFunc[key] = pressing;
}

void BSP_Key(u8 key) 
{
    static bool (*keyPtr)(void) = NULL;
    
    switch (--key) {
        case 0: keyPtr = Key1; break;
        case 1: keyPtr = Key2; break;
        case 2: keyPtr = Key3; break;
        case 3: keyPtr = Key4; break;
        default: keyPtr = NULL; break;
    }
    
    if ((keyPtr != NULL) && keyPtr()) {
        keyDelayFlag[key] = true;
        if (keyDelayCnt[key] >= 20 && KeyCurrentStatus[key] == KEY_RELEASE) {
            BSP_KeyPressStatusPreemp();
            KeyCurrentStatus[key] = KEY_DOWN;
            keyDelayFlag[key] = false;
            keyDelayCnt[key] = 0;
        }
        if (keyDelayCnt[key] >= 1000 && (KeyCurrentStatus[key] == KEY_DOWN || KeyCurrentStatus[key] == KEY_DOWNED)) {
            BSP_KeyPressStatusPreemp();
            KeyCurrentStatus[key] = KEY_PRESSING;
        }
    } else {
        keyDelayFlag[key] = false;
        keyDelayCnt[key] = 0;
        KeyCurrentStatus[key] = KEY_RELEASE;
    }
    
    if (KeyCurrentStatus[key] == KEY_DOWN) {
        KeyCurrentStatus[key] = KEY_DOWNED;
        if(keyDownFunc[key] != NULL)
            keyDownFunc[key]();
    }
    
    if (KeyCurrentStatus[key] == KEY_PRESSING) {
        if(keyPressingFunc[key] != NULL)
            keyPressingFunc[key]();
    }
}

/// @}

/// @}

/// @}

