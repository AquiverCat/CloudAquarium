/******************************************************************************
*
*   Copyright (C) 2014 Texas Instruments Incorporated
*
*   All rights reserved. Property of Texas Instruments Incorporated.
*   Restricted rights to use, duplicate or disclose this code are
*   granted through contract.
*
*   The program may not be used without the written permission of
*   Texas Instruments Incorporated or against the terms and conditions
*   stipulated in the agreement under which this program has been supplied,
*   and under no circumstances can it be used with non-TI connectivity device.
*
******************************************************************************/

// This file was automatically generated by the CC31xx PinMux Utility
// Version: 1.0.2
//
//*****************************************************************************

#include "pinmux.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "pin.h"
#include "rom.h"
#include "rom_map.h"
#include "rom_patch.h"
#include "gpio.h"
#include "prcm.h"

//*****************************************************************************
void
PinMuxConfig(void)
{
    //
    // Enable Peripheral Clocks 
    //
    MAP_PRCMPeripheralClkEnable(PRCM_GPIOA1, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(PRCM_GPIOA2, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(PRCM_GPIOA3, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(PRCM_UARTA0, PRCM_RUN_MODE_CLK);


    //
    // Configure PIN_64 for GPIOOutput
    //
    MAP_PinTypeGPIO(PIN_64, PIN_MODE_0, false);
    MAP_GPIODirModeSet(GPIOA1_BASE, 0x2, GPIO_DIR_MODE_OUT);

    //
    // Configure PIN_01 for GPIOOutput
    //
    MAP_PinTypeGPIO(PIN_01, PIN_MODE_0, false);
    MAP_GPIODirModeSet(GPIOA1_BASE, 0x4, GPIO_DIR_MODE_OUT);

    //
    // Configure PIN_02 for GPIOOutput
    //
    MAP_PinTypeGPIO(PIN_02, PIN_MODE_0, false);
    MAP_GPIODirModeSet(GPIOA1_BASE, 0x8, GPIO_DIR_MODE_OUT);

    //
    // Configure PIN_03 for GPIOOutput*****
    //
    MAP_PinTypeGPIO(PIN_03, PIN_MODE_0, false);
    MAP_GPIODirModeSet(GPIOA1_BASE, 0x10, GPIO_DIR_MODE_OUT);

    //
    // Configure PIN_04 for GPIOInput
    //
    MAP_PinTypeGPIO(PIN_04, PIN_MODE_0, false);
    MAP_GPIODirModeSet(GPIOA1_BASE, 0x20, GPIO_DIR_MODE_IN);

    //
    // Configure PIN_06 for GPIOOutput*****
    //
    MAP_PinTypeGPIO(PIN_06, PIN_MODE_0, false);
    MAP_GPIODirModeSet(GPIOA1_BASE, 0x80, GPIO_DIR_MODE_IN);

    //
    // Configure PIN_07 for GPIOOutput*****
    //
    MAP_PinTypeGPIO(PIN_07, PIN_MODE_0, false);
    MAP_GPIODirModeSet(GPIOA2_BASE, 0x01, GPIO_DIR_MODE_OUT);

    //
    // Configure PIN_08 for GPIOOutput*****
    //
    MAP_PinTypeGPIO(PIN_08, PIN_MODE_0, false);
    MAP_GPIODirModeSet(GPIOA2_BASE, 0x02, GPIO_DIR_MODE_OUT);

    //
    // Configure PIN_15 for GPIOInput
    //
    MAP_PinTypeGPIO(PIN_15, PIN_MODE_0, false);
    MAP_GPIODirModeSet(GPIOA2_BASE, 0x40, GPIO_DIR_MODE_OUT);


    //
    // Configure PIN_63 for GPIOOutput*****
    //
    MAP_PinTypeGPIO(PIN_63, PIN_MODE_0, false);
    MAP_GPIODirModeSet(GPIOA1_BASE, 0x01, GPIO_DIR_MODE_OUT);

    //
    // Configure PIN_18 for GPIOOutput*****
    //
    MAP_PinTypeGPIO(PIN_18, PIN_MODE_0, false);
    MAP_GPIODirModeSet(GPIOA3_BASE, 0x10, GPIO_DIR_MODE_OUT);//**

    //
    // Configure PIN_55 for UART0 UART0_TX
    //
    MAP_PinTypeUART(PIN_55, PIN_MODE_3);

    //
    // Configure PIN_57 for UART0 UART0_RX
    //
    MAP_PinTypeUART(PIN_57, PIN_MODE_3);
}
