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
/////����һ���ֽڵ�����
//void usart1_send_char(uint8_t ch)
//{
//    while (UART_GetFlagStatus(UART1, UART_IT_TXIEN) == RESET);//ѭ������,ֱ���������
//    UART_ClearITPendingBit(UART1, UART_IT_TXIEN);
//    UART_SendData(UART1, (uint8_t)ch);
//}
//
/////����ָ�����ȵ�����
//void usart1_putbuff (uint8_t *buff, uint32_t len)
//{
//    while(len--)
//    {
//        usart1_send_char(*buff);
//        buff++;
//    }
//}
//
/////����ͨ��Э������λ����������
//void vcan_sendware(uint8_t *wareaddr, uint32_t waresize)
//{
//    #define CMD_WARE     3   //3��������ʾ����,1����ͷ��2CCD
//  
//    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE}; 
//    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};  
//    
//    usart1_putbuff(cmdf,sizeof(cmdf));
//    usart1_putbuff(wareaddr,waresize);
//    usart1_putbuff(cmdr,sizeof(cmdr));
//}
//