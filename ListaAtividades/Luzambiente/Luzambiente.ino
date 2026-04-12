const int ldr = A0;
const int botao = 2;
const int led = 9;

void setup() {
  pinMode(botao, INPUT_PULLUP);
}

void loop() {
  int luz = analogRead(ldr);

  if (digitalRead(botao) == HIGH) {
    analogWrite(led, 25); // 10%
    return;
  }

  int pwm = map(luz, 0, 1023, 255, 0);

  analogWrite(led, pwm);
}