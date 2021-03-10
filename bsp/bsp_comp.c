////////////////////////////////////////////////////////////////////////////////
/// @file     BSP_COMP.C
/// @author   PX Liu
/// @version  v2.0.0
/// @date     2019-03-13
/// @brief    THIS FILE PROVIDES ALL THE COMP BSP LAYER FUNCTIONS.
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
#define _BSP_COMP_C_

// Files includes  -------------------------------------------------------------

#include "HAL_rcc.h"
#include "HAL_gpio.h"
#include "HAL_comp.h"

#include "bsp.h"
#include "bsp_comp.h"


////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Board_Support_Package
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup COMP_BSP
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup COMP_Exported_Functions
/// @{

#if defined(__MZ306) || defined(__MT307) || defined(__MZ308) || defined(__MZ309) || defined(__MZ310)
////////////////////////////////////////////////////////////////////////////////
/// @brief  Assign the value to inm, inp, out.
/// @param  COMPx: the selected comparator.
/// @param  NonInvert: non invert input selection
/// @param  Invert: invert input selection
/// @param  Output: output selection
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BSP_COMP_Configure(u32 COMPx, u32 NonInvert, u32 Invert, u32 Output)
{
	u8 inp = 0, inm = 0, out = 0;	   //INP:NonInvert, INM:Invert, OUT:Output

#if defined(__MZ306)	
	switch(Invert){
		case emCOMP_InvertingInput_1_4VREFINT:	inm = 0;	break;
		case emCOMP_InvertingInput_1_2VREFINT:	inm = 1;	break;
		case emCOMP_InvertingInput_3_4VREFINT:	inm = 2;	break;
		case emCOMP_InvertingInput_VREFINT:		inm = 3;	break;
		case emCOMP_InvertingInput_DAC1:		inm = 4;	break;
		case emCOMP_InvertingInput_DAC2:		inm = 5;	break;
		case emCOMP_InvertingInput_IO1:			inm = 6;	break;
		case emCOMP_InvertingInput_IO2:			inm = 7;	break;
		default:								inm = 0;	break;
	}
	switch(NonInvert){
		case emCOMP_NonInvertingInput_IO1:		inp = 0;	break;
		case emCOMP_NonInvertingInput_IO2:		inp = 1;	break;
		case emCOMP_NonInvertingInput_IO3:		inp = 2;	break;
		case emCOMP_NonInvertingInput_IO4:		inp = 3;	break;
    	case emCOMP_NonInvertingInput_IO5: 		inp = 4;	break;
    	case emCOMP_NonInvertingInput_IO6:		inp = 5;	break;
    	case emCOMP_NonInvertingInput_IO7: 		inp = 6;	break;
    	case emCOMP_NonInvertingInput_IO8: 		inp = 7;	break;
		default:								inp = 0;	break;
	}
#endif

#if defined(__MZ308) || defined(__MZ309) || defined(__MZ310)
#if defined(__MZ309)   
	switch(NonInvert){
		case emCOMP_NonInvertingInput_IO1:		inp = 0;	break;
		case emCOMP_NonInvertingInput_IO2:		inp = 1;	break;
		case emCOMP_NonInvertingInput_IO3:		inp = 2;	break;
		case emCOMP_NonInvertingInput_IO4:		inp = 3;	break;
		default:                                inp = 0;    break;
	}
#endif
#if defined(__MZ308) || defined(__MZ310)  
	switch(NonInvert){
		case emCOMP_NonInvertingInput_IO1:		inp = 0;	break;
		case emCOMP_NonInvertingInput_IO2:		inp = 3;	break;
		case emCOMP_NonInvertingInput_IO3:		inp = 2;	break;
		case emCOMP_NonInvertingInput_IO4:		inp = 1;	break;
		default:								inp = 0;	break;
	}
#endif
	switch(Invert){
		case emCOMP_InvertingInput_IO0:			inm = 0;	break;
		case emCOMP_InvertingInput_IO1:			inm = 1;	break;
		case emCOMP_InvertingInput_IO2:			inm = 2;	break;
		case emCOMP_InvertingInput_CRV:			inm = 3;	break;
		default:								inm = 0;	break;
	}
#endif

	switch(Output){
		case emCOMP_Output_None:				out = 0;	break;
		case emCOMP_Output_TIM1BKIN:			out = 1;	break;
		case emCOMP_Output_TIM1OCREFCLR:		out = 2;	break;
		case emCOMP_Output_TIM1IC1: 			out = 3;	break;
		case emCOMP_Output_TIM2IC4: 			out = 4;	break;
		case emCOMP_Output_TIM2OCREFCLR: 		out = 5;	break;
		case emCOMP_Output_TIM3IC1: 			out = 6;	break;
		case emCOMP_Output_TIM3OCREFCLR: 		out = 7;	break;
		default:								out = 0;	break;
	}

	BSP_COMP_GPIO_Configure(COMPx, inp, inm, out);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initialize the  channel of comparator.
/// @param  COMPx: the selected comparator.
//  @param  inp: non invert input selection

//  @param  inm: invert input selection
//  @param  out: output selection
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BSP_COMP_GPIO_Configure(u32 COMPx, u8 inp, u8 inm, u8 out)
{
#if defined(__MZ306) || defined(__MZ309) || defined(__MZ310)
	GPIOA_ClockEnable();
#endif
#if defined(__MZ308)
	GPIOA_ClockEnable(); GPIOB_ClockEnable(); GPIOD_ClockEnable();
#endif

#if defined(__REGISTER)	 /* ----------- Register Access ------------- */
    switch((u32)COMPx) {
    case COMP1:
#if defined(__MZ306)
/*  __MZ306 -------------------------------------------------------------
		compare 1:
			OUT:	PA0,  PA6,  PA11
			INP:	PA 0 : 7
			INM:	PA4, PA5, PA0, PA6
		compare 2:
			OUT:	PA2,  PA7,  PA12
			INP:	PA 0 : 7
			INM:	PA4, PA5, PA2, PA6
-----------------------------------------------------------------------*/
								GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << (inp * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << (inp * 4)) | (0x07 << (inp * 4));

		if 		(inm == 4) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((4  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((4  % 8) * 4)) | (0x07 << ((4  % 8) * 4));}
		else if (inm == 5) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((5  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((5  % 8) * 4)) | (0x07 << ((5  % 8) * 4));}
		else if (inm == 6) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((0  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((0  % 8) * 4)) | (0x07 << ((0  % 8) * 4));}
		else if (inm == 7) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((6  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((6  % 8) * 4)) | (0x07 << ((60  % 8) * 4));}


		if 		(out == 1) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((0  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((0  % 8) * 4)) | (0x07 << ((0  % 8) * 4));}
		else if (out == 2) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((6  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((6  % 8) * 4)) | (0x07 << ((6  % 8) * 4));}
		else if (out == 3) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((11 % 8) * 4));
								GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((11 % 8) * 4)) | (0x07 << ((11 % 8) * 4));}
