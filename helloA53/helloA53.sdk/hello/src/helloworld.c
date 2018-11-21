/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xgpio.h"


/*
 * The following constant is used to determine which channel of the GPIO is
 * used for the LED if there are 2 channels supported.
 */
#define LED_CHANNEL 1


int main()
{
    init_platform();

    print("Hello World\n\r");

    XGpio Gpio; /* The Instance of the GPIO Driver */

    /* Initialize the GPIO driver */
    int Status = XGpio_Initialize(&Gpio, XPAR_GPIO_0_DEVICE_ID);
    if (Status != XST_SUCCESS) {
            xil_printf("Gpio Initialization Failed\r\n");
            return XST_FAILURE;
    }

	/* Set the direction for all signals as LED output */
	XGpio_SetDataDirection(&Gpio, LED_CHANNEL, 0);

	/*
	 * D12 is ON by default, D13 ~ D19 are OFF
	 *
	 * D19, D18, D17, D16, D15, D14, D13, D12
	 *
	 *  0    0    0    0    0    0    0    1
	 */
	int LED = 0b00000001;

	/*
	 * 0: left to right (D12 -> D19)
	 * 1: right to left (D19 -> D12)
	 */
	int direction = 0;

	/* Loop forever blinking the LED */
	while (1) {
	        /* Set the LED to High */
	        XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, LED);

	        /* Wait a small amount of time so the LED is visible */
	        usleep(20 * 1000);	/* delay 20ms */

	        /* Clear the LED bit */
	        XGpio_DiscreteClear(&Gpio, LED_CHANNEL, LED);

	        /* Wait a small amount of time so the LED is visible */
	        usleep(20 * 1000);	/* delay 20ms */

	        /* When D19 is ON, change direction */
	        if (LED == 0b1000000)
	                direction = 1;  /* 1: right to left (D19 -> D12) */
	        /* When D12 is ON, change direction */
	        if (LED == 0b0000001)
	                direction = 0;  /* 0: left to right (D12 -> D19) */

	        /* Change LED status according to direction */
	        if (direction == 0)
	                LED = LED << 1; /* shift left */
	        else
	                LED = LED >> 1; /* shift right */
	}

    cleanup_platform();
    return 0;
}
