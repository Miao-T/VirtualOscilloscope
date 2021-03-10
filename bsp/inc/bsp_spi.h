////////////////////////////////////////////////////////////////////////////////
/// @file     BSP_SPI.H
/// @author   Z Yan
/// @version  v2.0.0
/// @date     2019-03-13
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE SPI
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
#ifndef __BSP_SPI_H
#define __BSP_SPI_H


////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Board_Support_Package
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup SPI_BSP
/// @brief  SPI BSP modules
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @defgroup SPI_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
// SPI1
#define SPI1_CONFIG     0

#if (SPI1_CONFIG == 0)
    #define SPI1_SCK_PORT   GPIOA       // GPIOB      
    #define SPI1_SCK_BIT    GPIO_Pin_5  // GPIO_Pin_3 
    #define SPI1_SCK_AF     GPIO_AF_0   // GPIO_AF_0 

    #define SPI1_MISO_PORT  GPIOA       // GPIOB
    #define SPI1_MISO_BIT   GPIO_Pin_6  // GPIO_Pin_4
    #define SPI1_MISO_AF    GPIO_AF_0   // GPIO_AF_0

    #define SPI1_MOSI_PORT  GPIOA       // GPIOB
    #define SPI1_MOSI_BIT   GPIO_Pin_7  // GPIO_Pin_5
    #define SPI1_MOSI_AF    GPIO_AF_0   // GPIO_AF_0

    #define SPI1_NSS_PORT   GPIOA       // GPIOA
    #define SPI1_NSS_BIT    GPIO_Pin_4  // GPIO_Pin_15
    #define SPI1_NSS_AF     GPIO_AF_0   // GPIO_AF_0
#endif
#if (SPI1_CONFIG == 1)
    #define SPI1_SCK_PORT   GPIOB      
    #define SPI1_SCK_BIT    GPIO_Pin_3 
    #define SPI1_SCK_AF     GPIO_AF_0 

    #define SPI1_MISO_PORT  GPIOB
    #define SPI1_MISO_BIT   GPIO_Pin_4
    #define SPI1_MISO_AF    GPIO_AF_0

    #define SPI1_MOSI_PORT  GPIOB
    #define SPI1_MOSI_BIT   GPIO_Pin_5
    #define SPI1_MOSI_AF    GPIO_AF_0

    #define SPI1_NSS_PORT   GPIOA
    #define SPI1_NSS_BIT    GPIO_Pin_15
    #define SPI1_NSS_AF     GPIO_AF_0
#endif

#define SPI1_MASTER_SCK_CONFIG()    {GPIO_Mode_AF_PP_50MHz_Init(SPI1_SCK_PORT,  SPI1_SCK_BIT,  NO_REMAP, SPI1_SCK_AF); }
#define SPI1_MASTER_MISO_CONFIG()   {GPIO_Mode_IPU_Init        (SPI1_MISO_PORT, SPI1_MISO_BIT, NO_REMAP, SPI1_MISO_AF);}
#define SPI1_MASTER_MOSI_CONFIG()   {GPIO_Mode_AF_PP_50MHz_Init(SPI1_MOSI_PORT, SPI1_MOSI_BIT, NO_REMAP, SPI1_MOSI_AF);}
#define SPI1_MASTER_NSS_CONFIG()    {exGPIO_PinAFConfig        (SPI1_NSS_PORT,  SPI1_NSS_BIT,  NO_REMAP, SPI1_NSS_AF); }
#define SPI1_MASTER_NSS_SW_CTL(x)   {if(x) GPIO_Mode_AF_PP_50MHz_Init(SPI1_NSS_PORT, SPI1_NSS_BIT,NO_REMAP, SPI1_NSS_AF);\
                                      else {\
                                          GPIO_SetBits(SPI1_NSS_PORT, SPI1_NSS_BIT);\
                                          GPIO_AF_Init(SPI1_NSS_PORT, SPI1_NSS_BIT, GPIO_Mode_Out_PP, GPIO_Speed_50MHz, NO_REMAP, SPI1_NSS_AF);\
                                      }}

