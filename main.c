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
    setMotor(0);
    setSteering(0,Front);
    while(diStart_GetValue());
    
    do{
        while(!cycle10ms);
        cycle10ms = 0;
        getBatteryVoltage();
//        printf("BVolt: %u\n", (uint16_t)BatteryVolt);
    }while(BatteryVolt < (minBatValue * 409.6)); // adc = (vbat * 409.6)
    
    startAccell();
    
    oldDistLeft = distLeft;
    oldDistRight = distRight;
    cycle10ms =  0;
    while(true){
        while(!cycle10ms);
        cycle10ms = 0;
        
        if(!diStop_GetValue()){
            setSpeed = 0;
            actMotorPow = 0;
            setSteering(0,Front);
            break;
        }
         
        ++tempCNT;
        if(tempCNT > 1000){
            tempCNT = 0;
            printf("10s passed\n");
        }
        
        if(checkBatt()){
            break;
        }
        
        getCurve();
        getReverse();
        
        calcSteering();
        calcSpeed();
        calcMotorPow();
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
    printf("BVolt: %u\n", (uint16_t) BatteryVolt);
}

bool checkBatt(){
    ++battCheckCount;
    if(battCheckCount > BattCheckPeriod){
        battCheckCount = 0;
        getBatteryVoltage();
        if(BatteryVolt < minBatValue * 409.6){
            setSpeed = 0;
            setSteering(0,Front);
            return true;
        }
    }
    return false;
}

void startAccell(){
    actMotorPow = startMPower;
    setMotor(actMotorPow);
    setSteering(0,Front);
    cycle10ms = 0;   
    while(cycle10ms < startAccelTime);
}

