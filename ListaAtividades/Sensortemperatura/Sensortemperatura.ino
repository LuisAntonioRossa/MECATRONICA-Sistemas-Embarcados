const int ntc = A0;
const int led = 2;

unsigned long tempo = 0;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  int valor = analogRead(ntc);

  if (valor > 183) { // ajuste conforme necessário
    if (millis() - tempo >= 100) {
      tempo = millis();
      digitalWrite(led, !digitalRead(led));
    }
  } else {
    digitalWrite(led, LOW);
  }
}
