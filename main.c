#include "mcc_generated_files/mcc.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

// höher = links | niedriger = rechts
#define LenkungVOffset 352
// höher = links | niedriger = rechts
#define LenkungHOffset 357
#define MaxV 65
#define MaxH 45
#define LenkungsVerhaeltnis 3

typedef enum{
    Schnell,
    Langsam,
    Ruckwarts,
    KurveLinks,
    KurveRechts
}FahrModus;

typedef enum{
    Invertiert,
    Gleich,
    Verhaeltnis,
    Vorne,
    Hinten
}LenkungsModus;

extern uint16_t distFront, distLeft, distRight;
extern int32_t smtWay;      //1 increment == 2,7mm ;370 == 1m
extern uint32_t smtPeriod;

FahrModus fahrModus = Langsam;

uint8_t cycle10ms;
// -1023 .. 1023
int16_t motPow = 0;
adc_result_t BatteryVolt;

int16_t setSpeed;
int16_t currentSpeed;

int16_t oldSpeed;
int16_t oldSpeedDelta;

int16_t actMotorPow;
int16_t maxMPowForward = 300;
int16_t maxMPowBackward = -200;

int16_t defaultMotorPowerForward = 150;
int16_t defaultMotorPowerBackward = 100;

void loop();

void TMR4_10msISR(void);
int16_t actSpeed();

void outBatteryVoltage(void);

void calcLenkung();
void setLenkung(int16_t, LenkungsModus);
void calcSpeed();
void calcMotorPow();
void setMotor(int16_t);

void main(void) {
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();
    
    TMR4_SetInterruptHandler(TMR4_10msISR);
    
    loop(); 
}

void loop(){
    //stop if bat is low
    do{
//        while(!cycle10ms);
//        cycle10ms = 0;
        
        BatteryVolt = ADCC_GetSingleConversion(aiBatt);  //adc = (vbat /2) * (4096 /5) -->2800 = 3,4V (leer)
        outBatteryVoltage();
    }while(BatteryVolt < 2800);
    
    while(true){
        while(!cycle10ms);
        cycle10ms = 0;
        
//        printf("L: %d | R: %d | F: %d\n", distLeft, distRight, distFront);
        printf("main\n");
        
        setSpeed = 150;
        
//        outBatteryVoltage();
        calcMotorPow();
        calcLenkung();
//        setLenkung(0, Invertiert);
    }
}

void TMR4_10msISR(void){
    ++cycle10ms;
}

int16_t actSpeed(){
    int16_t speed = 0;
    if(smtPeriod){
        if(CLC3CONbits.LC3OUT){
            speed = ((int32_t)(500000 / (int32_t)smtPeriod));
        } else {
            speed = ((int32_t)(-500000 / (int32_t)smtPeriod));
        }
    }
    return speed;
}

void outBatteryVoltage(void){
    adc_result_t batt = -1;
    batt = ADCC_GetSingleConversion(aiBatt);
    printf("BVolt: %d\n", batt);
}

void calcLenkung(){
//    float delta = distLeft - distRight;
    
    float ratio = 1;
//    if(distRight != 0){
//        ratio = distLeft / distRight;
//    }
    
//    printf("L: %d | R: %d | ratio: %d | d: %d\n", distLeft, distRight, ratio, delta);
    
    switch (fahrModus){
        case Langsam:
//            setLenkung(delta, Invertiert);
            break;
        case Schnell:
            
            break;
        case Ruckwarts:
            
            break;
        case KurveLinks:
            
            break;
        case KurveRechts:
            
            break;
    };
}

//Lenkung 
// neg.: links Lenkung
// pos.: rechts Lenkung
void setLenkung(int16_t Lenkung, LenkungsModus LenkungMode){
    int16_t L_Vorne = 0, L_Hinten = 0;
    switch(LenkungMode){
        case Invertiert:
            L_Vorne =  (-Lenkung);
            L_Hinten = Lenkung;
            break;
        case Gleich:
            L_Vorne = (-Lenkung);
            L_Hinten = (-Lenkung);
            break;
        case Verhaeltnis:
            L_Vorne = (-Lenkung);
            L_Hinten = (-Lenkung / LenkungsVerhaeltnis);
            break;
        case Vorne:
            L_Vorne = (-Lenkung);
            //L_Hinten = 0;
            break;
        case Hinten:
            //L_Vorne = 0;
            L_Hinten =  (-Lenkung);
            break;
        default:
            //L_Vorne = 0;
            //L_Hinten = 0;
            break;
    }
    
    if(L_Vorne > (MaxV)){
        L_Vorne = (MaxV);
    } else if(L_Vorne < (-MaxV)){
        L_Vorne = (-MaxV);
    }
    
    if(L_Hinten > (MaxH)){
        L_Hinten = (MaxH);
    } else if(L_Hinten < (-MaxH)){
        L_Hinten = (-MaxH);
    }
    
    //printf("Lenkung: V:%d H:%d\n", LenkungVOffset - L_Vorne, LenkungHOffset - L_Hinten);
    PWM6_LoadDutyValue(LenkungVOffset - L_Vorne); //286->rechts    428->links
    PWM5_LoadDutyValue(LenkungHOffset - L_Hinten);//255->rechts    460->links
}

void calcSpeed(){
    
}

void calcMotorPow(){
    float factor = 0.5;
    
    oldSpeed = currentSpeed;
    currentSpeed = actSpeed();
//    printf("%d | ", currentSpeed);
    
	int16_t setSpeedDelta = setSpeed - currentSpeed;
    int16_t addMPow = 0;
    
	addMPow = factor * (setSpeedDelta - (oldSpeedDelta / 2));
    
    if(setSpeed > 0){
		if(actMotorPow < 10){
			actMotorPow = defaultMotorPowerForward;
		}
	}else if(setSpeed < 0){
		if(actMotorPow > -10){
			actMotorPow = defaultMotorPowerBackward;
		}
		addMPow /= 2;
	}else{
		actMotorPow = 0;
        addMPow = 0;
	}
	
	actMotorPow += addMPow;
	
	if(actMotorPow > maxMPowForward){
		actMotorPow = maxMPowForward;
	}else if(actMotorPow < maxMPowBackward){
		actMotorPow = maxMPowBackward;
	}else if(actMotorPow < 10 && actMotorPow > -10){
		actMotorPow = 0;
	}
    
//    printf("%d\n", actMotorPow);
    setMotor(actMotorPow);
    
    oldSpeedDelta = setSpeedDelta;
}

void setMotor(int16_t MotorPower){
    int16_t limit = 100;
    if(MotorPower > 8){
       if(MotorPower > limit){
            MotorPower = limit;
        }
        PWM7_LoadDutyValue(MotorPower);
        PWM8_LoadDutyValue(0);
    } else if(MotorPower < -8){
        if(MotorPower < -limit){
            MotorPower = -limit;
        }
        PWM7_LoadDutyValue(0);
        PWM8_LoadDutyValue(-MotorPower);
    } else {
        PWM7_LoadDutyValue(0);
        PWM8_LoadDutyValue(0);
    }
}