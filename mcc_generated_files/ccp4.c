/**
  CCP4 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ccp4.c

  @Summary
    This is the generated driver implementation file for the CCP4 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for CCP4.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F46K42
        Driver Version    :  2.1.3
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
         MPLAB 	          :  MPLAB X 5.45
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "ccp4.h"
#include "interrupt_manager.h"

volatile uint16_t distRight;
uint16_t distRightM;

static void (*CCP4_CallBack)(uint16_t);

/**
  Section: Capture Module APIs:
*/

static void CCP4_DefaultCallBack(uint16_t capturedValue)
{
    // Add your code here
    if(PORTDbits.RD6) {
        distRightM = capturedValue;      
//        printf("Value: %d\n", capturedValue);
    } else {
        distRight = capturedValue - distRightM;
        distRight >>= 1;
    }
}
void CCP4_SetCallBack(void (*customCallBack)(uint16_t)){
    CCP4_CallBack = customCallBack;
}
void CCP4_Initialize(void)
{
    // Set the CCP4 to the options selected in the User Interface
	
	// MODE Every edge; EN enabled; FMT right_aligned; 
	CCP4CON = 0x83;    
	
	// CCP4CTS CCP4 pin; 
	CCP4CAP = 0x00;    
	
	// RH 0; 
	CCPR4H = 0x00;    
	
	// RL 0; 
	CCPR4L = 0x00;    
    
    // Set the default call back function for CCP4
    CCP4_SetCallBack(CCP4_DefaultCallBack);

	// Selecting Timer 3
	CCPTMRS0bits.C4TSEL = 0x2;
    
    // Clear the CCP4 interrupt flag
    PIR10bits.CCP4IF = 0;

    // Enable the CCP4 interrupt
    PIE10bits.CCP4IE = 1;
}

void __interrupt(irq(CCP4),base(8)) CCP4_CaptureISR()
{
    CCP4_PERIOD_REG_T module;

    // Clear the CCP4 interrupt flag
    PIR10bits.CCP4IF = 0;
    
    // Copy captured value.
    module.ccpr4l = CCPR4L;
    module.ccpr4h = CCPR4H;
    
    // Return 16bit captured value
    CCP4_CallBack(module.ccpr4_16Bit);
}


/**
 End of File
*/