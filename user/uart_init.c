//#include <string.h>
//#include <stdio.h>
//
//#include "types.h"
//#include "system_mm32.h"
//#include "common.h"
//
//#include "bsp.h"
//#include "bsp_led.h"
//#include "bsp_uart.h"
//
//#include "HAL_uart.h"
//#include "HAL_dma.h"
//#include "uart.h"
//
/////发送一个字节的数据
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
//    #define CMD_WARE     3   //3代表虚拟示波器,1摄像头，2CCD
//  
//    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE}; 
//    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};  
//    
//    usart1_putbuff(cmdf,sizeof(cmdf));
//    usart1_putbuff(wareaddr,waresize);
//    usart1_putbuff(cmdr,sizeof(cmdr));
//}
//