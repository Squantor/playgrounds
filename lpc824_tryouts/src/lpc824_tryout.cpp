/*
The MIT License (MIT)

Copyright (c) 2018 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/*
Main program entry/file.
*/

#include "chip.h"
#include <cr_section_macros.h>
#include <boardinit.h>
#include <sqassert.h>

#define TICKRATE_HZ (2)	/* 10 ticks per second */

extern "C"
{
	void SysTick_Handler(void)
	{
	}
}

/* I2CM transfer record */
static I2CM_XFER_T  i2cmXferRec;

/* Function to setup and execute I2C transfer request */
static void SetupXferRecAndExecute(uint8_t devAddr,
								   uint8_t *txBuffPtr,
								   uint16_t txSize,
								   uint8_t *rxBuffPtr,
								   uint16_t rxSize)
{
	/* Setup I2C transfer record */
	i2cmXferRec.slaveAddr = devAddr;
	i2cmXferRec.status = 0;
	i2cmXferRec.txSz = txSize;
	i2cmXferRec.rxSz = rxSize;
	i2cmXferRec.txBuff = txBuffPtr;
	i2cmXferRec.rxBuff = rxBuffPtr;

	Chip_I2CM_XferBlocking(LPC_I2C, &i2cmXferRec);
}

static uint8_t txData[1];
static uint8_t rxData[1];
/* Function sends update to the I/O expander */
static void sendI2CMaster(uint16_t i2c_addr, uint8_t ledStateOut)
{
	txData[0] = ledStateOut;
	SetupXferRecAndExecute(i2c_addr, txData, sizeof(txData), rxData, 0);
}

int main(void)
{
	char string[] = "hi!\n";
	uint8_t leds = 0;

	boardInit();

	/* Disable the interrupt for the I2C */
	NVIC_DisableIRQ(I2C_IRQn);

	/* Enable SysTick Timer */
	sqassert(SysTick_Config(SystemCoreClock / TICKRATE_HZ) == 0);


	/* Loop forever */
	while (1)
	{

		Chip_UART_SendBlocking(LPC_USART0, &string, sizeof(string));
		sendI2CMaster(0x20, ( ~(leds++) ) | 0xF0);
		__WFI();
	}

    return 0 ;
}
