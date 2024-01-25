
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define steeringFOffset                (352)     // höher = links | niedriger = rechts
#define steeringBOffset                (357)     // höher = links | niedriger = rechts
#define maxSterringF                   (65)
#define maxSteeringB                   (40)
#define maxSteeringStraight            (30)      //kann beim geradeaus fahren nicht mehr lenken
#define steeringRatio                  (3)
#define minBatValue                    (7.5)     // Mindestspg in Volt adc = (vbat * 409.6)

#define maxMPowForward                 (700)
#define maxSpeedForward                (450)
#define defaultMotorPowerForward       (250)

#define maxMPowBackward                (-300)
#define maxSpeedBackward               (-200)
#define defaultMotorPowerBackward      (-150)

#define setDelayStart                  (15)       // Delay bevor man zu Lenken beginnt
#define setDelayEnd                    (60)      // Delay bevor man die Kurve abbrechen kann
#define setDelayNew                    (50)      // Delay bevor man eine neue Kurve erkennen kann

#define startCurveDelta                (60)      // ((oldDist - actDist) > startCurveDelta  \n
#define MaxOldDist                     (200)     //  && oldDistLeft < MaxOldDist)  --> Kurv

#define endCurveValue                  (40)      // distF < endKurveValue --> Kurvenende

#define startReverseDist               (10)      // distFront < startReverseDist --> reverseCount++
#define minReverseTime                 (100)
#define stopReverseDist                (40)      // distFront > stopReverseDist  --> fahrModus = Gerade

#define middleOffSet                   (0)       // cm * sqr(2) = verschiebung in cm nach links oder rechts

#define steeringDivisor                (2)       // distLeft - distRight /= lenkungDivisor;

#define MotorPowFactor                 (0.025)

#define speedIncrease                  (0.8)
#define MinDistAccel                   (100)
#define MinStraightSpeed               (200)

#define maxAddMPow                     (2)

#define oldSpeedDeltaDivisor           (2)

#define curveSpeed                     (150)
#define reverseSpeed                   (-150)

#define BrakeDistance                  (40)
#define BrakeDistanceStrong            (20)

#define MinMPower                      (50)                  
    
typedef enum{
    Straight,
    Brake,
    ReverseRight,
    ReverseLeft,   
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
uint8_t battCheckCount = 0;

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

void startAccel();

bool checkBatt();



#endif	/* XC_HEADER_TEMPLATE_H */

