/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
#include <stdio.h>
#include <stdint.h>

void delay (void);


int main(void)
{
	uint32_t volatile *const pClkctrlReg = (uint32_t*)(0x40023800 + 0x30);       //peripheral clock enable memory address
	uint32_t volatile *const pModeReg_A = (uint32_t*)(0x40020000);           // mode register address for portA
	uint32_t volatile *const pModeReg_D = (uint32_t*)(0x40020C00);          // mode register address for portD

	uint32_t volatile *const pOutputDataReg_A = (uint32_t*)(0x40020000 + 0x14);          //output mode register address for port A
	uint32_t volatile *const pInputDataReg_A = (uint32_t*)(0x40020000 + 0x10);           //input mode register address for port A
	uint32_t volatile *const pPullUpDownReg_A = (uint32_t*)(0x40020000+ 0x0C);           //pull up register for port A

	uint32_t volatile *const pOutputDataReg_D = (uint32_t*)(0x40020C00 + 0x14);         //output mode register address for port D

//	uint32_t volatile *const pPullUpDownReg_D = (uint32_t*)0x40020C0C;    //pull down register for port A


// enable clock for port A and port D
	*pClkctrlReg |= (1 << 0); // port A
	*pClkctrlReg |= (1 << 3); // port D

// configuring PD11 and PD12 as output (Rows).
	*pModeReg_D &= ~(0xF << 22);   //clear
	*pModeReg_D |=  (0x5 << 22);  //set

// configuring PA2 and PA3 as input (Columns).
	*pModeReg_A &= ~(0xf << 4);

// configuring PA4 and PA5 as output for LED
	*pModeReg_A &= ~(0xF << 8);//clear
	*pModeReg_A |= (0x5 << 8);//set

//enabling the up resistor for PA2 and PA3 for port A
	*pPullUpDownReg_A &= ~(0xF << 4);//clear
	*pPullUpDownReg_A |= (0x5 << 4);//set

/*//enabling the down resistor for PD2 and PD3 for port D
	*pPullUpDownReg_D &= ~(0xF << 22);
	*pPullUpDownReg_D |= (0xA << 22);
*/

/* Loop forever */
	while(1){
//make all row gpios HIGH PD11 and PD12
	*pOutputDataReg_D |= (0x3 << 11);

//make row1(PD11) LOW and row2(PD12) HIGH
	*pOutputDataReg_D &= ~(0x1 << 11);

//scan the columns
//check if coloumn1(PA2) is LOW or HIGH
	if( !(*pInputDataReg_A & (1 << 2)) ){
		//key is pressed
		delay();
		*pOutputDataReg_A |= (1 << 4);// Turn LED ON(PA4)
		delay();
		*pOutputDataReg_A &= ~(1 << 4);// Turn LED OFF(PA4)

	}

//check if coloumn2(PA3) is LOW or HIGH
	if( !(*pInputDataReg_A & (1 << 3)) ){
			//key is pressed
		delay();
		*pOutputDataReg_A |= (1 << 5);// Turn LED ON(PA5)
		delay();
		*pOutputDataReg_A &= ~(1 << 5);// Turn LED ON(PA5)

		}

//make all row gpios HIGH PD2 and PD3
	*pOutputDataReg_D |= (0x3 << 11);

//make row1(PD2) LOW
	*pOutputDataReg_D &= ~(0x1 << 12);

//scan the columns
//check if coloumn1(PA2) is LOW or HIGH

	//scan the columns
	//check if coloumn1(PA2) is LOW or HIGH
		if( !(*pInputDataReg_A & (1 << 2)) ){
			//key is pressed
			delay();
			*pOutputDataReg_A |= (1 << 4);// Turn LED ON(PA4)
			delay();
			*pOutputDataReg_A &= ~(1 << 4);// Turn LED OFF(PA4)

		}

	//check if coloumn1(PA3) is LOW or HIGH
		if( !(*pInputDataReg_A & (1 << 3)) ){
				//key is pressed
			delay();
			*pOutputDataReg_A |= (1 << 5);// Turn LED ON(PA5)
			delay();
			*pOutputDataReg_A &= ~(1 << 5);// Turn LED ON(PA5)

			}

	}
}

void delay (void){
	for(uint32_t i=0; i < 300000 ; i++  );
}
