// 0에서 9까지 숫자 표현을 위한 세그먼트 a, b, c, d, e, f, g, dp의 패턴
byte patterns[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};

// 자릿 수 선택 핀
int digit_select_pin[] = {66, 67, 68, 69};

// 버튼 핀
int button_pin = 14;

// 7세그먼트 모듈 연결 핀 'a, b, c, d, e, f, g, dp' 순서
int segment_pin[] = {58, 59, 60, 61, 62, 63, 64, 65};

int SEGMENT_DELAY = 1;  // 숫자 표시 사이의 시간 간격
bool counting = true; // 상향 하향
bool state = LOW; // 버튼상태

int counter = 0; // 카운터 값

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 4; i++) {
    pinMode(digit_select_pin[i], OUTPUT);
  }
  for(int i = 0; i < 8; i++) {
    pinMode(segment_pin[i], OUTPUT);
  }
  pinMode(button_pin, INPUT);
}

void show_digit(int pos, int number) {
  for(int i = 0; i < 4; i++) {
    if(i + 1 == pos)
      digitalWrite(digit_select_pin[i], LOW);
    else
      digitalWrite(digit_select_pin[i], HIGH);
  }
  for(int i = 0; i < 8; i++) {
    boolean on_off = bitRead(patterns[number], 7 - i);
    digitalWrite(segment_pin[i], on_off);
  }
}

void show_3_digit(int _number) {
  int number = _number;
  
  number = number % 1000;
  int hundreads = number / 100;
  number = number % 100;
  int tens = number / 10;
  int ones = number % 10;

  if(_number > 99) show_digit(2, hundreads);
  delay(SEGMENT_DELAY);
  if(_number > 9) show_digit(3, tens);
  delay(SEGMENT_DELAY);
  show_digit(4, ones);
  delay(SEGMENT_DELAY);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool current_state = digitalRead(button_pin);
  if(current_state != state) {
    if(current_state == HIGH) {
      counting = !counting;
    }
    state = current_state;
  }

  show_3_digit(counter);

  if(counting) {
    counter = (counter + 1) % 1000;
  }
  else {
    counter = (counter - 1 + 1000) % 1000;
  }
  delay(1000);
}
