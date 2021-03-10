////////////////////////////////////////////////////////////////////////////////
/// @file     BSP_I2C.H
/// @author   S Yi
/// @version  v2.0.0
/// @date     2019-03-13
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE I2C
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

// Define to prevent recursive inclusion  --------------------------------------
#ifndef __BSP_I2C_H
#define __BSP_I2C_H


////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Board_Support_Package
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_BSP
/// @brief  I2C BSP modules
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_Exported_Types
/// @{

#if defined(__MZ311)

#if defined(__MM32_MB032) || defined(__MM32_MB033)
#define I2C_GPIO_CONFIG 3
#endif

#ifndef I2C_GPIO_CONFIG
#define I2C_GPIO_CONFIG 0
#endif

#if (I2C_GPIO_CONFIG == 0)
    #define I2C_SCL_PORT    GPIOA
    #define I2C_SCL_PIN     GPIO_Pin_0
    #define I2C_SCL_AF      GPIO_AF_3

    #define I2C_SDA_PORT    GPIOA
    #define I2C_SDA_PIN     GPIO_Pin_1
    #define I2C_SDA_AF      GPIO_AF_3
#endif
#if (I2C_GPIO_CONFIG == 1)
    #define I2C_SCL_PORT    GPIOA
    #define I2C_SCL_PIN     GPIO_Pin_5
    #define I2C_SCL_AF      GPIO_AF_3

    #define I2C_SDA_PORT    GPIOA
    #define I2C_SDA_PIN     GPIO_Pin_4
    #define I2C_SDA_AF      GPIO_AF_3
#endif

#if (I2C_GPIO_CONFIG == 2)
    #define I2C_SCL_PORT    GPIOA
    #define I2C_SCL_PIN     GPIO_Pin_0
    #define I2C_SCL_AF      GPIO_AF_3

    #define I2C_SDA_PORT    GPIOA
    #define I2C_SDA_PIN     GPIO_Pin_4
    #define I2C_SDA_AF      GPIO_AF_3
#endif

#if (I2C_GPIO_CONFIG == 3)
    #define I2C_SCL_PORT    GPIOA
    #define I2C_SCL_PIN     GPIO_Pin_5
    #define I2C_SCL_AF      GPIO_AF_3

    #define I2C_SDA_PORT    GPIOA
    #define I2C_SDA_PIN     GPIO_Pin_1
    #define I2C_SDA_AF      GPIO_AF_3
#endif

#endif

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_Exported_Variables
/// @{
#ifdef _BSP_I2C_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_Exported_Functions
/// @{

void BSP_I2C_GPIO_Configure(I2C_TypeDef* I2Cx, bool remapEn, u8 remapIdx);

/// @}



/// @}

/// @}



////////////////////////////////////////////////////////////////////////////////
#endif /* __BSP_I2C_H */
////////////////////////////////////////////////////////////////////////////////
