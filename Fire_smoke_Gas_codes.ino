#include <SoftwareSerial.h>
 SoftwareSerial mySerial(9,10);
 const int buzzerPin = 8;
const int fireSensorPin = 7; 
const int smokeA0= A5;
const int gasValue=A0; 
int sensorThres = 500;
int data = 0;
void setup()
{
randomSeed(analogRead(0));
mySerial.begin(9600); 
Serial.begin(9600); 
pinMode(buzzerPin, OUTPUT);
pinMode(fireSensorPin, INPUT);
pinMode(smokeA0, INPUT);
pinMode(gasValue,INPUT);
delay(3000);
}
void loop(){
  fire();
  smoke();
  gas();
}
void fire()
{
int fireValue = digitalRead(fireSensorPin);
if ( fireValue == 0) //
{
SendMessage();
Serial.print("Fire detect alarm");
digitalWrite(buzzerPin, HIGH);
delay(5000);
delay(1000);
 }
else
{
Serial.print("\n Fire Level Low \n");
Serial.println(fireValue);
digitalWrite(buzzerPin, LOW);
delay(1000);
}
 delay(500);
}
void smoke()
{
int analogSensor = analogRead(smokeA0);
Serial.println(analogSensor);
if ( analogSensor > sensorThres ) //
{
SendMessage1();
Serial.print("smoke detect alarm");
digitalWrite(buzzerPin, HIGH);
delay(5000);
delay(1000);
 }
else
{
Serial.print("\n smoke Level Low");
Serial.println(analogSensor);
digitalWrite(buzzerPin, LOW);
delay(1000);
}
 delay(500);
}
void gas(){
data = analogRead(gasValue);
if ( data > 200) //
{
SendMessage2();
Serial.print("Gas detect alarm");
delay(1000);
 }
else
{
Serial.print("Gas Level Normal");
delay(1000);
}
}
void SendMessage()
{
Serial.println("I am in send");
mySerial.println("AT+CMGF=1"); 
delay(1000); 
mySerial.println("AT+CMGS=\"+919594028027\"\r"); 
delay(1000);
mySerial.println("fire Detected. Open Windows");
delay(100);
mySerial.println((char)26);
delay(1000);
}
void SendMessage1()
{
Serial.println("I am in send");
mySerial.println("AT+CMGF=1"); 
delay(1000); 
mySerial.println("AT+CMGS=\"+919594028027\"\r"); 
delay(1000);
mySerial.println("smoke Detected. Open Windows");
delay(100);
mySerial.println((char)26);
delay(1000);
}
void SendMessage2()
{
Serial.println("I am in send");
mySerial.println("AT+CMGF=1"); 
delay(1000); 
mySerial.println("AT+CMGS=\"+919594028027\"\r"); 
delay(1000);
mySerial.println("Gas Detected. Open Windows");
delay(100);
mySerial.println((char)26);
delay(1000);
}
