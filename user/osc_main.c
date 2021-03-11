#include <string.h>
#include <stdio.h>

#include "types.h"
#include "system_mm32.h"
#include "common.h"

#include "bsp.h"
#include "bsp_led.h"
#include "bsp_uart.h"

#include "HAL_uart.h"
#include "HAL_dma.h"
//#include "uart.h"

#include <math.h>

float warebuf[8] =  {0x00,0x05,0x10,0x15,0x20,0x25,0x30,0x35};

void initUART1_IT(u32 baudrate)
{
    UART_InitTypeDef pUARTInit;

    COMMON_EnableIpClock(emCLOCK_UART1);
    COMMON_NVIC_Configure(UART1_IRQn, 1, 1);
    
    UART_StructInit(&pUARTInit);
    pUARTInit.BaudRate      = baudrate;
    pUARTInit.WordLength    = UART_WordLength_8b;
    pUARTInit.StopBits      = UART_StopBits_1;
    pUARTInit.Parity        = UART_Parity_No;
    pUARTInit.Mode          = UART_Mode_Rx | UART_Mode_Tx;
    pUARTInit.HWFlowControl = UART_HWFlowControl_None;
    UART_Init(UART1, &pUARTInit);
    
    UART_ITConfig(UART1, UART_IT_RXIEN, ENABLE);
    UART_ClearITPendingBit(UART1, UART_IT_RXIEN);
    UART_Cmd(UART1, ENABLE);
    
    BSP_UART_GPIO_CONFIGURE(UART1);
}


///发送一个字节的数据
void usart1_send_char(uint8_t ch)
{
    while (UART_GetFlagStatus(UART1, UART_IT_TXIEN) == RESET);//循环发送,直到发送完毕
    UART_ClearITPendingBit(UART1, UART_IT_TXIEN);
    UART_SendData(UART1, (uint8_t)ch);
}

///发送指定长度的数组
void usart1_putbuff (uint8_t *buff, uint32_t len)
{
    while(len--)
    {
        usart1_send_char(*buff);
        buff++;
    }
}

///根据通信协议向上位机发送数据
void vcan_sendware(uint8_t *wareaddr, uint32_t waresize)
{
//    #define CMD_WARE     3   //3代表虚拟示波器,1摄像头，2CCD
  
//    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE}; 
//    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};  
    uint8_t cmdf[2] = {0x03, 0xfc};    //串口调试 使用的前命令
    uint8_t cmdr[2] = {0xfc, 0x03};    //串口调试 使用的后命令
    
    usart1_putbuff(cmdf,sizeof(cmdf));
    usart1_putbuff(wareaddr,waresize);
    usart1_putbuff(cmdr,sizeof(cmdr));
}

void AppTaskTick()
{
    if (tickCnt++ >= 500) {
        tickCnt  = 0;
        tickFlag = true;
	}
}

void main(void)
{   
    MCUID = SetSystemClock(emSYSTICK_On, AppTaskTick);
    initUART1_IT(115200);
    while(1)
    {
        warebuf[0] += 5;
        vcan_sendware((uint8_t *)warebuf,sizeof(warebuf));
        for(int i = 0; i < 100000; i++){}
        if(warebuf[0] >= 0x50){
            warebuf[0] = 0x00;
        }
    }
}
