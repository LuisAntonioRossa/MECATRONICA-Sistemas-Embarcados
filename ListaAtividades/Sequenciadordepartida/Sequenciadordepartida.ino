const int botao1 = 4;
const int botao2 = 7;
const int leds[] = {2,3,5,6};

void setup() {
  for (int i = 0; i < 4; i++) pinMode(leds[i], OUTPUT);
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(botao1) == LOW) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], HIGH);
      delay(1000);
    }
  }

  if (digitalRead(botao2) == LOW) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], LOW);
    }
  }
}