// Standard includes
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// Driverlib includes
#include "utils.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "hw_types.h"
#include "hw_adc.h"
#include "hw_ints.h"
#include "hw_gprcm.h"
#include "rom.h"
#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"
#include "uart.h"
#include "pinmux.h"
#include "pin.h"
#include "gpio.h"
#include "adc.h"

#include "adc_userinput.h"
#include "uart_if.h"
#include "ph.h"

#define NO_OF_SAMPLES 		1
unsigned long pulAdcSamples[4096];

unsigned long  uiAdcInputPin = PIN_60;
unsigned int  uiChannel;
unsigned int  uiIndex=0;
unsigned long ulSample;

//*****************************************************************************
//                      GLOBAL VARIABLES
//*****************************************************************************
#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif

float ReadPh(void)
{
	uiIndex=0;
	float PhDate =0.0;

#ifdef CC3200_ES_1_2_1
        //
        // Enable ADC clocks.###IMPORTANT###Need to be removed for PG 1.32
        //
        HWREG(GPRCM_BASE + GPRCM_O_ADC_CLK_CONFIG) = 0x00000043;
        HWREG(ADC_BASE + ADC_O_ADC_CTRL) = 0x00000004;
        HWREG(ADC_BASE + ADC_O_ADC_SPARE0) = 0x00000100;
        HWREG(ADC_BASE + ADC_O_ADC_SPARE1) = 0x0355AA00;
#endif

	//
    // Pinmux for the selected ADC input pin选择ADC输入
    //
    MAP_PinTypeADC(uiAdcInputPin,PIN_MODE_255);

    //
    // Convert pin number to channel number
    //
    switch(uiAdcInputPin)
    {
    	case PIN_58:
    		uiChannel = ADC_CH_1;
        	break;
        case PIN_59:
        	uiChannel = ADC_CH_2;
        	break;
        case PIN_60:
        	uiChannel = ADC_CH_3;
        	break;
        default:
        	break;
    }

    //
    // Configure ADC timer which is used to timestamp the ADC data samples配置ADC定时器
    //
    MAP_ADCTimerConfig(ADC_BASE,2^17);

    //
    // Enable ADC timer which is used to timestamp the ADC data samples启用ADC定时器
    //
    MAP_ADCTimerEnable(ADC_BASE);

    //
    // Enable ADC module启用ADC模块
    //
    MAP_ADCEnable(ADC_BASE);

    //
    // Enable ADC channel使ADC通道
    //

    MAP_ADCChannelEnable(ADC_BASE, uiChannel);

    while(uiIndex < NO_OF_SAMPLES + 4)
    {
    	if(MAP_ADCFIFOLvlGet(ADC_BASE, uiChannel))			//读取ADC阈值
        {
        	ulSample = MAP_ADCFIFORead(ADC_BASE, uiChannel);		//读取ADC FIFO数据
        	pulAdcSamples[uiIndex++] = ulSample;
        }


    }

    MAP_ADCChannelDisable(ADC_BASE, uiChannel);		//禁止ADC通道

    uiIndex = 0;

    //UART_PRINT("\n\rTotal no of 32 bit ADC data printed :4096 \n\r");
    //UART_PRINT("\n\rADC data format:\n\r");
    //UART_PRINT("\n\rbits[13:2] : ADC sample\n\r");
    //UART_PRINT("\n\rbits[31:14]: Time stamp of ADC sample \n\r");

    //
    // Print out ADC samples
    //
    PhDate = 20.9025-17.875*((((float)((pulAdcSamples[4+uiIndex] >> 2 ) & 0x0FFF))*1.4)/4096);
    //while(uiIndex < NO_OF_SAMPLES)
    //{
    //    UART_PRINT("\n\rpH Voltage is %f\n\r",20.9025-17.875*((((float)((pulAdcSamples[4+uiIndex] >> 2 ) & 0x0FFF))*1.4)/4096));
    //   uiIndex++;
    //}

    return PhDate;
        //UART_PRINT("\n\rVoltage is %f\n\r",((pulAdcSamples[4] >> 2 ) & 0x0FFF)*1.4/4096);
        //UART_PRINT("\n\r");

}
