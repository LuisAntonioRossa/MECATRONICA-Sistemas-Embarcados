const int pot = A0;

const int baixo = 2;
const int medio = 3;
const int alto = 4;
const int alerta = 5;

unsigned long tempo = 0;
bool pisca = false;

void setup() {
  pinMode(baixo, OUTPUT);
  pinMode(medio, OUTPUT);
  pinMode(alto, OUTPUT);
  pinMode(alerta, OUTPUT);
}

void loop() {
  int valor = analogRead(pot);

  digitalWrite(baixo, LOW);
  digitalWrite(medio, LOW);
  digitalWrite(alto, LOW);

  //  níveis
  if (valor < 300) digitalWrite(baixo, HIGH);
  else if (valor < 700) digitalWrite(medio, HIGH);
  else digitalWrite(alto, HIGH);

  // alerta crítico
  if (valor < 100 || valor > 900) {
    if (millis() - tempo >= 200) {
      tempo = millis();
      pisca = !pisca;
      digitalWrite(alerta, pisca);
    }
  } else {
    digitalWrite(alerta, LOW);
  }
}