#define SPI1_SLAVER_SCK_CONFIG()    {GPIO_Mode_FLOATING_Init   (SPI1_SCK_PORT,  SPI1_SCK_BIT,  NO_REMAP, SPI1_SCK_AF); }
#define SPI1_SLAVER_MISO_CONFIG()   {GPIO_Mode_AF_PP_50MHz_Init(SPI1_MISO_PORT, SPI1_MISO_BIT, NO_REMAP, SPI1_MISO_AF);}
#define SPI1_SLAVER_MOSI_CONFIG()   {GPIO_Mode_IPU_Init        (SPI1_MOSI_PORT, SPI1_MOSI_BIT, NO_REMAP, SPI1_MOSI_AF);}
#define SPI1_SLAVER_NSS_CONFIG()    {GPIO_Mode_IPU_Init        (SPI1_NSS_PORT,  SPI1_NSS_BIT,  NO_REMAP, SPI1_NSS_AF); }

////////////////////////////////////////////////////////////////////////////////
// SPI2

#define SPI2_CONFIG     0

#if (SPI2_CONFIG == 0)
    #define SPI2_SCK_PORT   GPIOB       // GPIOB       // GPIOB       // GPIOB       // GPIOB      
    #define SPI2_SCK_BIT    GPIO_Pin_13 // GPIO_Pin_12 // GPIO_Pin_14 // GPIO_Pin_15 // GPIO_Pin_10
    #define SPI2_SCK_AF     GPIO_AF_0   // GPIO_AF_1   // GPIO_AF_3   // GPIO_AF_4   // GPIO_AF_5  

    #define SPI2_MISO_PORT  GPIOB       // GPIOB       // GPIOB       // GPIOB       // GPIOA       // GPIOA       
    #define SPI2_MISO_BIT   GPIO_Pin_14 // GPIO_Pin_13 // GPIO_Pin_15 // GPIO_Pin_12 // GPIO_Pin_12 // GPIO_Pin_13 
    #define SPI2_MISO_AF    GPIO_AF_0   // GPIO_AF_1   // GPIO_AF_3   // GPIO_AF_4   // GPIO_AF_4   // GPIO_AF_4   

    #define SPI2_MOSI_PORT  GPIOB       // GPIOB       // GPIOB       // GPIOB      
    #define SPI2_MOSI_BIT   GPIO_Pin_15 // GPIO_Pin_14 // GPIO_Pin_12 // GPIO_Pin_13
    #define SPI2_MOSI_AF    GPIO_AF_0   // GPIO_AF_1   // GPIO_AF_3   // GPIO_AF_4  

    #if defined(__MT304) || defined(__MZ306) || defined(__MT307) || defined(__MZ308) || defined(__MZ310)
    #define SPI2_NSS_PORT   GPIOB       // GPIOB       // GPIOB       // GPIOB       // GPIOB      
    #define SPI2_NSS_BIT    GPIO_Pin_12 // GPIO_Pin_15 // GPIO_Pin_13 // GPIO_Pin_14 // GPIO_Pin_9
    #define SPI2_NSS_AF     GPIO_AF_0   // GPIO_AF_1   // GPIO_AF_3   // GPIO_AF_4   // GPIO_AF_5  
    #endif

    #if defined(__MZ309)
    #define SPI2_NSS_PORT   GPIOA       // GPIOA       // GPIOB       // GPIOB       // GPIOB       // GPIOB       // GPIOB     
    #define SPI2_NSS_BIT    GPIO_Pin_0  // GPIO_Pin_2  // GPIO_Pin_12 // GPIO_Pin_15 // GPIO_Pin_13 // GPIO_Pin_14 // GPIO_Pin_9
    #define SPI2_NSS_AF     GPIO_AF_3   // GPIO_AF_3   // GPIO_AF_0   // GPIO_AF_1   // GPIO_AF_3   // GPIO_AF_4   // GPIO_AF_5 
    #endif