void getCurve(void){
    int16_t deltaLeft;
    int16_t deltaRight;

    switch (curveMode){
        case OutCurve:
            deltaLeft = (int16_t)(distLeft - oldDistLeft);
            deltaRight = (int16_t)(distRight - oldDistRight);
            //printf("Out | dL= %d | dR= %d", deltaLeft, deltaRight);

            if(deltaLeft > startCurveDelta && deltaLeft < maxStartCurveDelta && oldDistLeft < MaxOldDist){
                delay = 0;
                curveMode = BeforeCurve;
                driveMode = CurveLeft;
//                printf("Out | dL= %d | dR= %d", deltaLeft, deltaRight);
//                printf("   CurveLeft");
            } else if(deltaRight > startCurveDelta && deltaRight < maxStartCurveDelta && oldDistRight < MaxOldDist){
                delay = 0;
                curveMode = BeforeCurve;
                driveMode = CurveRight;
//                printf("Out | dL= %d | dR= %d", deltaLeft, deltaRight);
//                printf("   CurveRight");
            }
            //printf("\n");

            break;
        case BeforeCurve:
            if(delay > setDelayStart){
                delay = 0;
                curveMode = InCurve;
//                printf("InCurve\n");
            } else {
                delay++;
            }
            break;
        case InCurve:
            if(delay > setDelayEnd){
                if(driveMode == CurveLeft){
                    //printf("distL= %d\n", distLeft);
                } else if(driveMode == CurveLeft){
                    //printf("distR= %d\n", distRight);
                }

                if(distLeft < endCurveDist || distRight < endCurveDist || distFront > endCurveDistFront){
                    delay = 0;
                    curveMode = AfterCurve;
                    driveMode = Straight;
                    //printf("AfterCurve\n");
                }
            } else {
                delay++;
            }
            break;
        case AfterCurve:
            if(delay > setDelayNew){
                delay = 0;
                curveMode = OutCurve;
                //printf("OutCurve\n");
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
    }else{
        reverseCount = 0;
    }
    
    if(reverseCount > minReverseTime){
        ++reverseTime;
        
        if(driveMode != ReverseRight && driveMode != ReverseLeft){
            if(distLeft > distRight){
//                printf("ReverseRigth\n");
                driveMode = ReverseRight;
            }else{
//                printf("ReverseLeft\n");
                driveMode = ReverseLeft;
            }
        }

        if(distFront > stopReverseDist || reverseTime > maxReverseTime){
//            printf("Stop Reverse\n");
             driveMode = Straight;
             reverseCount = 0;
             reverseTime = 0;
        }
    } 
}

void calcSteering(void){
    int16_t delta = (int16_t)(distLeft - distRight ) - (int16_t)(middleOffSet * 1.4142135);
    delta /= steeringDivisor;
    
//    printf("L: %d | R: %d | d: %d\n", distLeft, distRight, delta);
    switch (driveMode){
        case Brake:
        case Straight:
        case CurveLeft:
        case CurveRight:
            if(delta > maxSteeringStraight){
                delta = maxSteeringStraight;
            }else if(delta < -maxSteeringStraight){
                delta = -maxSteeringStraight;
            }
            break;   
        default:
            break;
    }
    
    switch (driveMode){     
        case Brake:
            setSteering(delta, Ratio);
            break;
        case Straight:
            setSteering(delta, Front);
            break;
        case ReverseRight:
            setSteering(maxSteeringF, Inverted);
            break;
        case ReverseLeft:
            setSteering(maxSteeringF, Inverted);
            break;    
        case CurveLeft:
            if(curveMode == InCurve){
                setSteering(curveSteering, Ratio);
            } else {
                setSteering(delta, Front);
            }
            break;
        case CurveRight:
            if(curveMode == InCurve){
                setSteering(-curveSteering, Ratio);
            } else {
                setSteering(delta, Front);
            }
            break;
    };
}

void calcSpeed(void){
    int16_t speed = 0;
    
    switch (driveMode){
        case Brake:
            if(distFront > BrakeDistance) {
                driveMode = Straight;
            }
            if(setSpeed > minDriveSpeed){
                if(setSpeed > 0 ){
                    speed = setSpeed;
                    speed -= 2;
                }else if( setSpeed > 0 && distFront < BrakeDistanceStrong){
                    speed = setSpeed;
                    speed -= 4;
                }
            }
            break;
        case Straight:
            if(distFront < BrakeDistance) {
                driveMode = Brake;
            }

            if(distFront > MinDistAccel){
                speed = (int16_t)(speedIncrease * (distFront - MinDistAccel) + MinStraightSpeed);
            }else{
                speed = MinStraightSpeed;
            }
            
            
            break;
        case ReverseRight:
            speed = reverseSpeed;
            break;
        case ReverseLeft:
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
    if(motorPower > MinMPower){
       if(motorPower > maxMPowForward){
            motorPower = maxMPowForward;
        }
        PWM7_LoadDutyValue((uint16_t)(motorPower));
        PWM8_LoadDutyValue(0);
    } else if(motorPower < -MinMPower){
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

//Lenkung 
// neg.: links Lenkung
// pos.: rechts Lenkung
void setSteering(int16_t steering, SteeringMode steeringMode){
    int16_t steeringF = 0, steeringB = 0;
    switch(steeringMode){
        case Inverted:
            steeringF =  (+steering);
            steeringB = -steering;
            break;
        case Same:
            steeringF = (+steering);
            steeringB = (+steering);
            break;
        case Ratio:
            steeringF = (+steering);
            steeringB = (-steering / steeringRatio);
            break;
        case Front:
            steeringF = (+steering);
            steeringB = 0;
            break;
        case Back:
            steeringF = 0;
            steeringB =  (+steering);
            break;
        default:
            steeringF = 0;
            steeringB = 0;
            break;
    }
    
    if(steeringF > (maxSteeringF)){
        steeringF = (maxSteeringF);
    } else if(steeringF < (-maxSteeringF)){
        steeringF = (-maxSteeringF);
    }
    
    if(steeringB > (maxSteeringB)){
        steeringB = (maxSteeringB);
    } else if(steeringB < (-maxSteeringB)){
        steeringB = (-maxSteeringB);
    }
    
    //printf("Lenkung: V:%d H:%d\n", SteeringVOffset - L_Vorne, SteeringHOffset - L_Hinten);
    PWM6_LoadDutyValue((uint16_t)(steeringFOffset + steeringF)); //286->rechts    428->links
    PWM5_LoadDutyValue((uint16_t)(steeringBOffset + steeringB));//255->rechts    460->links
}