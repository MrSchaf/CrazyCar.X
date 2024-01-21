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
    
    while(1){
        loop(); 
    }
}

void loop(void){
    while(!diStart_GetValue());
    
    do{
//        while(!cycle10ms);
//        cycle10ms = 0;
        getBatteryVoltage();
    }while(BatteryVolt < (minBatValue * 409.6));
    
    oldDistLeft = distLeft;
    oldDistRight = distRight;
    
    while(true){
        while(!cycle10ms);
        cycle10ms = 0;
        
        if(diStop_GetValue()){
            setSpeed = 0;
            setSteering(0,Front);
            break;
        }
        if(ADCC_GetSingleConversion(aiBatt) < minBatValue * 409.6){
            setSpeed = 0;
            setSteering(0,Front);
            break;
        }

        getCurve();
        getReverse();
        
        calcSteering();
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
//    printf("BVolt: %d\n", BatteryVolt);
}

void getCurve(void){
    int16_t deltaLeft;
    int16_t deltaRight;

    switch (curveMode){
        case OutCurve:
            deltaLeft = (int16_t)(distLeft - oldDistLeft);
            deltaRight = (int16_t)(distRight - oldDistRight);
            printf("Out | dL= %d | dR= %d", deltaLeft, deltaRight);
            
            if(deltaLeft > startCurveDelta){
                delay = 0;
                curveMode = BeforeCurve;
                driveMode = CurveLeft;
                printf("   CurveLeft");
            } else if(deltaRight > startCurveDelta){
                delay = 0;
                curveMode = BeforeCurve;
                driveMode = CurveRight;
                printf("   CurveRight");
            }
            printf("\n");

            break;
        case BeforeCurve:
            if(delay > setDelayStart){
                delay = 0;
                curveMode = InCurve;
                printf("InCurve\n");
            } else {
                delay++;
            }
            break;
        case InCurve:
            if(delay > setDelayEnd){
                if(driveMode == CurveLeft){
                    printf("distL= %d\n", distLeft);
                } else if(driveMode == CurveLeft){
                    printf("distR= %d\n", distRight);
                }

                if(distLeft < endCurveValue || distRight < endCurveValue){
                    delay = 0;
                    curveMode = AfterCurve;
                    driveMode = Strait;
                    printf("AfterCurve\n");
                }
            } else {
                delay++;
            }
            break;
        case AfterCurve:
            if(delay > setDelayNew){
                delay = 0;
                curveMode = OutCurve;
                printf("OutCurve\n");
            } else {
                delay++;
            }
            break;
    };
    oldDistLeft = distLeft;
    oldDistRight = distRight;
}

void getReverse(void){
    if(distFront < startReverseDist){
        ++reverseCount;
    }else if(driveMode != Backwards){
        reverseCount = 0;
    }
    
    if(reverseCount > minReverseTime){
        driveMode = Backwards;
        if(distFront > stopReverseDist){
             driveMode = Strait;
             reverseCount = 0;
        }
    } 
}

void calcSteering(void){
    int16_t delta = (int16_t)(distLeft - distRight ) - (int8_t)(middleOffSet * 1.4142135);
    delta /= steeringDivisor;
    
//    printf("L: %d | R: %d | ratio: %d | d: %d\n", distLeft, distRight, ratio, delta);
    
    switch (driveMode){
        case Brake:
            setSteering(delta, Ratio);
            break;
        case Strait:
            setSteering(delta, Front);
            break;
        case Backwards:
            if(distLeft < distRight){
                setSteering(-maxSterringF, Front);
            }else{
                setSteering(maxSterringF, Front);
            }
            break;
        case CurveLeft:
            if(curveMode == InCurve){
                setSteering(maxSterringF, Inverted);
            } else {
                setSteering(delta, Front);
            }
            break;
        case CurveRight:
            if(curveMode == InCurve){
                setSteering(-maxSterringF, Inverted);
            } else {
                setSteering(delta, Front);
            }
            break;
    };
}

//Lenkung 
// neg.: links Lenkung
// pos.: rechts Lenkung
void setSteering(int16_t steering, SteeringMode steeringMode){
    int16_t steeringF = 0, steeringB = 0;
    switch(steeringMode){
        case Inverted:
            steeringF =  (-steering);
            steeringB = steering;
            break;
        case Same:
            steeringF = (-steering);
            steeringB = (-steering);
            break;
        case Ratio:
            steeringF = (-steering);
            steeringB = (steering / steeringRatio);
            break;
        case Front:
            steeringF = (-steering);
            //L_Hinten = 0;
            break;
        case Back:
            //L_Vorne = 0;
            steeringB =  (-steering);
            break;
        default:
            //L_Vorne = 0;
            //L_Hinten = 0;
            break;
    }
    
    if(steeringF > (maxSterringF)){
        steeringF = (maxSterringF);
    } else if(steeringF < (-maxSterringF)){
        steeringF = (-maxSterringF);
    }
    
    if(steeringB > (maxSteeringB)){
        steeringB = (maxSteeringB);
    } else if(steeringB < (-maxSteeringB)){
        steeringB = (-maxSteeringB);
    }
    
    //printf("Lenkung: V:%d H:%d\n", SteeringVOffset - L_Vorne, SteeringHOffset - L_Hinten);
    PWM6_LoadDutyValue((uint16_t)(steeringFOffset - steeringF)); //286->rechts    428->links
    PWM5_LoadDutyValue((uint16_t)(steeringBOffset - steeringB));//255->rechts    460->links
}

void calcSpeed(void){
    int16_t speed = 0;
    
    switch (driveMode){
        case Brake:
            if(distFront > 40) {
                driveMode = Strait;
            }
            
            if(distFront < 40 && setSpeed > 0){
                speed = setSpeed;
                speed -= 1;
            }else if( distFront < 20){
                speed = setSpeed;
                speed -= 2;
            }
            break;
        case Strait:
            if(distFront < 40) {
                driveMode = Brake;
            }
            
            speed = (int16_t)(speedIncrease * distFront + speedOffset);
            break;
        case Backwards:
            speed = reverseSpeed;
            break;
        case CurveLeft:
            speed = curveSpeed;
            break;
        case CurveRight:
            speed = curveSpeed;
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

void calcMotorPow(void){
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

void setMotor(int16_t motorPower){
    if(motorPower > 1){
       if(motorPower > maxMPowForward){
            motorPower = maxMPowForward;
        }
        PWM7_LoadDutyValue((uint16_t)(motorPower));
        PWM8_LoadDutyValue(0);
    } else if(motorPower < -1){
        if(motorPower < maxMPowBackward){
            motorPower = maxMPowBackward;
        }
        PWM7_LoadDutyValue(0);
        PWM8_LoadDutyValue((uint16_t)(-motorPower));
    } else {
        PWM7_LoadDutyValue(0);
        PWM8_LoadDutyValue(0);
    }
}