#endif
#if defined(__MZ308)
/*  __MZ308 -------------------------------------------------------------
		compare 1:
			OUT:	PA14,  PD4
			INP:  	PB8
			INM:  	PB9

		compare 2:
			OUT:	PA13, PD0, PD5
			INP:  	PD7
			INM:  	PC13

		compare 3:
			OUT:	PD1, PD6
			INP:  	PC14
			INM:  	PC15

		compare 4:
			OUT: 	PA0, PA6, PA11
			INP:	PD3, PA6, PB2, PB10
			INM:	PB12, PA8, PD2

		compare 5:
			OUT:	PA2, PA7, PA12, PC10
			INP:	PA11, PA6, PB2, PB10
			INM:	PB12, PA8, PA12

-----------------------------------------------------------------------*/
							GPIOB->CRH  = GPIOB->CRH  & ~(0x0F << ((8  % 8) * 4));
							GPIOB->AFRH = GPIOB->AFRH & ~(0x0F << ((8  % 8) * 4)) | (0x07 << ((8  % 8) * 4));
							GPIOB->CRH  = GPIOB->CRH  & ~(0x0F << ((9  % 8) * 4));
							GPIOB->AFRH = GPIOB->AFRH & ~(0x0F << ((9  % 8) * 4)) | (0x07 << ((9  % 8) * 4));

		if (out == 1) {		GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((14 % 8) * 4));
							GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((14 % 8) * 4)) | (0x07 << ((14 % 8) * 4));}
		if (out == 2) { 	GPIOD->CRL  = GPIOD->CRL  & ~(0x0F << ((4  % 8) * 4));
							GPIOD->AFRL = GPIOD->AFRL & ~(0x0F << ((4  % 8) * 4)) | (0x07 << ((4  % 8) * 4));}
