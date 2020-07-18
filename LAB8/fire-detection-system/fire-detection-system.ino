#include <LiquidCrystal.h>

int SCREEN_TIME_SENSOR = 5;

int SCREEN_TIME_HEAT_INDEX  = 4;
int bufferd;
int bufferi;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define PIN_GAS A2
#define PIN_TMP A1
#define PIN_RES A0


#define SENSOR_LIGHT_VERY_DARK 807
#define SENSOR_LIGHT_DARK 920
#define SENSOR_LIGHT_BRIGHT 957


#define SENSOR_GAS_MAX 20
#define SENSOR_GAS_MID 50
#define SENSOR_GAS_MIN 80



#define SENSOR_TMP_MIN 37
#define SENSOR_TMP_MID 60
#define SENSOR_TMP_MAX 80




int lightvalue = 0;
int gasvalue = 0;
int tmpvalue = 0;
float tmpCel = 0;
float tmpFer = 0;
void setup() {
  lcd.begin(16, 2);
  bufferd = SCREEN_TIME_SENSOR;
  bufferi = SCREEN_TIME_HEAT_INDEX;

  pinMode(PIN_GAS, INPUT);
  pinMode(PIN_RES, INPUT);
  pinMode(PIN_TMP, INPUT);
}



void loop() {
  lcd.begin(16, 2);
  int temp = SCREEN_TIME_SENSOR + SCREEN_TIME_HEAT_INDEX;
  gasvalue = map(analogRead(PIN_GAS), 300, 750, 0, 100);
  lightvalue = analogRead(PIN_RES);
  tmpvalue = analogRead(PIN_TMP);
  float voltage = (tmpvalue * 5.0) / 1024;
  float milliVolt = voltage * 1000;
  tmpCel =  (milliVolt - 500) / 10;
  tmpFer = (((tmpCel * 9) / 5) + 32);

  if (temp > SCREEN_TIME_HEAT_INDEX) {
    Normal();
    SCREEN_TIME_SENSOR--;
  }
  else if (temp > 0 ) {
    Fire();
    SCREEN_TIME_HEAT_INDEX --;
  }
  if (SCREEN_TIME_HEAT_INDEX == 0 && SCREEN_TIME_SENSOR == 0 ) {
    SCREEN_TIME_HEAT_INDEX = bufferi;
    SCREEN_TIME_SENSOR = bufferd;
  }
  delay(1000);
}

void Normal() {

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(tmpCel);
  lcd.print("C|");

  lcd.print(tmpFer);
  lcd.print("F");
  lcd.setCursor(0, 1); // for Line 2

  lcd.print("GS= ");
  lcd.print(gasvalue);
  lcd.print(" || LS=");
  lcd.print(lightvalue);


}

void Fire() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  int cel = tmpCel;
  int var;
  if (cel > SENSOR_TMP_MAX ) {
    if ( gasvalue < SENSOR_GAS_MAX) {
      if (lightvalue < SENSOR_LIGHT_VERY_DARK) {
        /* itstf4tf5 */
        var = 1;

      }
      else {
        /* its tf1 */
        var = 2;
      }
    }
    else {
      /* tf6 */
      var = 3;
    }
  }
  else if (cel < SENSOR_TMP_MIN) {
    if ( gasvalue < SENSOR_GAS_MAX) {
      if (lightvalue < SENSOR_LIGHT_VERY_DARK) {
        /* its tf8 */
        var = 4;
      }
      else if (lightvalue > SENSOR_LIGHT_DARK) {
        /* its tf2-3 */
        var = 5;
      }
    }
    else{
      var=6;
    }
  }
  else {
    var = 6;
  }


  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  switch (var) {
    case 1:
      //do something when var equals 1
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print("FIRE TF4&TF5");
      lcd.setCursor(0, 1); // for Line 2
      lcd.print("N-HEP OR POLYTHNE");

      break;
    case 2:
      //do something when var equals 2
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print("TF1 WOOD FIRE");

      lcd.setCursor(0, 1); // for Line 2
      lcd.print("CELLULOSE OPEN");


      break;
    case 3:
      //do something when var equals 2

      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print("TF6 FIRE ETHANOL ");
      lcd.setCursor(0, 1); // for Line 2
      lcd.print("LIQUID FIRE");
      break;
    case 4:
      //do something when var equals 2
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print("TF8 FIRE DECALINE ");
      lcd.setCursor(0, 1);
      lcd.print("LIQUID FIRE");
      break;
    case 5:
      //do something when var equals 2

      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print("FIRE TF2 or T3");
      lcd.setCursor(0, 1); // for Line 2
      lcd.print("     WOOD OR COTTON  ");
      break;
    case 6:
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print("NO FIRE I REPEAT");
      lcd.setCursor(0, 1); // for Line 2
      lcd.print("     NO FIRE  ");
      //do something when var equals 2
      break;

  }

}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
