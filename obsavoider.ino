//servo motor
#include<Servo.h>
Servo servo;
int servoPin=11;
//ultrasonic sensor
int trig=4;
int echo=5;
int dis,disl,disr;
//motor driver
int a1=6;
int a2=7;
int b1=8;
int b2=9;

int ultrasonic();
void motor(bool,bool,bool,bool);

void setup()
{
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(a1,OUTPUT);
  pinMode(a2,OUTPUT);
  pinMode(b1,OUTPUT);
  pinMode(b2,OUTPUT);
}

void loop()
{
  //forward movement
  motor(HIGH,LOW,HIGH,LOW);
  //sensor
  dis=ultrasonic();
  //brake
  if(dis>=5)
  { //break
    motor(HIGH,HIGH,HIGH,HIGH);
    //check
    servo.write(0);
    disl=ultrasonic();
    servo.write(180);
    disr=ultrasonic();
    //backup
    motor(LOW,HIGH,LOW,HIGH);
    delay(1000);
    motor(HIGH,HIGH,HIGH,HIGH);
    if(disl>=disr)
    motor(LOW,HIGH,HIGH,LOW);
    else
    motor(HIGH,LOW,LOW,HIGH);
    delay(1000);
  } 
}

int ultrasonic()
{
  long dur;
  int distance;
  digitalWrite(trig,LOW);
  delay(2);
  digitalWrite(trig,HIGH);
  delay(10);
  digitalWrite(trig,LOW);
  dur=pulseIn(echo,HIGH);
  distance=dur*0.0343/2;//in cm
  return distance;
}

void motor(bool p1,bool p2,bool q1,bool q2)
{
    digitalWrite(a1,p1);
    digitalWrite(a2,p2);
    digitalWrite(b1,q1);
    digitalWrite(b2,q2);
}