#endif
#if defined(__MZ309)
/*  __MZ309 -------------------------------------------------------------
		compare 1:
			OUT:	PA0,  PA6,  PA11
			INP:	PA 1 : 4
            INM:	PA 5 : 7
-----------------------------------------------------------------------*/
		GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((++inp) * 4));
		GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((++inp) * 4)) | (0x07 << ((++inp) * 4));

		GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((inm + 5) * 4));
		GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((inm + 5) * 4)) | (0x07 << ((inm + 5) * 4));


		if 		(out == 1) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((0  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((0  % 8) * 4)) | (0x07 << ((0  % 8) * 4));}
		else if (out == 2) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((6  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((6  % 8) * 4)) | (0x07 << ((6  % 8) * 4));}
		else if (out == 3) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((11 % 8) * 4));
								GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((11 % 8) * 4)) | (0x07 << ((11 % 8) * 4));}
#endif
#if defined(__MZ310)
/*  __MZ310 -------------------------------------------------------------
		compare 1:
			OUT:	PA0,  PA6,  PA11
			INP:	PA0,  PA1,  PA2,  PA3
            INM:	PA4,  PA5,  PA0

		compare 2:
			OUT:	PA2,  PA7,  PA12, PA10
			INP:	PA0,  PA1,  PA2,  PA3
            INM:	PA4,  PA5,  PA2
-----------------------------------------------------------------------*/
		if 		(inp == 1) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((0  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((0  % 8) * 4)) | (0x07 << ((0  % 8) * 4));}
		else if (inp == 2) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((1  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((1  % 8) * 4)) | (0x07 << ((1  % 8) * 4));}
		else if (inp == 3) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((2  % 8) * 4));
								GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((2  % 8) * 4)) | (0x07 << ((2  % 8) * 4));}
		else if (inp == 4) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((3  % 8) * 4));
								GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((3  % 8) * 4)) | (0x07 << ((3  % 8) * 4));}

		if 		(inm == 1) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((4  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((4  % 8) * 4)) | (0x07 << ((4  % 8) * 4));}
		else if (inm == 2) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((5  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((5  % 8) * 4)) | (0x07 << ((5  % 8) * 4));}
		else if (inm == 3) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((0  % 8) * 4));
								GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((0  % 8) * 4)) | (0x07 << ((0  % 8) * 4));}

		if 		(out == 1) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((0  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((0  % 8) * 4)) | (0x07 << ((0  % 8) * 4));}
		else if (out == 2) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((6  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((6  % 8) * 4)) | (0x07 << ((6  % 8) * 4));}
		else if (out == 3) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((11 % 8) * 4));
								GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((11 % 8) * 4)) | (0x07 << ((11 % 8) * 4));}
#endif
        break;

