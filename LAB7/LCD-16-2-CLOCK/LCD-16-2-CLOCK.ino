
#include <LiquidCrystal.h>

int SCREEN_DEFAULT_TIME = 5;
int SCREEN_INFO_TIME  = 2;

int bufferd;
int bufferi;

int hour =23;
int minute=59;
int second =56;

int day =8;
int month=4;
int year =2020;


int daypointer =2;
int daypasser =1;
int buttonState = 0;

char DaysEng [7] [7] = {
 { "MON" },
 { "TUE" },
 { "WED" },
 { "THU" },
 { "FRI" },
 { "SAT" },
 { "SUN" },
 };

 char DaysTr [7] [7] = {
  { "PZT" },
  { "SAL" },
  { "CAR" },
  { "PER" },
  { "CUM" },
  { "CTS" },
  { "PZR" },
  };

boolean  AMPMHolder = true; // true pm false am
boolean  LangSwitcher = true; // tr and eng swticherooooooooo true eng  false tr
int buttonPin = 8;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);


  bufferd = SCREEN_DEFAULT_TIME;
  bufferi= SCREEN_INFO_TIME;
}

void loop() {


  lcd.begin(16,2);


   buttonState = digitalRead(8);
    if (buttonState == HIGH) {
       LangSwitcher = !LangSwitcher;
       SCREEN_INFO_TIME = bufferi;
      SCREEN_DEFAULT_TIME= bufferd;
    }


    if (LangSwitcher == true) {
     int temp = SCREEN_DEFAULT_TIME + SCREEN_INFO_TIME;
      if (temp > SCREEN_INFO_TIME) {
        English();
    SCREEN_DEFAULT_TIME--;
      }
      else if (temp> 0 ) {
        EnglishInfo();
        SCREEN_INFO_TIME --;
      }

    }
    else if (LangSwitcher == false) {

      int temp = SCREEN_DEFAULT_TIME + SCREEN_INFO_TIME;
       if (temp > bufferi) {
         Turkish();
          SCREEN_DEFAULT_TIME--;
       }
       else if (temp>0 ) {
         TurkishInfo();
         SCREEN_INFO_TIME --;
       }
    }



    if (SCREEN_INFO_TIME == 0 && SCREEN_DEFAULT_TIME ==0 ) {
      SCREEN_INFO_TIME = bufferi;
      SCREEN_DEFAULT_TIME= bufferd;
    }


  while (buttonState == HIGH) {
                   buttonState = digitalRead(buttonPin);
                   delay(50);
                 }
   second++;
   delay(1000);
}



void English(){

  lcd.begin(16,2);
  if(day==30){
   day=1;
   month=month+1;
  }
  if(month==12)
  {
   month=1;
   year=year+1;
  }
  if(year==year+1)
  {
   year= year+1;
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
    if (hour / 12 ==0) {
     AMPMHolder= true;
    }
    else{
      AMPMHolder = false;
    }

    hour ==0;
   if (hour ==24) {
     hour=0;
     daypointer++;
     if (daypointer==7) {
      daypointer =0;
     }
   }




  }


  lcd.setCursor(0,0);
  if((hour%12)<10)lcd.print("0");// always 2 digits
  lcd.print(hour %12);
  lcd.print(":");
  if(minute<10)lcd.print("0");
  lcd.print(minute);
  lcd.print(":");
  if(second<10)lcd.print("0");
  lcd.print(second);

  if(AMPMHolder) lcd.print(" PM");
  else lcd.print(" AM");

  lcd.print("  ENG");

  lcd.setCursor(0,1);// for Line 2

  if(day<10)lcd.print("0");// always 2 digits
  lcd.print(day);
  lcd.print(".");
  if(month<10)lcd.print("0");
  lcd.print(month);
  lcd.print(".");

  lcd.print(year);


  lcd.print("   ");
  lcd.print(DaysEng[daypointer]);

}


void EnglishInfo(){
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("HH");
  lcd.print(":");
  lcd.print("MM");
  lcd.print(":");
  lcd.print("SS");

  lcd.print(" 12H ENG");

  lcd.setCursor(0,1);// for Line 2

  lcd.print("DD");
  lcd.print(".");
  lcd.print("MM");
  lcd.print(".");

  lcd.print("YY");


  lcd.print("   ");
  lcd.print("  DOW");

}

void TurkishInfo(){
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("HH");
  lcd.print(":");
  lcd.print("MM");
  lcd.print(":");
  lcd.print("SS");

  lcd.print(" 24H TUR");

  lcd.setCursor(0,1);// for Line 2

  lcd.print("DD");
  lcd.print(".");
  lcd.print("MM");
  lcd.print(".");

  lcd.print("YY");


  lcd.print("   ");
  lcd.print("  DOW");

}


void Turkish(){
    lcd.begin(16,2);
    if(day==30){
     day=1;
     month=month+1;
    }
    if(month==12)
    {
     month=1;
     year=year+1;
    }
    if(year==year+1)
    {
     year= year+1;
    }


    if(second>59){
     second=0;
     minute=minute+1;
    }
    if(minute>59)
    {
     minute=0;
     hour=hour+1;
    }
    if(hour == 24)
    {
     hour=0;
      
     day++;
     daypasser = daypasser+1;
     if (daypasser >1) {
       daypasser =0;
       daypointer++;
       if (daypointer==7) {
        daypointer =0;
       }
     }
     AMPMHolder= !AMPMHolder;
    }


    lcd.setCursor(0,0);
    if(hour<10)lcd.print("0");// always 2 digits
    lcd.print(hour);
    lcd.print(":");
    if(minute<10)lcd.print("0");
    lcd.print(minute);
    lcd.print(":");
    if(second<10)lcd.print("0");
    lcd.print(second);

    lcd.print("     TUR");

    lcd.setCursor(0,1);// for Line 2

    if(day<10)lcd.print("0");// always 2 digits
    lcd.print(day);
    lcd.print(".");
    if(month<10)lcd.print("0");
    lcd.print(month);
    lcd.print(".");

    lcd.print(year);


    lcd.print("   ");
    lcd.print(DaysTr[daypointer]);



}
