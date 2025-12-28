#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define trigPin 9
#define echoPin 10

LiquidCrystal_I2C lcd(0x27, 16, 2);

long sure;
float mesafe;
int threshold = 40;   // birim santimetre

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(4, 0);
  lcd.print("OTOPARK");
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  sure = pulseIn(echoPin, HIGH);

  mesafe = sure * 0.034 / 2;

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);

  lcd.print("M:");
  lcd.print(mesafe, 1);
  lcd.print("cm ");

  if (mesafe > 0 && mesafe < threshold) {
    lcd.print("DOLU ");
  } else {
    lcd.print("BOS  ");
  }

  // MATLAB'e veri gonderme
  Serial.println(mesafe);

  delay(1000);
}