#if defined(__MZ306)
    case COMP2:
                                GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << (8  * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << (inp * 4)) | (0x07 << (inp * 4));

		if 		(inm == 4) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((4  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((4  % 8) * 4)) | (0x07 << ((4  % 8) * 4));}
		else if (inm == 5) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((5  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((5  % 8) * 4)) | (0x07 << ((5  % 8) * 4));}
		else if (inm == 6) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((2  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((2  % 8) * 4)) | (0x07 << ((2  % 8) * 4));}
		else if (inm == 7) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((6  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((6  % 8) * 4)) | (0x07 << ((6  % 8) * 4));}

		if 		(out == 0) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((2  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((2  % 8) * 4)) | (0x07 << ((2  % 8) * 4));}
		else if (out == 1) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((7  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((7  % 8) * 4)) | (0x07 << ((7  % 8) * 4));}
		else if (out == 2) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((12 % 8) * 4));
								GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((12 % 8) * 4)) | (0x07 << ((12 % 8) * 4));}

#endif
#if defined(__MZ308)
    case COMP2:
		 					GPIOD->CRL  = GPIOD->CRL  & ~(0x0F << ((7  % 8) * 4));
		 					GPIOD->AFRL = GPIOD->AFRL & ~(0x0F << ((7  % 8) * 4)) | (0x07 << ((7  % 8) * 4));
		 					GPIOC->CRH  = GPIOC->CRH  & ~(0x0F << ((13 % 8) * 4));
		 					GPIOC->AFRH = GPIOC->AFRH & ~(0x0F << ((13 % 8) * 4)) | (0x07 << ((13 % 8) * 4));
		 if (out == 1) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((13 % 8) * 4));
                            GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((13 % 8) * 4)) | (0x07 << ((13 % 8) * 4));}
		 if (out == 2) { 	GPIOD->CRL  = GPIOD->CRL  & ~(0x0F << ((0  % 8) * 4));
		 					GPIOD->AFRL = GPIOD->AFRL & ~(0x0F << ((0  % 8) * 4)) | (0x07 << ((0  % 8) * 4));}
		 if (out == 3) { 	GPIOD->CRL  = GPIOD->CRL  & ~(0x0F << ((5  % 8) * 4));
		 					GPIOD->AFRL = GPIOD->AFRL & ~(0x0F << ((5  % 8) * 4)) | (0x07 << ((5  % 8) * 4));}
#endif
#if defined(__MZ310)
    case COMP2:
		if 		(inp == 1) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((0  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((0  % 8) * 4)) | (0x07 << ((0  % 8) * 4));}
		else if (inp == 2) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((1  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((1  % 8) * 4)) | (0x07 << ((1  % 8) * 4));}
		else if (inp == 3) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((2  % 8) * 4));
								GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((2  % 8) * 4)) | (0x07 << ((2  % 8) * 4));}
		else if (inp == 4) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((3  % 8) * 4));
								GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((3  % 8) * 4)) | (0x07 << ((3  % 8) * 4));}

		if 		(inm == 1) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((4  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((4  % 8) * 4)) | (0x07 << ((4  % 8) * 4));}
		else if (inm == 2) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((5  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((5  % 8) * 4)) | (0x07 << ((5  % 8) * 4));}
		else if (inm == 3) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((2  % 8) * 4));
								GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((2  % 8) * 4)) | (0x07 << ((2  % 8) * 4));}

		if 		(out == 1) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((2  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((2  % 8) * 4)) | (0x07 << ((2  % 8) * 4));}
		else if (out == 2) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((7  % 8) * 4));
								GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((7  % 8) * 4)) | (0x07 << ((7  % 8) * 4));}
		else if (out == 3) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((12 % 8) * 4));
								GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((12 % 8) * 4)) | (0x07 << ((12 % 8) * 4));}
		else if (out == 4) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((10 % 8) * 4));
								GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((10 % 8) * 4)) | (0x07 << ((10 % 8) * 4));}
#endif
        break;

