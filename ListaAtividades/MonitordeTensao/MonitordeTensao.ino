const int pot = A0;

const int verde = 2;
const int amarelo = 3;
const int vermelho = 4;
const int geral = 5;

unsigned long tempoFalha = 0;
bool foraFaixa = false;

void setup() {
  pinMode(verde, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(geral, OUTPUT);
}

void loop() {
  int valor = analogRead(pot);

  // converte para tensão
  float tensao = valor * (250.0 / 1023.0);

  // faixa normal
  if (tensao >= 210 && tensao <= 230) {
    digitalWrite(verde, HIGH);
    digitalWrite(amarelo, LOW);
    digitalWrite(vermelho, LOW);
  }
  else if (tensao < 210) {
    digitalWrite(amarelo, HIGH);
    digitalWrite(verde, LOW);
  }
  else {
    digitalWrite(vermelho, HIGH);
    digitalWrite(verde, LOW);
  }

  // fora da faixa crítica
  if (tensao < 180 || tensao > 240) {

    if (!foraFaixa) {
      tempoFalha = millis();
      foraFaixa = true;
    }

    if (millis() - tempoFalha >= 2000) {
      digitalWrite(geral, LOW); // desliga sistema
    }

  } else {
    foraFaixa = false;
    digitalWrite(geral, HIGH);
  }
}