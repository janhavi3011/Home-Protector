 #include <Keypad.h>
#include<LiquidCrystal.h> 
#include<Servo.h>
//#include<String.h>
#define buzzer 8
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
char keys[4][3]={ 
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}};
 byte rowPin[4]={1,2,3,4}; 
byte colPin[4]={5,6,7};
Servo servo_Motor; 
String password = "159";  
int position = 0;
int wrong = 0; 
 Keypad keypad=Keypad(makeKeymap(keys),rowPin,colPin,4,3);

int total = 0; 
void setup()
{ 
lcd.begin(16,2);
lcd.print("DOOR LOCK SYSTEM");
lcd.setCursor(0,2);
lcd.print("       WELCOME TO:");
delay(2000);
lcd.clear();
lcd.print("HOME");
lcd.setCursor(0,2);
lcd.print("    PROTECTOR");
delay(2000);
lcd.clear();
servo_Motor.attach(9);
setLocked(true);
delay(1000);
pinMode(buzzer, OUTPUT);
}
void loop()
{
   lcd.clear();
  lcd.print("Enter Password:");
  delay(100);
char pressed=keypad.getKey();
 String key[3];
   if(pressed) 
 {
  lcd.clear();
  lcd.print("Enter Password:");
  lcd.setCursor(position,2);
  lcd.print(pressed);
  delay(500);
    if(pressed == '*' || pressed == '#')
      {
          position = 0;
          setLocked(true);
          lcd.clear();
      }
  else if(pressed == password[position])
      {
          key[position]=pressed;
          position++;
      }
    else if (pressed != password[position] )
      {
          wrong++;
          position ++;
      }
    if(position == 3)
      {
          if( wrong >0) 
            {
                total++;
                wrong = 0;
                position = 0;
                lcd.clear();
                lcd.print("WRONG");
                lcd.setCursor(5,2);
                lcd.print("PASSWORD");
                delay(1000);
                setLocked(true);
            }
          else if(position == 3 && wrong == 0)
            {
                position = 0;
                wrong = 0;
                lcd.clear();
                lcd.print("PASSWORD");
                lcd.setCursor(6,2);
                lcd.print("ACCEPTED");
                delay(2000);
                lcd.clear();
                lcd.print("Door Open");
                delay(2000);
                setLocked(false);
            }
        if(total ==3)
            {
                total=0;
                buzzer_beep();
  digitalWrite(buzzer, HIGH);
                delay(100);
            }
        }
   } 
}
void setLocked(int locked)
  {
    if (locked)
      {
          delay(1000);
          servo_Motor.attach(9);
          servo_Motor.write(180);
          delay(1000);
          servo_Motor.detach();
      }
    else
      {
          delay(1000);
          servo_Motor.attach(9);
          servo_Motor.write(90);
          delay(1000);
          servo_Motor.detach();
      }
  }
void buzzer_beep()
{
   digitalWrite(buzzer,HIGH);
   delay(1000);
   digitalWrite(buzzer,HIGH);
   delay(1000);
   lcd.clear();
   lcd.setCursor(16,0);
   lcd.print("GET");
   lcd.setCursor(16,1);
   lcd.print("AWAY");
   delay(2000);
   while(1)
   {
    digitalWrite(buzzer,HIGH);
    delay(1000);
   lcd.scrollDisplayLeft();
   delay(200);
   }
}
