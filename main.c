#include "mcc_generated_files/mcc.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"


void main(void) {
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();
    TMR4_SetInterruptHandler(TMR4_10msISR);
    
    loop(); 
}

void loop(){
    while(!diStart_GetValue());
    
    do{
//        while(!cycle10ms);
//        cycle10ms = 0;
        getBatteryVoltage();
    }while(BatteryVolt < MinBattValue);                          
    
    
    
    oldDistLeft = distLeft;
    oldDistRight = distRight;
    
    while(true){
        while(!cycle10ms);
        cycle10ms = 0;
        
        if(diStop_GetValue()){
            break;
        }
        if(ADCC_GetSingleConversion(aiBatt) < MinBattValue){
            setSpeed = 0;
            setLenkung(0,Vorne);
            break;
        }

        getKurve();
        getReverse();
        
        calcLenkung();
        calcMotorPow();
        calcSpeed();
    }
}

void TMR4_10msISR(void){
    ++cycle10ms;
}

int16_t actSpeed(){
    int16_t speed = 0;
    if(smtPeriod){
        if(CLC3CONbits.LC3OUT){
            speed = (int16_t)((int32_t)(500000 / (int32_t)smtPeriod));
        } else {
            speed = (int16_t)((int32_t)(-500000 / (int32_t)smtPeriod));
        }
    }
    return speed;
}

void getBatteryVoltage(void){
    BatteryVolt = ADCC_GetSingleConversion(aiBatt);
    printf("BVolt: %d\n", BatteryVolt);
}

void getKurve(){
    int16_t deltaLeft;
    int16_t deltaRight;

    switch (kurvenModus){
        case AusKurve:
            deltaLeft = (int16_t)(distLeft - oldDistLeft);
            deltaRight = (int16_t)(distRight - oldDistRight);
            printf("Aus| dL= %d| dR= %d", deltaLeft, deltaRight);
            
            if(deltaLeft > startKurveDelta){
                delay = 0;
                kurvenModus = VorKurve;
                fahrModus = KurveLinks;
                printf("   KurveLinks");
            } else if(deltaRight > startKurveDelta){
                delay = 0;
                kurvenModus = VorKurve;
                fahrModus = KurveRight;
                printf("   KurveRight");
            }
            printf("\n");

            break;
        case VorKurve:
            if(delay > setDelayStart){
                delay = 0;
                kurvenModus = InKurve;
                printf("InKurve\n");
            } else {
                delay++;
            }
            break;
        case InKurve:
            if(delay > setDelayEnd){
                if(fahrModus == KurveLinks){
                    printf("distL= %d\n", distLeft);
                } else if(fahrModus == KurveLinks){
                    printf("distR= %d\n", distRight);
                }

                if(distLeft < endKurveValue || distRight < endKurveValue){
                    delay = 0;
                    kurvenModus = NachKurve;
                    fahrModus = Gerade;
                    printf("NachKurve\n");
                }
            } else {
                delay++;
            }
            break;
        case NachKurve:
            if(delay > setDelayNew){
                delay = 0;
                kurvenModus = AusKurve;
                printf("AusKurve\n");
            } else {
                delay++;
            }
            break;
    };
    oldDistLeft = distLeft;
    oldDistRight = distRight;
}

void getReverse(){
    if(distFront < startReverseDist){
        ++reverseCount;
    }else if(fahrModus != Ruckwarts){
        reverseCount = 0;
    }
    
    if(reverseCount > minReverseTime){
        fahrModus = Ruckwarts;
        if(distFront > stopReverseDist){
             fahrModus = Gerade;
             reverseCount = 0;
        }
    } 
}

