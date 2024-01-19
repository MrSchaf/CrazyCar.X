/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F46K42
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB             :  MPLAB X 5.45

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
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

#include "pin_manager.h"





void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATE = 0x00;
    LATD = 0x00;
    LATA = 0x24;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISE = 0x07;
    TRISA = 0xC0;
    TRISB = 0xF7;
    TRISC = 0xFF;
    TRISD = 0xFF;

    /**
    ANSELx registers
    */
    ANSELD = 0x1F;
    ANSELC = 0xFF;
    ANSELB = 0xC0;
    ANSELE = 0x07;
    ANSELA = 0x7F;

    /**
    WPUx registers
    */
    WPUD = 0x00;
    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    RxyI2C registers
    */
    RB1I2C = 0x00;
    RB2I2C = 0x00;
    RC3I2C = 0x00;
    RC4I2C = 0x00;
    RD0I2C = 0x00;
    RD1I2C = 0x00;

    /**
    ODx registers
    */
    ODCONE = 0x00;
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    ODCOND = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;
    SLRCOND = 0xFF;
    SLRCONE = 0x07;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLD = 0xFF;
    INLVLE = 0x0F;





   
    
	
    CCP3PPS = 0x1F;   //RD7->CCP3:CCP3;    
    CLCIN3PPS = 0x09;   //RB1->CLC3:CLCIN3;    
    RA1PPS = 0x0E;   //RA1->PWM6:PWM6;    
    U1RXPPS = 0x0A;   //RB2->UART1:RX1;    
    RA0PPS = 0x0D;   //RA0->PWM5:PWM5;    
    T5GPPS = 0x1D;   //RD5->TMR5:T5G;    
    RA4PPS = 0x10;   //RA4->PWM8:PWM8;    
    CLCIN0PPS = 0x07;   //RA7->CLC3:CLCIN0;    
    SMT1WINPPS = 0x09;   //RB1->SMT1:SMT1WIN;    
    RA3PPS = 0x0F;   //RA3->PWM7:PWM7;    
    RB3PPS = 0x13;   //RB3->UART1:TX1;    
    CLCIN2PPS = 0x08;   //RB0->CLC3:CLCIN2;    
    SMT1SIGPPS = 0x08;   //RB0->SMT1:SMT1SIG;    
    CCP4PPS = 0x1E;   //RD6->CCP4:CCP4;    
}
  
void PIN_MANAGER_IOC(void)
{   
}

/**
 End of File
*/