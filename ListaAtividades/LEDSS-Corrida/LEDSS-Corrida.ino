const int leds[] = {2, 3, 4, 5};
const int quantidade = 4;

// Controle de tempo
unsigned long tempoAnterior = 0;
const int intervalo = 200;

// Controle da sequência
int indiceAtual = 0;

void setup() {
  for (int i = 0; i < quantidade; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  unsigned long tempoAtual = millis();

  // Verifica se passou 200 ms
  if (tempoAtual - tempoAnterior >= intervalo) {
    tempoAnterior = tempoAtual;

    // Apaga todos os LEDs
    for (int i = 0; i < quantidade; i++) {
      digitalWrite(leds[i], LOW);
    }

    // Liga o LED atual
    digitalWrite(leds[indiceAtual], HIGH);

    // Avança para o próximo LED
    indiceAtual++;

    // Volta para o início (efeito loop)
    if (indiceAtual >= quantidade) {
      indiceAtual = 0;
    }
  }
}