#if defined(__MZ308)
	case COMP3:				
							GPIOC->CRH  = GPIOC->CRH  & ~(0x0F << ((14 % 8) * 4));
		 					GPIOC->AFRH = GPIOC->AFRH & ~(0x0F << ((14 % 8) * 4)) | (0x07 << ((14 % 8) * 4));
		 					GPIOC->CRH  = GPIOC->CRH  & ~(0x0F << ((15 % 8) * 4));
		 					GPIOC->AFRH = GPIOC->AFRH & ~(0x0F << ((15 % 8) * 4)) | (0x07 << ((15 % 8) * 4));
		 if (out == 1) { 	GPIOD->CRL  = GPIOD->CRL  & ~(0x0F << ((1  % 8) * 4));
		 					GPIOD->AFRL = GPIOD->AFRL & ~(0x0F << ((1  % 8) * 4)) | (0x07 << ((1  % 8) * 4));}
		 if (out == 2) { 	GPIOD->CRL  = GPIOD->CRL  & ~(0x0F << ((6  % 8) * 4));
		 					GPIOD->AFRL = GPIOD->AFRL & ~(0x0F << ((6  % 8) * 4)) | (0x07 << ((6  % 8) * 4));}
        break;

    case COMP4:				
		if 		(inp == 0) {	GPIOD->CRL  = GPIOD->CRL  & ~(0x0F << ((3  % 8) * 4));
		 						GPIOD->AFRL = GPIOD->AFRL & ~(0x0F << ((3  % 8) * 4)) | (0x07 << ((3  % 8) * 4));}
		 else if (inp == 1) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((6  % 8) * 4));
		 						GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((6  % 8) * 4)) | (0x07 << ((6  % 8) * 4));}
		 else if (inp == 2) {	GPIOB->CRL  = GPIOB->CRL  & ~(0x0F << ((2  % 8) * 4));
		 						GPIOB->AFRL = GPIOB->AFRL & ~(0x0F << ((2  % 8) * 4)) | (0x07 << ((2  % 8) * 4));}
		 else if (inp == 3) {	GPIOB->CRH  = GPIOB->CRH  & ~(0x0F << ((10 % 8) * 4));
		 						GPIOB->AFRH = GPIOB->AFRH & ~(0x0F << ((10 % 8) * 4)) | (0x07 << ((10 % 8) * 4));}

		 else if (inm == 0) {	GPIOB->CRH  = GPIOB->CRH  & ~(0x0F << ((12 % 8) * 4));
		 						GPIOB->AFRH = GPIOB->AFRH & ~(0x0F << ((12 % 8) * 4)) | (0x07 << ((12 % 8) * 4));}
		 else if (inm == 1) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((8  % 8) * 4));
		 						GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((8  % 8) * 4)) | (0x07 << ((8  % 8) * 4));}
		 else if (inm == 2) {	GPIOD->CRL  = GPIOD->CRL  & ~(0x0F << ((2  % 8) * 4));
		 						GPIOD->AFRL = GPIOD->AFRL & ~(0x0F << ((2  % 8) * 4)) | (0x07 << ((2  % 8) * 4));}

		 if 	(out == 1) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((0  % 8) * 4));
		 						GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((0  % 8) * 4)) | (0x07 << ((0  % 8) * 4));}
		 else if (out == 2) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((6  % 8) * 4));
		 						GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((6  % 8) * 4)) | (0x07 << ((6  % 8) * 4));}
		 else if (out == 3) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((11 % 8) * 4));
		 						GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((11 % 8) * 4)) | (0x07 << ((11 % 8) * 4));}
        break;

    case COMP5:				
		 if (inp == 0) {		GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((11 % 8) * 4));
		 						GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((11 % 8) * 4)) | (0x07 << ((11 % 8) * 4));}
		 else if (inp == 1) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((6  % 8) * 4));
		 						GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((6  % 8) * 4)) | (0x07 << ((6  % 8) * 4));}
		 else if (inp == 2) {	GPIOB->CRL  = GPIOB->CRL  & ~(0x0F << ((2  % 8) * 4));
		 						GPIOB->AFRL = GPIOB->AFRL & ~(0x0F << ((2  % 8) * 4)) | (0x07 << ((2  % 8) * 4));}
		 else if (inp == 3) {	GPIOB->CRH  = GPIOB->CRH  & ~(0x0F << ((10 % 8) * 4));
		 						GPIOB->AFRH = GPIOB->AFRH & ~(0x0F << ((10 % 8) * 4)) | (0x07 << ((10 % 8) * 4));}

		 else if (inm == 0) {	GPIOB->CRH  = GPIOB->CRH  & ~(0x0F << ((12 % 8) * 4));
		 						GPIOB->AFRH = GPIOB->AFRH & ~(0x0F << ((12 % 8) * 4)) | (0x07 << ((12 % 8) * 4));}
		 else if (inm == 1) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((8  % 8) * 4));
		 						GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((8  % 8) * 4)) | (0x07 << ((8  % 8) * 4));}
		 else if (inm == 2) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((12 % 8) * 4));
		 						GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((12 % 8) * 4)) | (0x07 << ((12 % 8) * 4));}

		 if 		(out == 1) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((2  % 8) * 4));
		 						GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((2  % 8) * 4)) | (0x07 << ((2  % 8) * 4));}
		 else if (out == 2) {	GPIOA->CRL  = GPIOA->CRL  & ~(0x0F << ((7  % 8) * 4));
		 						GPIOA->AFRL = GPIOA->AFRL & ~(0x0F << ((7  % 8) * 4)) | (0x07 << ((7  % 8) * 4));}
		 else if (out == 3) {	GPIOA->CRH  = GPIOA->CRH  & ~(0x0F << ((12 % 8) * 4));
		 						GPIOA->AFRH = GPIOA->AFRH & ~(0x0F << ((12 % 8) * 4)) | (0x07 << ((12 % 8) * 4));}
		 else if (out == 4) {	GPIOC->CRH  = GPIOC->CRH  & ~(0x0F << ((10 % 8) * 4));
		 						GPIOC->AFRH = GPIOC->AFRH & ~(0x0F << ((10 % 8) * 4)) | (0x07 << ((10 % 8) * 4));}
        break;
