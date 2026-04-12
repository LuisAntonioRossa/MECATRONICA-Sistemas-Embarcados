const int pot = A0;
const int led = 2;

unsigned long tempo = 0;
bool estado = false;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  int valor = analogRead(pot);

  int intervalo = map(valor, 0, 1023, 2000, 100);

  if (millis() - tempo >= intervalo) {
    tempo = millis();
    estado = !estado;
    digitalWrite(led, estado);
  }
}
