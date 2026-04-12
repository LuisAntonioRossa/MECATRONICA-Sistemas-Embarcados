const int botao = 4;
const int atuador = 3;
const int corrente = 5;
const int pronto = 6;
const int pot = A0;

int estado = 0;
unsigned long tempo = 0;

void setup() {
  pinMode(botao, INPUT_PULLUP);
  pinMode(atuador, OUTPUT);
  pinMode(pronto, OUTPUT);
}

void loop() {

  if (digitalRead(botao) == LOW && estado == 0) {
    estado = 1;
    tempo = millis();
  }

  if (estado == 1 && millis() - tempo >= 800) {
    digitalWrite(atuador, HIGH);
    estado = 2;
    tempo = millis();
  }

  else if (estado == 2 && millis() - tempo >= 200) {
    int pwm = map(analogRead(pot), 0, 1023, 0, 255);
    analogWrite(corrente, pwm);
    estado = 3;
    tempo = millis();
  }

  else if (estado == 3 && millis() - tempo >= 1500) {
    analogWrite(corrente, 0);
    estado = 4;
    tempo = millis();
  }

  else if (estado == 4 && millis() - tempo >= 500) {
    digitalWrite(atuador, LOW);
    digitalWrite(pronto, HIGH);
    estado = 5;
    tempo = millis();
  }

  else if (estado == 5 && millis() - tempo >= 2000) {
    digitalWrite(pronto, LOW);
    estado = 0;
  }
}