//#include "types.h"
//#include "mm32.h"
//#include "system_mm32.h"
//#include "common.h"
//
//#include "HAL_rcc.h"
//#include "HAL_gpio.h"
//#include "HAL_adc.h"
//#include "HAL_tim.h"
//#include "bsp_adc.h"
//#include "bsp.h"
//
//#include "bsp_uart.h"
//#include "HAL_uart.h"
//
//void Set_ADC_Clock(ADC_TypeDef* ADCx)
//{
//	if (ADCx == ADC1)	COMMON_EnableIpClock(emCLOCK_ADC1);
//#if defined(__MT304) || defined(__MZ308)
//    else				COMMON_EnableIpClock(emCLOCK_ADC2);
//#endif
//}
//
//void ADC_Configure_Init(ADC_TypeDef* ADCx)
//{
//	ADC_InitTypeDef ADC_InitStructure;
//    ADC_InitStructure.ADC_Resolution         = ADC_Resolution_12b;
//    ADC_InitStructure.ADC_PRESCARE           = ADC_PCLK2_PRESCARE_8;
//    ADC_InitStructure.ADC_Mode               = ADC_CR_CONTINUE;
//	ADC_InitStructure.ADC_ExternalTrigConv = 0;
//    ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
//	Set_ADC_Clock(ADCx);
//	ADC_Init(ADCx, &ADC_InitStructure); 
//}  
//
//void ADC_Function(ADC_TypeDef* ADCx)
//{
//	ADC_ExternalTrigConvCmd(ADCx, DISABLE);
//}
//
//void ADC_RegularChannelConfigure(void)
//{
//    u32 chs = 0 ;        
//    chs |= LEFT_SHIFT_BIT(0) | LEFT_SHIFT_BIT(1) | LEFT_SHIFT_BIT(2) | LEFT_SHIFT_BIT(3);
//    ADC1->CFGR &= ~ADC_CFGR_SAMCTL;
//#if defined(__MT304) || defined(__MZ306) || defined(__MT307) ||defined(__MZ308) || defined(__MZ309)  
//    ADC1->CFGR |=  ADC_Samctl_13_5;
//#else
//    ADC1->CFGR |=  ADC_Samctl_6_5;
//#endif    
//	ADC1->CHSR &= ~chs;
//	ADC1->CHSR |=  chs;
//    
//    exADC_TempSensorVrefintCmd(chs, ENABLE);  
//}
//
//void initUART1_IT(u32 baudrate)
//{
//    UART_InitTypeDef pUARTInit;
//
//    COMMON_EnableIpClock(emCLOCK_UART1);
//    COMMON_NVIC_Configure(UART1_IRQn, 1, 1);
//    
//    UART_StructInit(&pUARTInit);
//    pUARTInit.BaudRate      = baudrate;
//    pUARTInit.WordLength    = UART_WordLength_8b;
//    pUARTInit.StopBits      = UART_StopBits_1;
//    pUARTInit.Parity        = UART_Parity_No;
//    pUARTInit.Mode          = UART_Mode_Rx | UART_Mode_Tx;
//    pUARTInit.HWFlowControl = UART_HWFlowControl_None;
//    UART_Init(UART1, &pUARTInit);
//    
//    UART_ITConfig(UART1, UART_IT_RXIEN, ENABLE);
//    UART_ClearITPendingBit(UART1, UART_IT_RXIEN);
//    UART_Cmd(UART1, ENABLE);
//    
//    BSP_UART_GPIO_CONFIGURE(UART1);
//}
//
//void usart1_send_char(uint8_t ch)
//{
//    while (UART_GetFlagStatus(UART1, UART_IT_TXIEN) == RESET);//循环发送,直到发送完毕
//    UART_ClearITPendingBit(UART1, UART_IT_TXIEN);
//    UART_SendData(UART1, (uint8_t)ch);
//}
//
/////发送指定长度的数组
//void usart1_putbuff (uint8_t *buff, uint32_t len)
//{
//    while(len--)
//    {
//        usart1_send_char(*buff);
//        buff++;
//    }
//}
//
/////根据通信协议向上位机发送数据
//void vcan_sendware(uint8_t *wareaddr, uint32_t waresize)
//{
////    #define CMD_WARE     3   //3代表虚拟示波器,1摄像头，2CCD
//  
////    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE}; 
////    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};  
//    uint8_t cmdf[2] = {0x03, 0xfc};    //串口调试 使用的前命令
//    uint8_t cmdr[2] = {0xfc, 0x03};    //串口调试 使用的后命令
//    
//    usart1_putbuff(cmdf,sizeof(cmdf));
//    usart1_putbuff(wareaddr,waresize);
//    usart1_putbuff(cmdr,sizeof(cmdr));
//}
//
//void AppTaskTick()
//{
//    if (tickCnt++ >= 500) {
//        tickCnt  = 0;
//        tickFlag = true;
//	}
//}
//
//int main(void)
//{
//// Step 1:  Setting System Clock     ------------------>>>>>
//	/* ====  System Clock & SysTick & AppTaskTick Setting  ==== */
//	/* When the parameter is NULL, AppTaskTick function used */
//	MCUID = SetSystemClock(emSYSTICK_On, AppTaskTick);
//	/* When the parameter is NULL, AppTaskTick function not be used */
//    ADC_Configure_Init(ADC1);
//    ADC_Function(ADC1);
//    ADC_RegularChannelConfigure();
//    ADC_Cmd(ADC1, ENABLE);
//    BSP_ADC_GPIO_Configure(ADC1, 15);
//    
//    initUART1_IT(115200);
//    
//    float ADC_ConvertedValue; 
//    float ADC_ConvertedValueLocal;
//    float warebuf[8] =  {0x00,0x05,0x10,0x15,0x20,0x25,0x30,0x35};
//    
//	while (1) {
//        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//        while(!ADC_GetFlagStatus(ADC1, ADC_IT_EOC));
//        ADC_ConvertedValue = ADC_GetConversionValue(ADC1); //获取转换结果*ADC_ConvertedValue*	
//        warebuf[0] = (float)ADC_ConvertedValue;
//	    warebuf[1] = (float)ADC_ConvertedValue*(3.3/4096);   //计算出实际电压值*ADC_ConvertedValueLocal*
//        vcan_sendware((uint8_t *)warebuf,sizeof(warebuf));
//        for(int i = 0; i < 100000; i++){}
//	}
//}