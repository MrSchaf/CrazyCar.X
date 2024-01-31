/*
 * FINAL RIGHT
 */

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

    while (1) {
        loop();
    }
}

void loop(void) {
    setMotor(0);
    setSteering(0, Front);
    
    while (diStart_GetValue());

    startAccell();
    driveMode = Straight;
    curveMode = OutCurve;
    oldDistLeft = distLeft;
    oldDistRight = distRight;
    cycle10ms = 0;
    while (true) {
        while (!cycle10ms);
        cycle10ms = 0;

        if (!diStop_GetValue()) {
            setSpeed = 0;
            actMotorPow = 0;
            setSteering(0, Front);
            break;
        }

        getCurve();
        getReverse();

        calcSteering();
        calcSpeed();
        calcMotorPow();
    }
}

void TMR4_10msISR(void) {
    ++cycle10ms;
}

int16_t actSpeed() {
    int16_t speed = 0;
    if (smtPeriod) {
        if (CLC3CONbits.LC3OUT) {
            speed = (int16_t) ((int32_t) (500000 / (int32_t) smtPeriod));
        } else {
            speed = (int16_t) ((int32_t) (-500000 / (int32_t) smtPeriod));
        }
    }
    return speed;
}

void startAccell() {
    setSteering(0, Front);
    driveMode = Accel;
    
    actMotorPow = MinMPower;
    float MPow = actMotorPow;
    while (MPow < startMPower) {
        MPow *= startAccelMult;
        actMotorPow = (int16_t) MPow;
        setMotor(actMotorPow);
        
        calcSteering();
        
        cycle10ms = 0;
        while (!cycle10ms);
    }
    actMotorPow = startMPower;
    setMotor(actMotorPow);

    cycle10ms = 0;
    while (cycle10ms < (startAccelTime - startAccellSteps)){
        calcSteering();
    }
    
    driveMode = Straight;
    calcSteering();
}

void getCurve(void) {
    int16_t deltaLeft = (int16_t) (distLeft - oldDistLeft);
    int16_t deltaRight = (int16_t) (distRight - oldDistRight);

    switch (curveMode) {
        case OutCurve:
            if (deltaLeft > startCurveDelta && deltaLeft < maxStartCurveDelta && oldDistLeft < MaxOldDist) {
                delay = 0;
                curveMode = BeforeCurve;
                driveMode = CurveLeft;
            } else if (deltaRight > startCurveDelta && deltaRight < maxStartCurveDelta && oldDistRight < MaxOldDist) {
                delay = 0;
                curveMode = BeforeCurve;
                driveMode = CurveRight;
            }

            break;
        case BeforeCurve:
            if (delay >= setDelayStart) {
                delay = 0;
                curveMode = InCurve;
            } else {
                ++delay;
            }
            break;
        case InCurve:
            if (delay >= setDelayEnd) {
                if ((driveMode == CurveLeft && distLeft < endCurveDist) || (driveMode == CurveRight && distRight < endCurveDist) || distFront > endCurveDistFront) {
                    if (delay >= 70) {
                        middleOffSet = -15;
                    } else {
                        middleOffSet = 15;
                    }
                    delay = 0;
                    curveMode = AfterCurve;
                    driveMode = Straight;
                } else if(driveMode == CurveRight && deltaLeft > switchCurveDelta){
                    delay = 0;
                    curveMode = BeforeCurve;
                    driveMode = CurveLeft;
                }
            }
            ++delay;
            break;
        case AfterCurve:
            if (delay >= setDelayNew) {
                delay = 0;
                curveMode = OutCurve;
            } else {
                ++delay;
            }
            break;
    };
    oldDistLeft = distLeft;
    oldDistRight = distRight;
}

void getReverse(void) {
    if (distFront < startReverseDist) {
        ++reverseCount;
    } else if(driveMode != ReverseRight && driveMode != ReverseLeft) {
        reverseCount = 0;
    }

    if (reverseCount > minReverseTime) {
        ++reverseTime;
        
        if (driveMode != ReverseRight && driveMode != ReverseLeft) {
            if (distLeft > distRight) {
                driveMode = ReverseRight;
            } else {
                driveMode = ReverseLeft;
            }
        }

        if (distFront > stopReverseDist || reverseTime > maxReverseTime) {
            if (distLeft > distRight) {
                driveMode = Straight;
            } else {
                driveMode = Straight;
            }
            
            reverseCount = 0;
            reverseTime = 0;
        }
    }
}

