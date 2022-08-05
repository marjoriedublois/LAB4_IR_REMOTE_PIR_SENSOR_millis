/*

LABORATORY 4: Automatic Door Disinfecting System
CODED BY: Marjorie Dublois and Czarlean Grace Najito

The goal of this program is to spray disinfectant when motion is
detected by the PIR sensor.

INSTRUCTIONS:
- Upon clicking the Start Simulation button, the lcd will present
greetings and introduce itself to the user as well as the LED will
turn green which indicates that the system is on.

- After the loading message and the LCD is clear you can now
adjust the PIR sensor and while there is motion detected the 
door(servo) will close and the dc motor(disinfectant spray) will
start working and for the LED it will turn into yellow indictating
that the disinfection is ongoing

-By clicking the power off button in the IR remote the system will
turn off and the LED will turn into red.

-NOTE: If you want to use again the circuit you must click the
"START SIMULATION" again to turn on the system.

*/


#include <LiquidCrystal_I2C.h>
#include<Wire.h>
#include<Servo.h>
#include<IRremote.h>
LiquidCrystal_I2C lcd(32,16,2);
Servo myServo;


//Setting up pins
int rLED=9;
int bLED=6;
int gLED=3;
int IRpin=5;
int pirPin=12;
int pirVal; //value from sensor detection
int servoPin=11;
int dcMotor=8;  //disinfectant spray
IRrecv IR(IRpin);  //door
//init servPos=0;


//variables
bool repeat = true;
bool arepeat = true;
bool brepeat = true;
int i;

//time delay
int t1=500;
int t2=1000;
int t3=1500;


//msg 
String msg1="";
String msg2="";
String msg3="";

//millis 
unsigned long fromStartms;//millis from start
unsigned long prevms;//millis prev read
unsigned long interval=1000;

void setup()
{
lcd.begin(16,2);
lcd.init();
lcd.backlight();
pinMode(rLED,OUTPUT);
pinMode(bLED,OUTPUT);
pinMode(gLED,OUTPUT);
pinMode(dcMotor,OUTPUT); 
pinMode(IRpin,INPUT);
pinMode(pirPin,INPUT);
myServo.attach(servoPin);  
Serial.begin(9600);  
IR.enableIRIn();
  
  
}

void loop()
{  
if (repeat == true)
{  
digitalWrite(gLED,HIGH);   // indicator when system is on
lcd.setCursor(5,0);
lcd.print("HELLO");
lcd.setCursor(4,1);
lcd.print("WELCOME");
delay(t2);
lcd.clear();
  
lcd.setCursor(2,0);
lcd.print("To The World");
lcd.setCursor(3,1);
lcd.print("OF ARDUINO!");
delay(t3);
lcd.clear();
  
lcd.setCursor(5,0);
lcd.print("MY NAME ");
lcd.setCursor(7,1);
lcd.print("IS");
delay(t3);
lcd.clear();
  
lcd.setCursor(0,0);
lcd.print("AUTOMATIC  DOOR");
lcd.setCursor(1,1);
lcd.print("DISINFEFCTING");
delay(t3);
lcd.clear();  
  
  
lcd.setCursor(5,0);
lcd.print("CHAMBER");
lcd.setCursor(6,1);
lcd.print("LMAO");
delay(t3);
lcd.clear(); 
} 
repeat = false;  

if( arepeat == true)
{  
lcd.setCursor(0,0); 
lcd.print("LOADING...");
lcd.setCursor(0,1);
lcd.print("baking cookies");
delay(t1);
lcd.clear();
}

arepeat = false;  
  
fromStartms=millis();
pirVal=digitalRead(pirPin);
if(fromStartms - prevms >= interval)

{

prevms = fromStartms;

if(pirVal==1)
{

digitalWrite(dcMotor,HIGH);
myServo.write(90); 
digitalWrite(gLED,80);  // indicator when there is motion inside
digitalWrite(rLED,255);  // and when the disinfection is ongoing
digitalWrite(bLED,0);
//delay(t2);
lcd.setCursor(0,0);
lcd.print("PLS SPIN FOR US");
delay(t2);

}  
}
else
{

digitalWrite(dcMotor,LOW);    
myServo.write(20);
digitalWrite(gLED,HIGH);
digitalWrite(rLED,LOW);
lcd.clear();

}

Serial.println(pirVal);
  
while(IR.decode())
{
//POWER OFF BUTTON
 if(IR.decodedIRData.decodedRawData==0xFF00BF00)
 {
  lcd.clear();
  digitalWrite(rLED,HIGH);
  digitalWrite(gLED,LOW);
  digitalWrite(bLED,LOW);
 }
  
delay(t3);
//IR.resume();   
}   
} 
  
  
  
