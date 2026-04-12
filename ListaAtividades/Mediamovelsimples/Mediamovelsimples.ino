const int pot = A0;
const int led = 2;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  int soma = 0;

  for (int i = 0; i < 10; i++) {
    soma += analogRead(pot);
    delay(5);
  }

  int media = soma / 10;

  if (media > 700) digitalWrite(led, HIGH);
  else digitalWrite(led, LOW);
}
