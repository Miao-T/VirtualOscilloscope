////////////////////////////////////////////////////////////////////////////////
/// @file     BSP_SPI.C
/// @author   Z Yan
/// @version  v2.0.0
/// @date     2019-03-13
/// @brief    THIS FILE PROVIDES ALL THE SPI BSP LAYER FUNCTIONS.
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
#define _BSP_SPI_C_

// Files includes  -------------------------------------------------------------
#include "hal_rcc.h"
#include "hal_gpio.h"
#include "hal_spi.h"

#include "bsp.h"
#include "bsp_spi.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Board_Support_Package
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup SPI_BSP
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup SPI_Exported_Functions
/// @{

#if defined(SPI1)
void BSP_SPI1_NSS_ENABLE(void)  { GPIO_ResetBits(SPI1_NSS_PORT, SPI1_NSS_BIT); nssStatus = true;  }
void BSP_SPI1_NSS_DISABLE(void) { GPIO_SetBits(SPI1_NSS_PORT, SPI1_NSS_BIT);   nssStatus = false; }
#endif

#if defined(SPI2)
void BSP_SPI2_NSS_ENABLE(void)  { GPIO_ResetBits(SPI2_NSS_PORT, SPI2_NSS_BIT); nssStatus = true;  }
void BSP_SPI2_NSS_DISABLE(void) { GPIO_SetBits(SPI2_NSS_PORT, SPI2_NSS_BIT);   nssStatus = false; }
#endif

void BSP_SPI_NSS_Configure(SPI_TypeDef* SPIx, FunctionalState newState)
{
#if defined(SPI1)
	if (SPIx == SPI1) (newState) ? BSP_SPI1_NSS_ENABLE() : BSP_SPI1_NSS_DISABLE();
#endif
#if defined(SPI2)
	if (SPIx == SPI2) (newState) ? BSP_SPI2_NSS_ENABLE() : BSP_SPI2_NSS_DISABLE();
#endif
}

void BSP_SPI_GPIO_Configure(SPI_TypeDef* SPIx, bool master, bool nss)
{
#if defined(SPI1)
    if(SPIx == SPI1){
        GPIOA_ClockEnable();
        GPIOB_ClockEnable();
        if (master) {
            SPI1_MASTER_NSS_SW_CTL(!nss == SPI_NSS_Soft);
            SPI1_MASTER_SCK_CONFIG();  
            SPI1_MASTER_MISO_CONFIG();
            SPI1_MASTER_MOSI_CONFIG();
            SPI1_MASTER_NSS_CONFIG();
        } else {
            SPI1_SLAVER_SCK_CONFIG();
            SPI1_SLAVER_MISO_CONFIG();
            SPI1_SLAVER_MOSI_CONFIG();
            SPI1_SLAVER_NSS_CONFIG();
        }
    }
#endif
#if defined(SPI2)
    if (SPIx == SPI2) {
        GPIOA_ClockEnable();
        GPIOB_ClockEnable();
        if (master) {
            SPI2_MASTER_NSS_SW_CTL(!nss == SPI_NSS_Soft);
            SPI2_MASTER_SCK_CONFIG();  
            SPI2_MASTER_MISO_CONFIG();
            SPI2_MASTER_MOSI_CONFIG();
            SPI2_MASTER_NSS_CONFIG();
        } else {
            SPI2_SLAVER_SCK_CONFIG();
            SPI2_SLAVER_MISO_CONFIG();
            SPI2_SLAVER_MOSI_CONFIG();
            SPI2_SLAVER_NSS_CONFIG();
        }
    }
#endif
#if !defined(SPI1) && !defined(SPI2)
    #error "No matches to any SPI peripherals!"
#endif
}


/// @}

/// @}

/// @}