void calcSteering(void) {
    int16_t delta = (int16_t) (distLeft - distRight) - (int16_t) (middleOffSet * 1.4142135);
    delta /= steeringDivisor;

    switch (driveMode) {
        case Accel:
        case Brake:
        case Straight:
        case CurveLeft:
        case CurveRight:
            if (delta > maxSteeringStraight) {
                delta = maxSteeringStraight;
            } else if (delta < -maxSteeringStraight) {
                delta = -maxSteeringStraight;
            }
            break;
        default:
            break;
    }

    switch (driveMode) {
        case Brake:
            setSteering(delta, Ratio);
            break;
        case Straight:
            setSteering(delta, Front);
            break;
        case Accel:
            setSteering(delta / startAccellSteeringRatio, Front);
            break;
        case ReverseRight:
            setSteering(-curveSteering, Inverted);
            break;
        case ReverseLeft:
            setSteering(curveSteering, Inverted);
            break;
        case CurveLeft:
            if (curveMode == InCurve) {
                setSteering(curveSteering, Ratio);
            } else {
                setSteering(delta, Ratio);
            }
            break;
        case CurveRight:
            if (curveMode == InCurve) {
                setSteering(-curveSteering, Ratio);
            } else {
                setSteering(delta, Ratio);
            }
            break;
    };
}

void calcSpeed(void) {
    int16_t speed = 0;

    switch (driveMode) {
        case Brake:
            if (distFront > BrakeDistance) {
                driveMode = Straight;
            }
            if (setSpeed > minDriveSpeed) {
                    speed = setSpeed;
                if (distFront < BrakeDistanceStrong) {
                    speed -= 4;
                } else {
                    speed -= 2;
                }
            }else{
                speed = minDriveSpeed;
            }
            break;
        case Accel:
        case Straight:
            if (distFront < BrakeDistance) {
                driveMode = Brake;
            }

            if (distFront >= MinDistAccel) {
                speed = (int16_t) (speedIncrease * (distFront - MinDistAccel) + MinStraightSpeed);
            } else {
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

    if (speed > maxSpeedForward) {
        speed = maxSpeedForward;
    }
    if (speed < maxSpeedBackward) {
        speed = maxSpeedBackward;
    }
    setSpeed = speed;
}

void calcMotorPow(void) {
    currentSpeed = actSpeed();
    
    int16_t setSpeedDelta = setSpeed - currentSpeed;
    int16_t oldSpeedDelta = currentSpeed - oldSpeed;
    int8_t addMPow = 0;
    
    addMPow = (int8_t) (MotorPowFactor * (setSpeedDelta - (oldSpeedDelta / oldSpeedDeltaDivisor)));

    if (addMPow > maxAddMPow) {
        addMPow = maxAddMPow;
    } else if (addMPow < -maxAddMPow) {
        addMPow = -maxAddMPow;
    }

    actMotorPow += addMPow;

    if (actMotorPow > maxMPowForward) {
        actMotorPow = maxMPowForward;
    } else if (actMotorPow < maxMPowBackward) {
        actMotorPow = maxMPowBackward;
    }

    setMotor(actMotorPow);

    oldSpeed = currentSpeed;
}

void setMotor(int16_t motorPower) {
    if (motorPower >= MinMPower) {
        if (motorPower > maxMPowForward) {
            motorPower = maxMPowForward;
        }
        PWM7_LoadDutyValue((uint16_t) (motorPower));
        PWM8_LoadDutyValue(0);
    } else if (motorPower <= -MinMPower) {
        if (motorPower < maxMPowBackward) {
            motorPower = maxMPowBackward;
        }
        PWM7_LoadDutyValue(0);
        PWM8_LoadDutyValue((uint16_t) (-motorPower));
    } else {
        PWM7_LoadDutyValue(0);
        PWM8_LoadDutyValue(0);
    }
}

//Lenkung 
// neg.: links Lenkung
// pos.: rechts Lenkung
void setSteering(int16_t steering, SteeringMode steeringMode) {
    int16_t steeringF = 0, steeringB = 0;
    switch (steeringMode) {
        case Inverted:
            steeringF = (+steering);
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
            steeringB = (+steering);
            break;
        default:
            steeringF = 0;
            steeringB = 0;
            break;
    }

    if (steeringF > (maxSteeringF)) {
        steeringF = (maxSteeringF);
    } else if (steeringF < (-maxSteeringF)) {
        steeringF = (-maxSteeringF);
    }

    if (steeringB > (maxSteeringB)) {
        steeringB = (maxSteeringB);
    } else if (steeringB < (-maxSteeringB)) {
        steeringB = (-maxSteeringB);
    }
    
    PWM6_LoadDutyValue((uint16_t) (steeringFOffset + steeringF)); //286->rechts    428->links
    PWM5_LoadDutyValue((uint16_t) (steeringBOffset + steeringB)); //255->rechts    460->links
} 