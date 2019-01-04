/*
The MIT License (MIT)

Copyright (c) 2019 Bart Bilos

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

#include <chip.h>
#include <DeviceSystick_cm0.hpp>

namespace system_tick::detail
{
	void Configure(Whatever& peripheral, uint32_t ticks)
	{
		assert((periperal.CTRL & (1 << 0)) == 0 && "Already configured");

		peripheral.LOAD  = ticks - 1;                                  /* set reload register */
		NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Systick Interrupt */
		peripheral.VAL   = 0;                                          /* Load the SysTick Counter Value */
		peripheral.CTRL  = 0x01 << 2 |
					   0x01 << 1   |
					   0x01 << 0;                    /* Enable SysTick IRQ and SysTick Timer */
	}
}
