
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  



#define minBatValue                    (7.5)     // Mindestspg in Volt adc = (vbat * 409.6)
#define BattCheckPeriod                (100)     


#define steeringFOffset                (352)     // höher = links | niedriger = rechts
#define steeringBOffset                (357)     // höher = links | niedriger = rechts
#define maxSteeringF                   (65)
#define maxSteeringB                   (40)
#define maxSteeringStraight            (40)      //kann beim geradeaus fahren nicht mehr lenken
#define steeringRatio                  (2)
#define steeringDivisor                (1)       // distLeft - distRight /= lenkungDivisor;
#define middleOffSet                   (0)       // cm * sqr(2) = verschiebung in cm nach links oder rechts
#define curveSpeed                     (200)



#define maxMPowForward                 (600)
#define maxSpeedForward                (400)
#define defaultMotorPowerForward       (250)

#define maxMPowBackward                (-400)
#define maxSpeedBackward               (-250)
#define defaultMotorPowerBackward      (-150)

#define maxAddMPow                     (4)
#define MotorPowFactor                 (0.025)
#define oldSpeedDeltaDivisor           (2)
#define MinMPower                      (100) 

#define setDelayStart                  (20)       // Delay bevor man zu Lenken beginnt
#define setDelayEnd                    (25)      // Delay bevor man die Kurve abbrechen kann
#define setDelayNew                    (5)      // Delay bevor man eine neue Kurve erkennen kann

#define startCurveDelta                (40)      // ((oldDist - actDist) > startCurveDelta  \n
#define maxStartCurveDelta             (300)
#define MaxOldDist                     (150)     //  && oldDistLeft < MaxOldDist)  --> Kurv
#define endCurveDist                   (30)      // distF < endKurveValue --> Kurvenende
#define curveSteering                  (45)       


#define startReverseDist               (15)      // distFront < startReverseDist --> reverseCount++
#define minReverseTime                 (50)
#define stopReverseDist                (30)      // distFront > stopReverseDist  --> fahrModus = Gerade
#define reverseSpeed                   (-150)
#define maxReverseTime                 (200)
        

#define speedIncrease                  (0.75)
#define MinDistAccel                   (125)
#define MinStraightSpeed               (220)


#define BrakeDistance                  (40)
#define BrakeDistanceStrong            (20)
#define minDriveSpeed                  (125)

#define startAccelTime                 (25)
#define startMPower                    (250)

                 
    
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

volatile uint8_t cycle10ms = 0;

uint8_t delay = 0;
uint8_t reverseCount = 0;
uint16_t oldDistLeft, oldDistRight;
uint16_t battCheckCount = 0;

int16_t motPow = 0;
int16_t setSpeed = 0;
int16_t currentSpeed = 0;
int16_t oldSpeed = 0;
int16_t actMotorPow = 0;
int16_t reverseTime = 0;
int16_t tempCNT;

adc_result_t BatteryVolt = 0;



void TMR4_10msISR(void);

void loop(void);

bool checkBatt();       //returns true whenn BatVolt * 409.6 < minBatValue
int16_t actSpeed();
void startAccell();
void getBatteryVoltage(void);

void getCurve(void);
void getReverse(void);

void calcSteering(void);
void calcSpeed(void);
void calcMotorPow(void);

void setSteering(int16_t, SteeringMode);
void setMotor(int16_t);

                         



#endif	/* XC_HEADER_TEMPLATE_H */

