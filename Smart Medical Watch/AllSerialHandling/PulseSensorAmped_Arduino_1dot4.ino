
/*  Pulse Sensor Amped 1.4    by Joel Murphy and Yury Gitman   http://www.pulsesensor.com

----------------------  Notes ----------------------  ---------------------- 
This code:
1) Blinks an LED to User's Live Heartbeat   PIN 13
2) Fades an LED to User's Live HeartBeat
3) Determines BPM
4) Prints All of the Above to Serial

Read Me:
https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/README.md   
 ----------------------       ----------------------  ----------------------
*/
//#include "I2Cdev.h"
//#include "MPU6050_6Axis_MotionApps20.h"
//#include "Wire.h"
#include <math.h>
#define READING_PIN 1
//  Variables
//MPU6050 mpu;
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin

// Volatile Variables, used in the interrupt service routine!
volatile float BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = true;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse 

// temp 


double R1 = 10000.0; //resistance put in parallel
double V_IN = 5.0;

double A = 1.129148e-3;
double B = 2.34125e-4;
double C = 8.76741e-8;
double K = 9.5; // mW/dec C – dissipation factor

double SteinhartHart(double R)
{
// calculate temperature
double logR  = log(R);
double logR3 = logR * logR * logR;

return 1.0 / (A + B * logR + C * logR3 );

}

void setup(){
 
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
  Serial.begin(9600);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
   // UN-COMMENT THE NEXT LINE IF YOU ARE POWERING The Pulse Sensor AT LOW VOLTAGE, 
   // AND APPLY THAT VOLTAGE TO THE A-REF PIN
//   analogReference(EXTERNAL);   
}


//  Where the Magic Happens
void loop(){
     
    serialOutput() ;       
    
  if (QS == true){     //  A Heartbeat Was Found
                       // BPM and IBI have been Determined
                       // Quantified Self "QS" true when arduino finds a heartbeat
        digitalWrite(blinkPin,HIGH);     // Blink LED, we got a beat. 
        fadeRate = 255;         // Makes the LED Fade Effect Happen
                                // Set 'fadeRate' Variable to 255 to fade LED with pulse
        serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.     
        QS = false;                      // reset the Quantified Self flag for next time    
       } 
      else { 

      digitalWrite(blinkPin,LOW);            // There is not beat, turn off pin 13 LED
      }
     
   ledFadeToBeat();                      // Makes the LED Fade Effect Happen 
  //delay(500);                             //  take a break
  // temp 
  
  double adc_raw = analogRead(READING_PIN);
//Serial.println(adc_raw);
double V =  adc_raw / 1024 * V_IN;
Serial.print("V =");
Serial.print(V);

//calculate resistance
double Rth = ((R1 * V ) / (V_IN - V));
Serial.print("V   R_th = ");
Serial.print(Rth);

double kelvin = (SteinhartHart(Rth) - ((V*V)/(K * Rth)));
double celsius = kelvin - 273.15;
Serial.print("Ohm  —   T = ");
Serial.print(celsius/2);
Serial.print("C\n");
delay(500);
}