#endif
#if (SPI2_CONFIG == 1)
    #define SPI2_SCK_PORT   GPIOB       // GPIOB       // GPIOB       // GPIOB      
    #define SPI2_SCK_BIT    GPIO_Pin_12 // GPIO_Pin_14 // GPIO_Pin_15 // GPIO_Pin_10
    #define SPI2_SCK_AF     GPIO_AF_1   // GPIO_AF_3   // GPIO_AF_4   // GPIO_AF_5  

    #define SPI2_MISO_PORT  GPIOB       // GPIOB       // GPIOB       // GPIOA       // GPIOA       
    #define SPI2_MISO_BIT   GPIO_Pin_13 // GPIO_Pin_15 // GPIO_Pin_12 // GPIO_Pin_12 // GPIO_Pin_13 
    #define SPI2_MISO_AF    GPIO_AF_1   // GPIO_AF_3   // GPIO_AF_4   // GPIO_AF_4   // GPIO_AF_4   

    #define SPI2_MOSI_PORT  GPIOB       // GPIOB       // GPIOB      
    #define SPI2_MOSI_BIT   GPIO_Pin_14 // GPIO_Pin_12 // GPIO_Pin_13
    #define SPI2_MOSI_AF    GPIO_AF_1   // GPIO_AF_3   // GPIO_AF_4  

    #if defined(__MT304) || defined(__MZ306) || defined(__MT307) || defined(__MZ308) || defined(__MZ310)
    #define SPI2_NSS_PORT   GPIOB       // GPIOB       // GPIOB       // GPIOB      
    #define SPI2_NSS_BIT    GPIO_Pin_15 // GPIO_Pin_13 // GPIO_Pin_14 // GPIO_Pin_9
    #define SPI2_NSS_AF     GPIO_AF_1   // GPIO_AF_3   // GPIO_AF_4   // GPIO_AF_5  
    #endif

    #if defined(__MZ309)
    #define SPI2_NSS_PORT   GPIOA       // GPIOB       // GPIOB       // GPIOB       // GPIOB       // GPIOB     
    #define SPI2_NSS_BIT    GPIO_Pin_2  // GPIO_Pin_12 // GPIO_Pin_15 // GPIO_Pin_13 // GPIO_Pin_14 // GPIO_Pin_9
    #define SPI2_NSS_AF     GPIO_AF_3   // GPIO_AF_0   // GPIO_AF_1   // GPIO_AF_3   // GPIO_AF_4   // GPIO_AF_5 
    #endif
#endif
#if (SPI2_CONFIG == 2)
    #define SPI2_SCK_PORT   GPIOB       // GPIOB       // GPIOB      
    #define SPI2_SCK_BIT    GPIO_Pin_14 // GPIO_Pin_15 // GPIO_Pin_10
    #define SPI2_SCK_AF     GPIO_AF_3   // GPIO_AF_4   // GPIO_AF_5  

    #define SPI2_MISO_PORT  GPIOB       // GPIOB       // GPIOA       // GPIOA       
    #define SPI2_MISO_BIT   GPIO_Pin_15 // GPIO_Pin_12 // GPIO_Pin_12 // GPIO_Pin_13 
    #define SPI2_MISO_AF    GPIO_AF_3   // GPIO_AF_4   // GPIO_AF_4   // GPIO_AF_4   

    #define SPI2_MOSI_PORT  GPIOB       // GPIOB      
    #define SPI2_MOSI_BIT   GPIO_Pin_12 // GPIO_Pin_13
    #define SPI2_MOSI_AF    GPIO_AF_3   // GPIO_AF_4  

    #if defined(__MT304) || defined(__MZ306) || defined(__MT307) || defined(__MZ308) || defined(__MZ310)
    #define SPI2_NSS_PORT   GPIOB       // GPIOB       // GPIOB      
    #define SPI2_NSS_BIT    GPIO_Pin_13 // GPIO_Pin_14 // GPIO_Pin_9
    #define SPI2_NSS_AF     GPIO_AF_3   // GPIO_AF_4   // GPIO_AF_5  
    #endif

    #if defined(__MZ309)
    #define SPI2_NSS_PORT   GPIOB       // GPIOB       // GPIOB       // GPIOB       // GPIOB     
    #define SPI2_NSS_BIT    GPIO_Pin_12 // GPIO_Pin_15 // GPIO_Pin_13 // GPIO_Pin_14 // GPIO_Pin_9
    #define SPI2_NSS_AF     GPIO_AF_0   // GPIO_AF_1   // GPIO_AF_3   // GPIO_AF_4   // GPIO_AF_5 
    #endif
