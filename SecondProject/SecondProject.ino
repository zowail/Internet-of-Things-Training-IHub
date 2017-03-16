#define E1 13
#define MA1 12
#define  MA2 8
#define E2 6
#define MB1 7
#define MB2 4
#define E3 5
#define MC1 3
#define MC2 2
#define trigger_pin 0
#define echo_pin 1
#define led 13
char input;
int speeds=225;
void Direction( int mA1, int mA2, int mB1, int mB2){
  digitalWrite(MA1,mA1);
  digitalWrite(MA2,mA2);
  digitalWrite(MB1,mB1);
  digitalWrite(MB2,mB2);
 
  delay(50);
}
  long ultrasonic ()
  {
    long duration,distance;
  digitalWrite(trigger_pin,LOW);
delayMicroseconds(2);
digitalWrite(trigger_pin,HIGH);
delayMicroseconds(10);
digitalWrite(trigger_pin,LOW);
duration=pulseIn(echo_pin,HIGH);
distance=(duration/2)/29.1;
  delay(500);
  return distance;
    }

void setup() {
  // put your setup code here, to run once:
pinMode(MA1,OUTPUT);
pinMode(MA2,OUTPUT);
pinMode(MB1,OUTPUT);
pinMode(MB2,OUTPUT);
pinMode(trigger_pin, OUTPUT);
pinMode(echo_pin,INPUT);
pinMode(8,OUTPUT);
//Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly: 
      digitalWrite(MA1,LOW);//forward SWEEPER
      digitalWrite(MA2,HIGH);
      digitalWrite(E3,HIGH);
      
   int val;
val=analogRead(0);
if(val>10)
{
   tone(8,1000);

    delay(500);

    noTone(8);

    delay(500);

}
//Serial.println(val,DEC);
delay(100);
      Direction(HIGH,LOW,HIGH,LOW);//forward
      analogWrite(E1,speeds);
      analogWrite(E2,speeds);
      if(ultrasonic()==10){
         digitalWrite(led,HIGH);
        delay(50);
        digitalWrite(led,LOW);
     for(int i=0;i<2;i++){
      Direction(HIGH,LOW,LOW,HIGH);//right   
      analogWrite(E1,speeds);
      analogWrite(E2,(speeds*1/2));}
      }
    
 Direction(HIGH,LOW,HIGH,LOW);//forward
      analogWrite(E1,speeds);
      analogWrite(E2,speeds);
      if(ultrasonic()==10){
        digitalWrite(led,HIGH);
        delay(50);
        digitalWrite(led,LOW);
     for(int i=0;i<2;i++){
     Direction(LOW,HIGH,HIGH,LOW);//left
      analogWrite(E1,(speeds*1/2));
      analogWrite(E2,speeds);
      }
    
      
     
    
    
      
   /* else  if (input=='b')
    {
    Direction(LOW,HIGH,LOW,HIGH);
      analogWrite(E1,speeds);
      analogWrite(E2,speeds);
    }*/
  
/*else  if (input=='q')
    {
      Direction(HIGH,HIGH,HIGH,HIGH);     
      
}*/
}}
