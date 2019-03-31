//*****************************************************************************
// adc_userinput.c 
//
// Functions for ADC USER Input
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
// 
// 
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//    Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the   
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup adc_userinput
//! @{
//
//*****************************************************************************

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hw_memmap.h"
#include "hw_types.h"
#include "rom.h"
#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"
#include "uart_if.h"
#include "uart.h"
#include "pinmux.h"
#include "pin.h"
#include "adc_userinput.h"

#define UART_PRINT Report

//*****************************************************************************
//
//! ADC Parser Function
//!
//! This function
//!        1. Parses and gets the Configuration解析并获得配置
//! \param ucCMD - Command Buffer命令缓冲区
//! \out puiAdcInputPin - ADC input pin
//!
//! \return Success or Failure
//
//*****************************************************************************
bool
ADCParser( char *ucCMD,unsigned long *puiAdcInputPin,unsigned long *puiAdcInputPin1)
{
    char *ucInpString;
    ucInpString = strtok(ucCMD, " ");

    //
    // Check Whether Command is valid检查命令是否有效
    //
    if(ucInpString != NULL)
    {
    	if(!strcmp(ucInpString,"ph"))				//ph检测
    	{
    		*puiAdcInputPin = PIN_60;
    	}
    	else if(!strcmp(ucInpString,"temp"))		//温度检测
    	{
    		*puiAdcInputPin = PIN_03;
    	}
        else if(!strcmp(ucInpString,"heating"))		//加热
        {
            *puiAdcInputPin = PIN_01;
        }
        else if(!strcmp(ucInpString,"filtration"))		//水过滤
        {
            *puiAdcInputPin = PIN_07;
        }
        else if(!strcmp(ucInpString,"oxygen"))			//加氧泵
        {
            *puiAdcInputPin = PIN_08;
        }
        else if(!strcmp(ucInpString,"change"))				//换水
        {
            *puiAdcInputPin = PIN_15;
        }
        else if(!strcmp(ucInpString,"cool"))				//降温
        {
            *puiAdcInputPin = PIN_02;
        }
        else if(!strcmp(ucInpString,"feed"))				//降温
        {
            *puiAdcInputPin = PIN_63;
        }
        else if(!strcmp(ucInpString,"18"))				//p18
        {
            *puiAdcInputPin = PIN_18;
        }

        ucInpString=strtok(NULL," ");
        if(!strcmp(ucInpString,"on"))
        {
            *puiAdcInputPin1 = 0;
        }
        else if(!strcmp(ucInpString,"off"))
        {
            *puiAdcInputPin1 = 1;
        }
        return true;
   }
   else
   {
       UART_PRINT("\n\rInvalid Command \n\r");
       return false;
   }
}

//*****************************************************************************
//
//! Application startup display on UART
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void
UsageDisplay()
{
    //Report("*********************************************\n\r");
    UART_PRINT("Command Usage \n\r");
    UART_PRINT("-------------- \n\r");
    UART_PRINT("Parameters \n\r");
    UART_PRINT("heating on/off \n\r");
    UART_PRINT("filtration on/off \n\r");
    UART_PRINT("oxygen on/off \n\r");
    UART_PRINT("change on/off \n\r");
    UART_PRINT("cool on/off \n\r");
    UART_PRINT("-------------- \n\r");
    UART_PRINT("-----------------------------------------------------------"
                "-------------- \n\r\n\r");
    UART_PRINT("\n\r");

}

//*****************************************************************************
//
//! ReadFrom User Function
//!
//! This function
//!        1. Gets Input from User
//! \out puiAdcInputPin - ADC input pin
//!
//! \return Success or Failure
//
//*****************************************************************************
bool 
ReadFromUser(unsigned long * puiAdcInputPin,unsigned long * puiAdcInputPin1)
{
    char ucCmdBuffer[64];
    UsageDisplay();
    UART_PRINT("cmd# ");
    GetCmd(ucCmdBuffer,64);
    if(ADCParser(ucCmdBuffer,puiAdcInputPin,puiAdcInputPin1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
