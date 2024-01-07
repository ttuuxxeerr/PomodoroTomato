#include "DS3231.h"

int a = 6;
int b = 10;
int c = A0;
int d = A2;
int e = A3;
int f = 7;
int g = 12;
int D1 = 5;
int D2 = 8;
int D3 = 9;
int D4 = 11;
int DP = A1;
int BUZZER1 = 2;
int BUZZER2 = 3;

int BUTTON = 4;

int RTC_SDA = A4;
int RTC_SCL = A5;
uint8_t sec_L = 0;
uint8_t sec_H = 0;

uint8_t min_L = 0;
uint8_t min_H = 0;

uint8_t hour_L = 0;
uint8_t hour_H = 0;

bool buttonPressed = false;
bool RTC_mode = false;
bool timer_mode = false;
bool sequence1 = true;
bool sequence2 = false;

uint8_t prevHour = 0;
uint8_t prevMin = 0;
uint8_t prevSec = 0;
// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

Time times;
void setup()
{
  // Initialize the rtc object
  rtc.begin();
  
  rtc.setTime(5, 6, 0);     // Set the time to 12:00:00 (24hr format) this has to be commented after the first initialitation
  pinMode(a, OUTPUT);                          // Pins for 7-segment
  pinMode(b, OUTPUT);     
  pinMode(c, OUTPUT);     
  pinMode(d, OUTPUT);     
  pinMode(e, OUTPUT);     
  pinMode(f, OUTPUT);        
  pinMode(g, OUTPUT);      
  pinMode(D1, OUTPUT);        
  pinMode(D2, OUTPUT);        
  pinMode(D3, OUTPUT);        
  pinMode(D4, OUTPUT);        
  pinMode(DP, OUTPUT);
  
  pinMode(BUZZER1, OUTPUT);                             // Pins for Buzzers
  pinMode(BUZZER2, OUTPUT);

  pinMode(BUTTON, INPUT);                              // Pin for Button

  digitalWrite(BUZZER1, LOW);
  digitalWrite(BUZZER2, LOW);

  times = rtc.getTime();
  prevHour = times.hour;
  prevMin  = times.min;
  prevSec  = times.sec;
}

void loop()
{
  if(digitalRead(BUTTON) == LOW){
    buttonPressed = !buttonPressed;
    delay(100);
  }
 
  times = rtc.getTime();
                                // print seconds
  if(buttonPressed == false){
    if(RTC_mode == false){
      rtc.setTime(prevHour, prevMin, prevSec); 
      timer_mode = false;
      RTC_mode = true;
    }
    modeRTC();
  }
  else if(buttonPressed == true){
   if(timer_mode == false){
    prevHour = times.hour;
    prevMin = times.min;
    prevSec = times.sec;
    rtc.setTime(0, 0, 0); 
    timer_mode = true;
    RTC_mode = false;
   }
   modeTimer(); 
  }
}

void modeTimer(){
  uint8_t Seconds = times.sec;
  sec_L = Seconds%10;
  sec_H = Seconds/10;
  digitTwo();
  printNum(sec_H);
  delay(1);
  digitOne();
  printNum(sec_L);
  delay(1);

  uint8_t Minutes = times.min;
  min_L = Minutes%10;
  min_H = Minutes/10;
  digitFour();
  printNum(min_H);
  delay(1);
  digitThree();
  printNum(min_L);
  delay(1);

  if(Minutes == 25 && sequence1 == true){
    rtc.setTime(0, 0, 0); 
    BuzzerBeep();
    sequence1 = false; 
    sequence2 = true;
  }
  else if(Minutes == 5 && sequence2 == true){
    rtc.setTime(0, 0, 0); 
    BuzzerBeep();
    sequence1 = true;    
    sequence2 = false;  
  }
  
  
  
}
void modeRTC(){
  uint8_t Minutes = times.min;
  min_L = Minutes%10;
  min_H = Minutes/10;
  digitTwo();
  printNum(min_H);
  delay(1);
  digitOne();
  printNum(min_L);
  delay(1);
  
  uint8_t Hours = times.hour;
  hour_L = Hours%10;
  hour_H = Hours/10;
  digitFour();
  printNum(hour_H);
  delay(1);
  digitThree();
  printNum(hour_L);
  delay(1);
}

void printNum(int value){

  switch(value){
    case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);              
      break;
    case 1:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);              
      break;
    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
   case 4:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
   case 5:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
  case 6:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
  case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
  case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
  case 9:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break; 
  }
  //delay(20);
}

void digitFour(void){
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);
      digitalWrite(DP, LOW);
 }
   
void digitThree(void){
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);
      digitalWrite(DP, HIGH);
 }
   
void digitTwo(void){
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      digitalWrite(D4, HIGH);
      digitalWrite(DP, LOW);
 }
   
void digitOne(void){
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      digitalWrite(DP, LOW);
 }

 void BuzzerBeep(void){
  digitalWrite(BUZZER1, HIGH);
  digitalWrite(BUZZER2, HIGH);
  delay(1000);
  digitalWrite(BUZZER1, LOW);
  digitalWrite(BUZZER2, LOW);  
 }