#endif
    default: break;
    }


#else     	/* ----------- Hardware Abstraction Layer Access ------------- */
    switch(COMPx) {
    case COMP1:
#if defined(__MZ306)
        if (inm == 4)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_4, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        if (inm == 5)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_5, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        if (inm == 6)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_0, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        if (inm == 7)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_6, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);

        GPIO_Mode_IN_Init(GPIOA, 1 << inp , GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
		if 		(out == 1) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_0,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 2) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_6,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
        else if (out == 3) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_11, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
#endif
#if defined(__MZ308)
        GPIO_Mode_IN_Init(GPIOB, GPIO_Pin_8,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);  //inp
        GPIO_Mode_IN_Init(GPIOB, GPIO_Pin_9,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);  //inm        
		if 		(out == 1) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_14,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 2) 	GPIO_Mode_IN_Init(GPIOD, GPIO_Pin_4,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
#endif       
#if defined(__MZ309)
        if (inm == 0)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_5, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        if (inm == 1)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_6, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        if (inm == 2)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_7, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);

		GPIO_Mode_IN_Init(GPIOA, (u16)(1 << (inp + 1)) , GPIO_Mode_AIN, NO_REMAP, 0);
		if 		(out == 1) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_0,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 2) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_6,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 3) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_11, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
#endif       
#if defined(__MZ310)
        if(inp == 0)              GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_0,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inp == 1)         GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_1,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inp == 2)         GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_2,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inp == 3)         GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_3,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);

        if(inm == 0)        GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_4,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inm == 1)   GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_5,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inm == 2)   GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_0,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        
		if 		(out == 1)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_0,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 2) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_6,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 3) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_11, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