#endif
#if (SPI2_CONFIG == 3)
    #define SPI2_SCK_PORT   GPIOB       // GPIOB      
    #define SPI2_SCK_BIT    GPIO_Pin_15 // GPIO_Pin_10
    #define SPI2_SCK_AF     GPIO_AF_4   // GPIO_AF_5  

    #define SPI2_MISO_PORT  GPIOB       // GPIOA       // GPIOA       
    #define SPI2_MISO_BIT   GPIO_Pin_12 // GPIO_Pin_12 // GPIO_Pin_13 
    #define SPI2_MISO_AF    GPIO_AF_4   // GPIO_AF_4   // GPIO_AF_4   

    #define SPI2_MOSI_PORT  GPIOB      
    #define SPI2_MOSI_BIT   GPIO_Pin_13
    #define SPI2_MOSI_AF    GPIO_AF_4  

    #if defined(__MT304) || defined(__MZ306) || defined(__MT307) || defined(__MZ308) || defined(__MZ310)
    #define SPI2_NSS_PORT   GPIOB       // GPIOB      
    #define SPI2_NSS_BIT    GPIO_Pin_14 // GPIO_Pin_9
    #define SPI2_NSS_AF     GPIO_AF_4   // GPIO_AF_5  
    #endif

    #if defined(__MZ309)
    #define SPI2_NSS_PORT   GPIOB       // GPIOB       // GPIOB       // GPIOB     
    #define SPI2_NSS_BIT    GPIO_Pin_15 // GPIO_Pin_13 // GPIO_Pin_14 // GPIO_Pin_9
    #define SPI2_NSS_AF     GPIO_AF_1   // GPIO_AF_3   // GPIO_AF_4   // GPIO_AF_5 
    #endif
#endif
#define SPI2_MASTER_SCK_CONFIG()    {GPIO_Mode_AF_PP_50MHz_Init(SPI2_SCK_PORT,  SPI2_SCK_BIT,  NO_REMAP, SPI2_SCK_AF); }
#define SPI2_MASTER_MISO_CONFIG()   {GPIO_Mode_IPU_Init        (SPI2_MISO_PORT, SPI2_MISO_BIT, NO_REMAP, SPI2_MISO_AF);}
#define SPI2_MASTER_MOSI_CONFIG()   {GPIO_Mode_AF_PP_50MHz_Init(SPI2_MOSI_PORT, SPI2_MOSI_BIT, NO_REMAP, SPI2_MOSI_AF);}
#define SPI2_MASTER_NSS_CONFIG()    {exGPIO_PinAFConfig        (SPI2_NSS_PORT,  SPI2_NSS_BIT,  NO_REMAP, SPI2_NSS_AF); }
#define SPI2_MASTER_NSS_SW_CTL(x)   {if(x) GPIO_Mode_AF_PP_50MHz_Init(SPI2_NSS_PORT, SPI2_NSS_BIT,NO_REMAP, SPI2_NSS_AF);\
                                      else {\
                                          GPIO_SetBits(SPI2_NSS_PORT, SPI2_NSS_BIT);\
                                          GPIO_AF_Init(SPI2_NSS_PORT, SPI2_NSS_BIT, GPIO_Mode_Out_PP, GPIO_Speed_50MHz, NO_REMAP, SPI2_NSS_AF);\
                                      }}

#define SPI2_SLAVER_SCK_CONFIG()    {GPIO_Mode_FLOATING_Init   (SPI2_SCK_PORT,  SPI2_SCK_BIT,  NO_REMAP, SPI2_SCK_AF); }
#define SPI2_SLAVER_MISO_CONFIG()   {GPIO_Mode_AF_PP_50MHz_Init(SPI2_MISO_PORT, SPI2_MISO_BIT, NO_REMAP, SPI2_MISO_AF);}
#define SPI2_SLAVER_MOSI_CONFIG()   {GPIO_Mode_IPU_Init        (SPI2_MOSI_PORT, SPI2_MOSI_BIT, NO_REMAP, SPI2_MOSI_AF);}
#define SPI2_SLAVER_NSS_CONFIG()    {GPIO_Mode_IPU_Init        (SPI2_NSS_PORT,  SPI2_NSS_BIT,  NO_REMAP, SPI2_NSS_AF); }

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup SPI_Exported_Variables
/// @{
#ifdef _BSP_SPI_C_
#define GLOBAL


#else
#define GLOBAL extern
#endif

GLOBAL bool nssStatus;

#undef GLOBAL

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup SPI_Exported_Functions
/// @{

void BSP_SPI_NSS_Configure(SPI_TypeDef* SPIx, FunctionalState newState);
void BSP_SPI_GPIO_Configure(SPI_TypeDef* SPIx, bool master, bool nss);

/// @}


/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif /*__BSP_SPI_H */
////////////////////////////////////////////////////////////////////////////////
