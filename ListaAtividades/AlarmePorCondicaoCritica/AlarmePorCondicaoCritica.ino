const int pot = A0;
const int led = 2;

unsigned long tempo = 0;
bool estado = false;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  int valor = analogRead(pot);

  if (valor > 800) {

    if (millis() - tempo >= 100) {
      tempo = millis();
      estado = !estado;
      digitalWrite(led, estado);
    }

  } else {
    digitalWrite(led, LOW);
  }
}