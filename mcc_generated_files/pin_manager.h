/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F46K42
        Driver Version    :  2.11
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 procedures
#define RA0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define RA0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define RA0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define RA0_GetValue()              PORTAbits.RA0
#define RA0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define RA0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define RA0_SetPullup()             do { WPUAbits.WPUA0 = 1; } while(0)
#define RA0_ResetPullup()           do { WPUAbits.WPUA0 = 0; } while(0)
#define RA0_SetAnalogMode()         do { ANSELAbits.ANSELA0 = 1; } while(0)
#define RA0_SetDigitalMode()        do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set RA1 procedures
#define RA1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define RA1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define RA1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define RA1_GetValue()              PORTAbits.RA1
#define RA1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define RA1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define RA1_SetPullup()             do { WPUAbits.WPUA1 = 1; } while(0)
#define RA1_ResetPullup()           do { WPUAbits.WPUA1 = 0; } while(0)
#define RA1_SetAnalogMode()         do { ANSELAbits.ANSELA1 = 1; } while(0)
#define RA1_SetDigitalMode()        do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set doEnMot1 aliases
#define doEnMot1_TRIS                 TRISAbits.TRISA2
#define doEnMot1_LAT                  LATAbits.LATA2
#define doEnMot1_PORT                 PORTAbits.RA2
#define doEnMot1_WPU                  WPUAbits.WPUA2
#define doEnMot1_OD                   ODCONAbits.ODCA2
#define doEnMot1_ANS                  ANSELAbits.ANSELA2
#define doEnMot1_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define doEnMot1_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define doEnMot1_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define doEnMot1_GetValue()           PORTAbits.RA2
#define doEnMot1_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define doEnMot1_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define doEnMot1_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define doEnMot1_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define doEnMot1_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define doEnMot1_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define doEnMot1_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define doEnMot1_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set RA3 procedures
#define RA3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define RA3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define RA3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define RA3_GetValue()              PORTAbits.RA3
#define RA3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define RA3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define RA3_SetPullup()             do { WPUAbits.WPUA3 = 1; } while(0)
#define RA3_ResetPullup()           do { WPUAbits.WPUA3 = 0; } while(0)
#define RA3_SetAnalogMode()         do { ANSELAbits.ANSELA3 = 1; } while(0)
#define RA3_SetDigitalMode()        do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set RA4 procedures
#define RA4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define RA4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define RA4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define RA4_GetValue()              PORTAbits.RA4
#define RA4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define RA4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define RA4_SetPullup()             do { WPUAbits.WPUA4 = 1; } while(0)
#define RA4_ResetPullup()           do { WPUAbits.WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode()         do { ANSELAbits.ANSELA4 = 1; } while(0)
#define RA4_SetDigitalMode()        do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set doEnMot2 aliases
#define doEnMot2_TRIS                 TRISAbits.TRISA5
#define doEnMot2_LAT                  LATAbits.LATA5
#define doEnMot2_PORT                 PORTAbits.RA5
#define doEnMot2_WPU                  WPUAbits.WPUA5
#define doEnMot2_OD                   ODCONAbits.ODCA5
#define doEnMot2_ANS                  ANSELAbits.ANSELA5
#define doEnMot2_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define doEnMot2_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define doEnMot2_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define doEnMot2_GetValue()           PORTAbits.RA5
#define doEnMot2_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define doEnMot2_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define doEnMot2_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define doEnMot2_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define doEnMot2_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define doEnMot2_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define doEnMot2_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define doEnMot2_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set RA7 procedures
#define RA7_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define RA7_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define RA7_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define RA7_GetValue()              PORTAbits.RA7
#define RA7_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define RA7_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define RA7_SetPullup()             do { WPUAbits.WPUA7 = 1; } while(0)
#define RA7_ResetPullup()           do { WPUAbits.WPUA7 = 0; } while(0)
#define RA7_SetAnalogMode()         do { ANSELAbits.ANSELA7 = 1; } while(0)
#define RA7_SetDigitalMode()        do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set RB0 procedures
#define RB0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()              PORTBbits.RB0
#define RB0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define RB0_SetPullup()             do { WPUBbits.WPUB0 = 1; } while(0)
#define RB0_ResetPullup()           do { WPUBbits.WPUB0 = 0; } while(0)
#define RB0_SetAnalogMode()         do { ANSELBbits.ANSELB0 = 1; } while(0)
#define RB0_SetDigitalMode()        do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()              PORTBbits.RB1
#define RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()             do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()           do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode()         do { ANSELBbits.ANSELB1 = 1; } while(0)
#define RB1_SetDigitalMode()        do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB2 procedures
#define RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RB2_GetValue()              PORTBbits.RB2
#define RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define RB2_SetPullup()             do { WPUBbits.WPUB2 = 1; } while(0)
#define RB2_ResetPullup()           do { WPUBbits.WPUB2 = 0; } while(0)
#define RB2_SetAnalogMode()         do { ANSELBbits.ANSELB2 = 1; } while(0)
#define RB2_SetDigitalMode()        do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set RB3 procedures
#define RB3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define RB3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define RB3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define RB3_GetValue()              PORTBbits.RB3
#define RB3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define RB3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define RB3_SetPullup()             do { WPUBbits.WPUB3 = 1; } while(0)
#define RB3_ResetPullup()           do { WPUBbits.WPUB3 = 0; } while(0)
#define RB3_SetAnalogMode()         do { ANSELBbits.ANSELB3 = 1; } while(0)
#define RB3_SetDigitalMode()        do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set diStart aliases
#define diStart_TRIS                 TRISBbits.TRISB4
#define diStart_LAT                  LATBbits.LATB4
#define diStart_PORT                 PORTBbits.RB4
#define diStart_WPU                  WPUBbits.WPUB4
#define diStart_OD                   ODCONBbits.ODCB4
#define diStart_ANS                  ANSELBbits.ANSELB4
#define diStart_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define diStart_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define diStart_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define diStart_GetValue()           PORTBbits.RB4
#define diStart_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define diStart_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define diStart_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define diStart_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define diStart_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define diStart_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define diStart_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define diStart_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set diStop aliases
#define diStop_TRIS                 TRISBbits.TRISB5
#define diStop_LAT                  LATBbits.LATB5
#define diStop_PORT                 PORTBbits.RB5
#define diStop_WPU                  WPUBbits.WPUB5
#define diStop_OD                   ODCONBbits.ODCB5
#define diStop_ANS                  ANSELBbits.ANSELB5
#define diStop_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define diStop_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define diStop_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define diStop_GetValue()           PORTBbits.RB5
#define diStop_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define diStop_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define diStop_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define diStop_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define diStop_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define diStop_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define diStop_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define diStop_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set RD5 procedures
#define RD5_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define RD5_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define RD5_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define RD5_GetValue()              PORTDbits.RD5
#define RD5_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define RD5_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define RD5_SetPullup()             do { WPUDbits.WPUD5 = 1; } while(0)
#define RD5_ResetPullup()           do { WPUDbits.WPUD5 = 0; } while(0)
#define RD5_SetAnalogMode()         do { ANSELDbits.ANSELD5 = 1; } while(0)
#define RD5_SetDigitalMode()        do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set RD6 procedures
#define RD6_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define RD6_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define RD6_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define RD6_GetValue()              PORTDbits.RD6
#define RD6_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define RD6_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define RD6_SetPullup()             do { WPUDbits.WPUD6 = 1; } while(0)
#define RD6_ResetPullup()           do { WPUDbits.WPUD6 = 0; } while(0)
#define RD6_SetAnalogMode()         do { ANSELDbits.ANSELD6 = 1; } while(0)
#define RD6_SetDigitalMode()        do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set RD7 procedures
#define RD7_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define RD7_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define RD7_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define RD7_GetValue()              PORTDbits.RD7
#define RD7_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define RD7_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define RD7_SetPullup()             do { WPUDbits.WPUD7 = 1; } while(0)
#define RD7_ResetPullup()           do { WPUDbits.WPUD7 = 0; } while(0)
#define RD7_SetAnalogMode()         do { ANSELDbits.ANSELD7 = 1; } while(0)
#define RD7_SetDigitalMode()        do { ANSELDbits.ANSELD7 = 0; } while(0)

// get/set aiBatt aliases
#define aiBatt_TRIS                 TRISEbits.TRISE2
#define aiBatt_LAT                  LATEbits.LATE2
#define aiBatt_PORT                 PORTEbits.RE2
#define aiBatt_WPU                  WPUEbits.WPUE2
#define aiBatt_OD                   ODCONEbits.ODCE2
#define aiBatt_ANS                  ANSELEbits.ANSELE2
#define aiBatt_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define aiBatt_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define aiBatt_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define aiBatt_GetValue()           PORTEbits.RE2
#define aiBatt_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define aiBatt_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define aiBatt_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define aiBatt_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define aiBatt_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define aiBatt_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define aiBatt_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define aiBatt_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);




#endif // PIN_MANAGER_H
/**
 End of File
*/