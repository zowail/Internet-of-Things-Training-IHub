#define E1 10
#define MA1 8
#define  MA2 7
#define E2 5
#define MB1 2
#define MB2 4
char input;
int speeds=225;
void Direction( int mA1, int mA2, int mB1, int mB2){
  digitalWrite(MA1,mA1);
  digitalWrite(MA2,mA2);
  digitalWrite(MB1,mB1);
  digitalWrite(MB2,mB2);
 
  delay(50);
}
  

void setup() {
  // put your setup code here, to run once:
pinMode(MA1,OUTPUT);
pinMode(MA2,OUTPUT);
pinMode(MB1,OUTPUT);
pinMode(MB2,OUTPUT);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available())
{
  
    input=Serial.read();
    if (input=='F')
    {
      
      Direction(HIGH,LOW,HIGH,LOW);
      analogWrite(E1,speeds);
      analogWrite(E2,speeds);
      
    }
      
   else  if (input=='r')
    {
     Direction(HIGH,LOW,LOW,HIGH);
      analogWrite(E1,speeds);
      analogWrite(E2,(speeds*1/2));
    
    }
     else if (input=='l')
    {
      Direction(LOW,HIGH,HIGH,LOW);
      analogWrite(E1,(speeds*1/2));
      analogWrite(E2,speeds);
     
    } 
    else  if (input=='b')
    {
    Direction(LOW,HIGH,LOW,HIGH);
      analogWrite(E1,speeds);
      analogWrite(E2,speeds);
    }
  
else  if (input=='q')
    {
      Direction(HIGH,HIGH,HIGH,HIGH);     
      
}
}}
