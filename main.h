/* 
 * File:   main.h
 * Author: Simon
 *
 * Created on January 20, 2024, 10:06 PM
 */

#ifndef MAIN_H
#define	MAIN_H

    // höher = links | niedriger = rechts
#define LenkungVOffset (352)
// höher = links | niedriger = rechts
#define LenkungHOffset (357)
#define MaxV (65)
#define MaxH (45)
#define LenkungsVerhaeltnis (3)
#define MinBattValue (7.4 * 409.6)          //adc = (vbat /2) * (4096 /5) -->2800 = 3,4V (leer)

#define maxMPowForward (600)
#define maxSpeedForward (400)
#define defaultMotorPowerForward (250)

#define maxMPowBackward (-300)
#define maxSpeedBackward (-250)
#define defaultMotorPowerBackward (-100)

#define setDelayStart (5)                   //Delay bevor man zu Lenken beginnt
#define setDelayEnd (20)                    //Delay bevor man die Kurve abbrechen kann
#define setDelayNew (20)                    //Delay bevor man eine neue Kurve erkennen kann

#define startKurveDelta 50                  //(oldDist - actDist) > startKurveDelta --> Kurve

#define endKurveValue 40                    //dist < endKurveValue --> Kurvenende

#define startReverseDist 10                 //distFront < startReverseDist --> reverseCount++
#define minReverseTime 25                   //
#define stopReverseDist 40                  //distFront > stopReverseDist  --> fahrModus = Gerade;

#define middleOffSet (int8_t)(0 * 1.4142135)// cm * sqr(2) = verschiebung in cm nach links oder rechts

#define lenkungDivisor 2                    //distLeft - distRight /= lenkungDivisor;

#define MotorPowFactor 0.05


#define speedSteigung 0.8
#define speedOffset 150


#define maxAddMPow 3

#define oldSpeedDeltaDivisor 1

#define kurvenSpeed 150
#define reverseSpeed (-150)
    

typedef enum{
    Gerade,
    Bremsen,
    Ruckwarts,
    KurveLinks,
    KurveRight
}FahrModus;

typedef enum{
    Invertiert,
    Gleich,
    Verhaeltnis,
    Vorne,
    Hinten
}LenkungsModus;

typedef enum{
    AusKurve,
    VorKurve,
    InKurve,
    NachKurve
} KurvenModus;



extern uint16_t distFront, distLeft, distRight;
extern int32_t smtWay;      //1 increment == 2,7mm ;370 == 1m
extern uint32_t smtPeriod;

FahrModus fahrModus = Gerade;
KurvenModus kurvenModus = AusKurve;

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


void loop(void);
void TMR4_10msISR(void);
void getBatteryVoltage(void);
void getKurve(void);
void getReverse(void);
void calcLenkung(void);
void setLenkung(int16_t, LenkungsModus);
void calcSpeed(void);
void calcMotorPow(void);
void setMotor(int16_t);

int16_t actSpeed();


#endif	/* MAIN_H */

