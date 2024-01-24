/**
  CCP3 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ccp3.c

  @Summary
    This is the generated driver implementation file for the CCP3 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for CCP3.
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
#include "ccp3.h"
#include "interrupt_manager.h"

volatile uint16_t distLeft;
uint16_t distLeftM;

static void (*CCP3_CallBack)(uint16_t);

/**
  Section: Capture Module APIs:
*/ 

static void CCP3_DefaultCallBack(uint16_t capturedValue)
{
    // Add your code here
    if(PORTDbits.RD7) {
        distLeftM = capturedValue;
    } else {
        distLeft = capturedValue - distLeftM;
        distLeft >>= 1;
    }
}

void CCP3_Initialize(void)
{
    // Set the CCP3 to the options selected in the User Interface
	
	// MODE Every edge; EN enabled; FMT right_aligned; 
	CCP3CON = 0x83;    
	
	// CCP3CTS CCP3 pin; 
	CCP3CAP = 0x00;    
	
	// RH 0; 
	CCPR3H = 0x00;    
	
	// RL 0; 
	CCPR3L = 0x00;    
    
    // Set the default call back function for CCP3
    CCP3_SetCallBack(CCP3_DefaultCallBack);

	// Selecting Timer 3
	CCPTMRS0bits.C3TSEL = 0x2;
    
    // Clear the CCP3 interrupt flag
    PIR9bits.CCP3IF = 0;

    // Enable the CCP3 interrupt
    PIE9bits.CCP3IE = 1;
}

void __interrupt(irq(CCP3),base(8)) CCP3_CaptureISR()
{
    CCP3_PERIOD_REG_T module;

    // Clear the CCP3 interrupt flag
    PIR9bits.CCP3IF = 0;
    
    // Copy captured value.
    module.ccpr3l = CCPR3L;
    module.ccpr3h = CCPR3H;
    
    // Return 16bit captured value
    CCP3_CallBack(module.ccpr3_16Bit);
}

void CCP3_SetCallBack(void (*customCallBack)(uint16_t)){
    CCP3_CallBack = customCallBack;
}
/**
 End of File
*/