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
#include "uart.h"

#include <math.h>

//float a = 1.5;
float warebuf[8] =  {0x05,0x10,0x15,0x20,0x25,0x30,0x35,0x40};

static u16 fac_us=0; //us��ʱ������
static u16 fac_ms=0; //ms��ʱ������

////////////////////////////////////////
//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ�� ��72
////////////////////////////////////////
void delay_init(u8 SYSCLK)
{
    SysTick->CTRL&=0xfffffffb;//bit2���,ѡ���ⲿʱ�� HCLK/8
    fac_us=SYSCLK/8;
    fac_ms=(u16)fac_us*1000;
}

////////////////////////////////////////
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864
////////////////////////////////////////
void delay_ms(u16 nms)
{
    u32 temp;
    SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
    SysTick->VAL =0x00; //��ռ�����
    SysTick->CTRL=0x01 ; //��ʼ����
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��
    SysTick->CTRL=0x00; //�رռ�����
    SysTick->VAL =0X00; //��ռ�����
}

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


///����һ���ֽڵ�����
void usart1_send_char(uint8_t ch)
{
    while (UART_GetFlagStatus(UART1, UART_IT_TXIEN) == RESET);//ѭ������,ֱ���������
//    UART_ClearITPendingBit(UART1, UART_IT_TXIEN);
    UART_SendData(UART1, (uint8_t)ch);
}

///����ָ�����ȵ�����
void usart1_putbuff (uint8_t *buff, uint32_t len)
{
    while(len--)
    {
        usart1_send_char(*buff);
        buff++;
    }
}

///����ͨ��Э������λ����������
void vcan_sendware(uint8_t *wareaddr, uint32_t waresize)
{
//    #define CMD_WARE     3   //3��������ʾ����,1����ͷ��2CCD
  
//    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE}; 
//    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};  
    uint8_t cmdf[2] = {0x03, 0xfc};    //���ڵ��� ʹ�õ�ǰ����
    uint8_t cmdr[2] = {0xfc, 0x03};    //���ڵ��� ʹ�õĺ�����
    
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
 //   int i = 0;
    while(1)
    {
//        a = 10 * a;
//        warebuf[0] = a;
        vcan_sendware((uint8_t *)warebuf,sizeof(warebuf));
        for(int i = 0; i < 100000; i++){}
    }
}
