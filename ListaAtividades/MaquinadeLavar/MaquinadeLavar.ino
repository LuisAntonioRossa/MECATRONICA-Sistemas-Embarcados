const int botao = 2;

const int led1 = 3; // enchimento
const int led2 = 5; // lavagem PWM
const int led3 = 6; // lavagem PWM
const int led4 = 7; // drenagem

int estado = 0; // 0=parado,1,2,3 etapas

unsigned long tempo = 0;
bool rodando = false;

void setup() {
  pinMode(botao, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {

  // inicia ciclo
  if (digitalRead(botao) == LOW && !rodando) {
    rodando = true;
    estado = 1;
    tempo = millis();
  }

  if (!rodando) return;

  //  ETAPA 1
  if (estado == 1) {
    digitalWrite(led1, HIGH);

    if (millis() - tempo >= 4000) {
      digitalWrite(led1, LOW);
      estado = 2;
      tempo = millis();
    }
  }

  // ETAPA 2 (PWM alternado)
  else if (estado == 2) {

    // alterna LEDs
    if ((millis() / 500) % 2 == 0) {
      analogWrite(led2, 127);
      analogWrite(led3, 0);
    } else {
      analogWrite(led2, 0);
      analogWrite(led3, 127);
    }

    if (millis() - tempo >= 8000) {
      analogWrite(led2, 0);
      analogWrite(led3, 0);
      estado = 3;
      tempo = millis();
    }
  }

  //  ETAPA 3
  else if (estado == 3) {
    digitalWrite(led4, HIGH);

    if (millis() - tempo >= 4000) {
      digitalWrite(led4, LOW);
      rodando = false;
      estado = 0;
    }
  }
}