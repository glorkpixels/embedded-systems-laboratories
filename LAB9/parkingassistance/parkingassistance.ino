//realtime clock istendiği için setupa
//parse ve variable ları atmayı ekledim
//bu sebeple değişik kısım videomda anlattığımdan sadece
//orası
#include <LiquidCrystal.h>


#define piezzoPin 6
const int pingPin = 7;
int hour =13;
int minute=59;
int second =56;

int day =8;
String month;
int year =2020;

int daypasser =1;
long distancer;


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(piezzoPin, OUTPUT);
  
  String myString = __TIME__;
  int commaIndex = myString.indexOf(':');
  int secondCommaIndex = myString.indexOf(':', commaIndex + 1);
  String firstValue = myString.substring(0, commaIndex);
  String secondValue = myString.substring(commaIndex + 1, secondCommaIndex);
  String thirdValue = myString.substring(secondCommaIndex + 1);
  
  int r = firstValue.toInt() ;
  int g = secondValue.toInt();
  int b = thirdValue.toInt();
  
  hour = r +3;
  minute = g;
  second = b;
  
  
  
  String dater = __DATE__;

  int emptyindex = dater.indexOf(' ');
  int secondemptyindex = dater.indexOf(' ', emptyindex + 1);
  String monthx = dater.substring(0, emptyindex);
  String dayx = dater.substring(emptyindex + 1, secondemptyindex);
  String yearx = dater.substring(secondemptyindex + 1);
  
  int x = dayx.toInt();
  int d = yearx.toInt();
  
  month = monthx;
  day=x;
  year=d;
    
}

void loop() {

  long duration, cm;


  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);


  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  distancer = cm;
  lcd.begin(16,2);
  
  
  Starter();
  second++;
  delay(1000);
  }



void Starter(){

  lcd.begin(16,2);
  
  if(day==30){
   day=1;
  }
  
  if(second > 59){
   second=0;
   minute=minute+1;
  }
  if(minute >59)
  {
   minute=0;
   hour=hour+1;
  }
  if(hour == 24)
  {
    day++;
   daypasser = daypasser+1;

    hour ==0;
   if (hour ==24) {
     hour=0;
   }


  }


  lcd.setCursor(0,0);
  lcd.print("Distance:");
  lcd.print(distancer);
  lcd.print("cm");

  Serial.print("DATE: " );
  if(day<10)Serial.print("0");// always 2 digits
  Serial.print(day);
  Serial.print(".");
  Serial.print(month);
  Serial.print(".");
  Serial.print(year);


  Serial.print("    HOUR: " );
  if((hour)<10)Serial.print("0");
  Serial.print(hour);
  Serial.print(":");
  if((minute)<10)Serial.print("0");
  Serial.print(minute);
  Serial.print(":");
  Serial.print(second );
  lcd.setCursor(0,1);// for Line 2
  

  if (distancer>100) {
    tone(piezzoPin, 1000, 30);
    lcd.print("  ITS FAR");
    Serial.print(" It is far.");
    Serial.println("\n ------------------------------------------");
  } else if (distancer >20) {
    tone(piezzoPin, 1000, 500);
    lcd.print(" ITS CLOSE!");
    Serial.print(" It is close.");
    Serial.println("\n ------------------------------------------");
  } else if(distancer>5){
    lcd.print(" TOO CLOSE");
    Serial.print(" It is too close.");
    Serial.println("\n ------------------------------------------");
    tone(piezzoPin, 1000, 1000);
  }
  else{
    lcd.print("  GG CRASH");
    Serial.print(" GG CRASH");
    Serial.println("\n ------------------------------------------");
  tone(piezzoPin, 500, 500);
    delay(200);
    tone(piezzoPin, 300, 300);
    delay(200);
     tone(piezzoPin, 200, 350);
    delay(200);
     tone(piezzoPin, 200, 400);
    delay(200);
     tone(piezzoPin, 225, 250);
    delay(200);
     tone(piezzoPin, 200, 888);
    delay(200);
    tone(piezzoPin, 700, 722);
    delay(200);
    tone(piezzoPin, 200, 100);
  }



}


long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
