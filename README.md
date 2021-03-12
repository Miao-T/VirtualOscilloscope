# Virtual Oscilloscope of MM32 Based on ShanWai Debugging Assistant
## <font color=#990000>Introduction</font>

The virtual oscilloscope on ShanWai Multifunctional Debugging Assistant could help us to observe the real-time change of data when we are debugging MM32 chip.

**Characteristics of ShanWai Virtual Oscilloscope:**

- Support eight channels and every channel could be hidden
- Selectable channel data type
- Scalable and removable interface

- Trace update data

**Communication protocol of of ShanWai Virtual Oscilloscope:**

- The format of communication protocol: \[CMD\]\[\~CMD\]\[…data…\]\[\~CMD\]\[CMD\]

- CMD = 0x03 when debugging assistant is used as virtual oscilloscope:

  \[0x03\]\[0xFC\]\[…data…\]\[0xFC\]\[0x03\]

- \[…data…\] will shown as waveform. The length of data is different according to the amount of wave channel and data type.

- The microcontroller would transmit data in this order:

  1. Frame head: 0x03 0xFC
  2. The data of waveform
  3. End of frame: 0xFC 0x03

For more details: [Instructions of ShanWai Debugging Assistant][instructions]

## <font color=#990000>Solution: Output Triangle Wave</font>

The following codes refer to [「顶点元」STM32使用虚拟示波器][oscilloscope]

1. **Configure UART**

   ```C
   void initUART1_IT(u32 baudrate);
   ```

2. **Transmit one byte data**

   ```C
   void usart1_send_char(uint8_t ch);
   ```

3. **Transmit an array data**

   The length of the array represents the amount of channel.

   ```C
   void usart1_putbuff (uint8_t *buff, uint32_t len);
   ```

4. **Transmit data to upper computer according to communication protocol**

   ```C
   void vcan_sendware(uint8_t *wareaddr, uint32_t waresize);
   ```

5. **Output triangle wave**

## <font color=#990000>Solution: Output ADC Wave</font>

1. **The code of UART configuration and data transmission is the same as above**

2. **Configure ADC**

   ```c
   void ADC_Configure_Init(ADC_TypeDef* ADCx);
   void Set_ADC_Clock(ADC_TypeDef* ADCx);
   void ADC_Function(ADC_TypeDef* ADCx);
   void ADC_RegularChannelConfigure(void);
   ```

3. **Output ADC wave**

   ```C
   warebuf[1] = (float)ADC_ConvertedValue*(3.3/4096);
   ```


## <font color=#990000>CSDN</font>

For more details, you could read [「Rose Island」山外多功能调试助手用作MM32虚拟示波器][rose island]

[instructions]: https://wenku.baidu.com/view/a1300c6e59fb770bf78a6529647d27284b733799.html
[oscilloscope]: https://blog.csdn.net/xiaoyuanwuhui/article/details/86350171

[rose island]:https://blog.csdn.net/weixin_42150654/article/details/114698352

