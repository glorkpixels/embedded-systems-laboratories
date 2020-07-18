#define ButtonPin   8
#define Potentiometer  0
#define PWMSIGNAL1  9
#define PWMSIGNAL2  10

boolean Direction = 0;
int Speed;
int directionx = 0;


void setup() {
  Serial.begin(9600);
  pinMode(ButtonPin,INPUT_PULLUP);
  pinMode(PWMSIGNAL1,OUTPUT);
  pinMode(PWMSIGNAL2,OUTPUT);
}

void loop() {
  Speed = analogRead(Potentiometer) / 4;

  if (Direction)
    analogWrite(PWMSIGNAL1, Speed);
  else
    analogWrite(PWMSIGNAL2, Speed);

  if (digitalRead(ButtonPin)) {
    ButtonPinreverser();
  }
  delay(3000);
  reverser();
}

void ButtonPinreverser() {

  if (digitalRead(ButtonPin)) {

    while (digitalRead(ButtonPin)){
      //buttonpressedwaiting
    };

    Direction = !Direction;

  if (Direction)
      digitalWrite(PWMSIGNAL2, 0);
  else
      digitalWrite(PWMSIGNAL1, 0);

  }
  if (Direction)
    analogWrite(PWMSIGNAL1, Speed);
  else
    analogWrite(PWMSIGNAL2, Speed);

  Serial.println("ButtonPin pressed");
}

void reverser() {

  Direction = !Direction;
  if (Direction)
    digitalWrite(PWMSIGNAL2, 0);
  else
    digitalWrite(PWMSIGNAL1, 0);

  directionx++;
  Serial.println(directionx % 2);
}
