#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

//all Distance Values are in[cm]
//all Time Values are in [10ms]
//all speed Values are in [unknown]

#define minBatValue                     (6.8)     // Mindestspg in Volt adc = (vbat * 409.6)
#define BattCheckPeriod                 (500)     


#define steeringFOffset                 (352)     // höher = links | niedriger = rechts
#define steeringBOffset                 (357)     // höher = links | niedriger = rechts
#define maxSteeringF                    (65)
#define maxSteeringB                    (40)
#define maxSteeringStraight             (25)      //kann beim geradeaus fahren nicht stärker lenken
#define steeringRatio                   (2)
#define steeringDivisor                 (1)       // distLeft - distRight /= lenkungDivisor;
//#define middleOffSet                    (0)       // cm * sqr(2) = verschiebung in cm nach links oder rechts

#define maxMPowForward                  (700)
#define maxSpeedForward                 (400)
#define defaultMotorPowerForward        (250)

#define maxMPowBackward                 (-400)
#define maxSpeedBackward                (-250)
#define defaultMotorPowerBackward       (-150)

#define maxAddMPow                      (5)
#define MotorPowFactor                  (0.020)
#define oldSpeedDeltaDivisor            (2)
#define MinMPower                       (40)

#define setDelayStart                   (20)       // Delay bevor man zu Lenken beginnt
#define setDelayEnd                     (25)      // Delay bevor man die Kurve abbrechen kann
#define setDelayNew                     (1)      // Delay bevor man eine neue Kurve erkennen kann   

#define startCurveDelta                 (30)      // ((oldDist - actDist) > startCurveDelta  \n
#define maxStartCurveDelta              (300)
#define MaxOldDist                      (125)     //  && oldDistLeft < MaxOldDist)  --> Kurv
#define endCurveDist                    (45)      // distL || distR < endKurveValue --> Kurvenende
#define endCurveDistFront               (150)     //distFront > endCurveDistFront   --> Kurvenende
#define curveSteering                   (60)       
#define curveSpeed                      (200)
#define switchCurveDelta                (30)

#define startReverseDist                (15)      // distFront < startReverseDist --> reverseCount++
#define minReverseTime                  (50)
#define stopReverseDist                 (35)      // distFront > stopReverseDist  --> fahrModus = Gerade
#define reverseSpeed                    (-125)
#define maxReverseTime                  (300)

#define speedIncrease                   (0.5)
#define MinDistAccel                    (150)
#define MinStraightSpeed                (275)


#define BrakeDistance                   (30)
#define BrakeDistanceStrong             (15)
#define minDriveSpeed                   (100)

#define startAccelTime                  (50)      //how long the function runs in total
#define startMPower                     (250)      //to what MPow the function accelerates
#define startAccellSteps                (20)       //in how many steps does the function accelerate to startMPower
#define startAccellStep       (int16_t) (startMPower / startAccellSteps)   //increment AcctMpow by this value
#define startAccelMult                  (1.1)
#define startAccellSteeringRatio        (2)

typedef enum {
    Accel,
    Straight,
    Brake,
    ReverseRight,
    ReverseLeft,
    CurveLeft,
    CurveRight
} DriveMode;

typedef enum {
    Inverted,
    Same,
    Ratio,
    Front,
    Back
} SteeringMode;

typedef enum {
    OutCurve,
    BeforeCurve,
    InCurve,
    AfterCurve
} CurveMode;

extern uint16_t distFront, distLeft, distRight;
extern int32_t smtWay; //1 increment == 2,7mm ;370 == 1m
extern uint32_t smtPeriod;

DriveMode driveMode = Straight;
CurveMode curveMode = OutCurve;

volatile uint8_t cycle10ms = 0;

uint8_t delay = 0;
uint16_t reverseCount = 0;
uint16_t oldDistLeft, oldDistRight;
uint16_t battCheckCount = 0;

// neg: naher and der linken Wand
int16_t  middleOffSet = 0;

int16_t motPow = 0;
int16_t setSpeed = 0;
int16_t currentSpeed = 0;
int16_t oldSpeed = 0;
int16_t actMotorPow = 0;
int16_t reverseTime = 0;

adc_result_t BatteryVolt = 0;


void TMR4_10msISR(void);

void loop(void);

int16_t actSpeed();
void startAccell();

void getCurve(void);
void getReverse(void);

void calcSteering(void);
void calcSpeed(void);
void calcMotorPow(void);

void setSteering(int16_t, SteeringMode);
void setMotor(int16_t);

#endif	/* XC_HEADER_TEMPLATE_H */