void calcLenkung(){
    int16_t delta = (int16_t)(distLeft - distRight )- middleOffSet;
    delta /= lenkungDivisor;
    
//    printf("L: %d | R: %d | ratio: %d | d: %d\n", distLeft, distRight, ratio, delta);
    
    switch (fahrModus){
        case Bremsen:
            setLenkung(delta, Verhaeltnis);
            break;
        case Gerade:
            setLenkung(delta, Vorne);
            break;
        case Ruckwarts:
            if(distLeft < distRight){
                setLenkung(-MaxV, Vorne);
            }else{
                setLenkung(MaxV, Vorne);
            }
            break;
        case KurveLinks:
            if(kurvenModus == InKurve){
                setLenkung(MaxV, Invertiert);
            } else {
                setLenkung(delta, Vorne);
            }
            break;
        case KurveRight:
            if(kurvenModus == InKurve){
                setLenkung(-MaxV, Invertiert);
            } else {
                setLenkung(delta, Vorne);
            }
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
            L_Hinten = (Lenkung / LenkungsVerhaeltnis);
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
    PWM6_LoadDutyValue((uint16_t)(LenkungVOffset - L_Vorne)); //286->rechts    428->links
    PWM5_LoadDutyValue((uint16_t)(LenkungHOffset - L_Hinten));//255->rechts    460->links
}


void calcSpeed(){
    int16_t limit;
    int16_t speed = 0;
    
    switch (fahrModus){
        case Bremsen:
            if(distFront > 40) {
                fahrModus = Gerade;
            }
            
            if(distFront < 40 && setSpeed > 0){
                speed = setSpeed;
                speed -= 1;
            }else if( distFront < 20){
                speed = setSpeed;
                speed -= 2;
            }
            break;
        case Gerade:
            if(distFront < 40) {
                fahrModus = Bremsen;
            }
            speed = (int16_t)(speedSteigung * distFront + speedOffset);
            break;
        case Ruckwarts:
            speed = reverseSpeed;
            break;
        case KurveLinks:
            speed = kurvenSpeed;
            break;
        case KurveRight:
            speed = kurvenSpeed;
            break;
    };
    
    if(speed > maxSpeedForward){
        speed = maxSpeedForward;
    }
    if(speed < maxSpeedBackward){
        speed = maxSpeedBackward;
    }
    setSpeed = speed;
}

void calcMotorPow(){
    int16_t setSpeedDelta = setSpeed - currentSpeed;
    int16_t oldSpeedDelta = currentSpeed - oldSpeed;
    int8_t addMPow = 0;
	
    currentSpeed = actSpeed();
//    printf("actSpeed:= %d | setSpeed= %d |", currentSpeed,setSpeed);
//    printf("setSpeedDelta:= %d | oldSpeedDelta= %d |", setSpeedDelta,oldSpeedDelta);
    
    
	addMPow = (int8_t)(MotorPowFactor * (setSpeedDelta - (oldSpeedDelta / oldSpeedDeltaDivisor)));
    
    
    if(addMPow > maxAddMPow){
        addMPow = maxAddMPow;
    }else if(addMPow < -maxAddMPow){
        addMPow = -maxAddMPow;
    }
    
  
	actMotorPow = actMotorPow + addMPow;
	
	if(actMotorPow > maxMPowForward){
		actMotorPow = maxMPowForward;
	}else if(actMotorPow < maxMPowBackward){
		actMotorPow = maxMPowBackward;
	}
     
   
    setMotor(actMotorPow);
    
    oldSpeed = currentSpeed;
}

void setMotor(int16_t MotorPower){
    if(MotorPower > 1){
       if(MotorPower > maxMPowForward){
            MotorPower = maxMPowForward;
        }
        PWM7_LoadDutyValue((uint16_t)(MotorPower));
        PWM8_LoadDutyValue(0);
    } else if(MotorPower < -1){
        if(MotorPower < maxMPowBackward){
            MotorPower = maxMPowBackward;
        }
        PWM7_LoadDutyValue(0);
        PWM8_LoadDutyValue((uint16_t)(-MotorPower));
    } else {
        PWM7_LoadDutyValue(0);
        PWM8_LoadDutyValue(0);
    }
}