#endif
		break;

#if defined(__MZ306)
    case COMP2:
        if (inm == 4)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_4, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        if (inm == 5)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_5, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        if (inm == 6)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        if (inm == 7)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_6, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);

        GPIO_Mode_IN_Init(GPIOA, 1 << inp , GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
		if 		(out == 1) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_2,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 2) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_7,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
        else if (out == 3) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_12, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
        break;
#endif
#if defined(__MZ310)
    case COMP2:
        if(inp == 0)              GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_0,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inp == 1)         GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_1,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inp == 2)         GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_2,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inp == 3)         GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_3,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);

        if(inm == 0)        GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_4,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inm == 1)   GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_5,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inm == 2)   GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_2,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        
		if 		(out == 1)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_2,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 2) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_7,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 3) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_12, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
        else if (out == 4) 	GPIO_Mode_IN_Init(GPIOC, GPIO_Pin_10, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
        break;
#endif
#if defined(__MZ308)
    case COMP2:
        GPIO_Mode_IN_Init(GPIOD, GPIO_Pin_7,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);  //inp
        GPIO_Mode_IN_Init(GPIOC, GPIO_Pin_13, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);  //inm 
		if 		(out == 1) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_13,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 2) 	GPIO_Mode_IN_Init(GPIOD, GPIO_Pin_0,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 3)	GPIO_Mode_IN_Init(GPIOD, GPIO_Pin_5, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
        break;
#endif

#if defined(__MZ308)
    case COMP3:				
        GPIO_Mode_IN_Init(GPIOC, GPIO_Pin_14,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);  //inp
        GPIO_Mode_IN_Init(GPIOC, GPIO_Pin_15,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);  //inm 
		if 		(out == 1)	GPIO_Mode_IN_Init(GPIOD, GPIO_Pin_1,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 2) 	GPIO_Mode_IN_Init(GPIOD, GPIO_Pin_6,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
        break;

    case COMP4:				
        if(inp == 0)              GPIO_Mode_IN_Init(GPIOD, GPIO_Pin_3,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inp == 1)         GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_6,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inp == 2)         GPIO_Mode_IN_Init(GPIOB, GPIO_Pin_2,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inp == 3)         GPIO_Mode_IN_Init(GPIOB, GPIO_Pin_10, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);

        if(inm == 0)        GPIO_Mode_IN_Init(GPIOB, GPIO_Pin_12, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inm == 1)   GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_8,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inm == 2)   GPIO_Mode_IN_Init(GPIOD, GPIO_Pin_2,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        
		if 		(out == 1)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_0,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 2) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_6,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 3) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_11, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
        break;

    case COMP5:				
        if(inp == 0)              GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_11, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inp == 1)         GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_6,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inp == 2)         GPIO_Mode_IN_Init(GPIOB, GPIO_Pin_2,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inp == 3)         GPIO_Mode_IN_Init(GPIOB, GPIO_Pin_10, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        
        if(inm == 0)        GPIO_Mode_IN_Init(GPIOB, GPIO_Pin_12, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inm == 1)   GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_8,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);
        else if(inm == 2)   GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_12, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_0);

		if 		(out == 1)	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_2,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
		else if (out == 2) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_7,  GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
        else if (out == 3) 	GPIO_Mode_IN_Init(GPIOA, GPIO_Pin_12, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
        else if (out == 4) 	GPIO_Mode_IN_Init(GPIOC, GPIO_Pin_10, GPIO_Mode_AIN, NO_REMAP, GPIO_AF_7);
        break;
#endif

    default: break;
    }
/* -------------------------------------------------------------------------- */
#endif			 /* ----------------- End Access  ------------------- */
/* -------------------------------------------------------------------------- */
}

#endif

/// @}


/// @}

/// @}
