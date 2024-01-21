#ifndef MAIN_H
#define	MAIN_H

#define steeringFOffset                (352)     // höher = links | niedriger = rechts
#define steeringBOffset                (357)     // höher = links | niedriger = rechts
#define maxSterringF                   (65)
#define maxSteeringB                   (45)
#define steeringRatio                  (3)
#define minBatValue                    (7.4)     // adc = (vbat /2) * (4096 /5) -->2800 = 3,4V (leer)

#define maxMPowForward                 (600)
#define maxSpeedForward                (400)
#define defaultMotorPowerForward       (250)

#define maxMPowBackward                (-300)
#define maxSpeedBackward               (-250)
#define defaultMotorPowerBackward      (-100)

#define setDelayStart                  (5)       // Delay bevor man zu Lenken beginnt
#define setDelayEnd                    (20)      // Delay bevor man die Kurve abbrechen kann
#define setDelayNew                    (20)      // Delay bevor man eine neue Kurve erkennen kann

#define startCurveDelta                (50)      // (oldDist - actDist) > startCurveDelta --> Kurve

#define endCurveValue                  (40)      // dist < endKurveValue --> Kurvenende

#define startReverseDist               (10)      // distFront < startReverseDist --> reverseCount++
#define minReverseTime                 (25)
#define stopReverseDist                (40)      // distFront > stopReverseDist  --> fahrModus = Gerade

#define middleOffSet                   (0)       // cm * sqr(2) = verschiebung in cm nach links oder rechts

#define steeringDivisor                (2)       // distLeft - distRight /= lenkungDivisor;

#define MotorPowFactor                 (0.05)

#define speedIncrease                  (0.8)
#define speedOffset                    (150)

#define maxAddMPow                     (3)

#define oldSpeedDeltaDivisor           (1)

#define curveSpeed                     (150)
#define reverseSpeed                   (-150)
    
typedef enum{
    Straight,
    Brake,
    Backwards,
    CurveLeft,
    CurveRight
}DriveMode;

typedef enum{
    Inverted,
    Same,
    Ratio,
    Front,
    Back
}SteeringMode;

typedef enum{
    OutCurve,
    BeforeCurve,
    InCurve,
    AfterCurve
} CurveMode;

extern uint16_t distFront, distLeft, distRight;
extern int32_t smtWay;      //1 increment == 2,7mm ;370 == 1m
extern uint32_t smtPeriod;

DriveMode driveMode = Straight;
CurveMode curveMode = OutCurve;

uint8_t cycle10ms = 0;
uint8_t delay = 0;
uint8_t reverseCount = 0;

uint16_t oldDistLeft, oldDistRight;

int16_t motPow = 0;
int16_t setSpeed = 0;
int16_t currentSpeed = 0;
int16_t oldSpeed = 0;
int16_t actMotorPow = 0;

adc_result_t BatteryVolt = 0;

void TMR4_10msISR(void);

void loop(void);

int16_t actSpeed();
void getBatteryVoltage(void);

void getCurve(void);
void getReverse(void);

void calcSteering(void);
void calcSpeed(void);
void calcMotorPow(void);

void setSteering(int16_t, SteeringMode);
void setMotor(int16_t);


#endif	/* MAIN_H */