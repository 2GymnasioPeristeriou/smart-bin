#include <AccelStepper.h>
#include <MultiStepper.h>

#include<Servo.h>
#include <AccelStepper.h>
Servo flap;
#define trigPin 7
#define echoPin 6
int rain_pin = 3;
int inductive_pin = 4;
int flap_pin = 5;
const int buzzer = 12;
int homing_pin=13;
int homing;
int rain;
int inductive;
int sound = 250;
int i;
#define FULLSTEP 4
AccelStepper myStepper(FULLSTEP,8,10,9,11);
void setup() 
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(rain_pin,INPUT);
  pinMode(inductive_pin,INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(homing_pin,INPUT);
  flap.attach(flap_pin);
  homing=digitalRead(homing_pin);
  myStepper.setMaxSpeed(1000.0);
  myStepper.setAcceleration(100.0);
  myStepper.setSpeed(1000);
   for(i=0;homing==LOW;i++){
  myStepper.moveTo(i);
  myStepper.runToPosition();
    homing=digitalRead(homing_pin);
    }
  myStepper.moveTo(i-2);
 myStepper.runToPosition();
  myStepper.setCurrentPosition(0);
 
}

void loop() {
  long duration, distance;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
Serial.println(distance);
inductive=digitalRead(inductive_pin);
rain=digitalRead(rain_pin);
Serial.println(rain);
if(inductive==HIGH)//metallic waste
{
  tone(buzzer, 1000); 
  delay(300);       
  noTone(buzzer);
  delay(300);
  tone(buzzer, 1000); 
  delay(300);       
  noTone(buzzer);  
  myStepper.moveTo(982);
  myStepper.runToPosition();
 delay(2000);
  flap.write(179);
  delay(1500);
  flap.write(0);
  delay(500);
  myStepper.moveTo(0);
  myStepper.runToPosition();
}
if(rain==LOW)//wet waste
{
  tone(buzzer, 1000); 
  delay(300);       
  noTone(buzzer);
  delay(300);
  tone(buzzer, 1000); 
  delay(300);       
  noTone(buzzer);
  delay(300);
  tone(buzzer, 1000); 
  delay(300);       
  noTone(buzzer);
  myStepper.moveTo(1485);
  myStepper.runToPosition();
 delay(2000);
  flap.write(179);
  delay(1500);
  flap.write(0);
  delay(500);
  myStepper.moveTo(0);
  myStepper.runToPosition();
}
if(distance <=8)//dry waste
{
     
//delay(500);
if(rain==HIGH);
{
if(inductive==LOW);

{
  tone(buzzer, 1000); 
  delay(500);       
  noTone(buzzer);     
  myStepper.moveTo(510);
  myStepper.runToPosition();
 delay(2000);
  flap.write(179);
  delay(1500);
  flap.write(0);
  delay(500);
  myStepper.moveTo(0);
  myStepper.runToPosition();
}}}
if(distance>=9&&inductive==LOW&&rain==HIGH) //No waste
{
 myStepper.moveTo(0);
 myStepper.runToPosition();
  flap.write(0);
}
delay(4000);
}
 
 
