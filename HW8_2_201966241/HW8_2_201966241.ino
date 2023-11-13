#include <LiquidCrystal.h>

// LCD 핀 설정
LiquidCrystal lcd(44, 45, 46, 47, 48, 49);

// LM35 온도센서 및 CDS 조도센서 핀 설정
const int lm35Pin = A1;
const int lightPin = A2;
byte user1[8] = {B11001, B11010, B00100, B00100, B00100, B00100, B00010, B00001};
void setup() {
  // LCD 초기화
  lcd.createChar(0, user1); // 사용자 정의 문자 1 생성
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  int lm35Value = analogRead(lm35Pin);
  float temperature = (lm35Value * 5.0 / 1024.0) * 100.0;

  float lightValue = analogRead(lightPin);

  // LCD에 출력
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.setCursor(11, 0);
  lcd.write(byte(0));

  lcd.setCursor(0, 1);
  lcd.print("Light: ");
  lcd.print(lightValue/1000);

  // 1초 대기
  delay(1000);
}
