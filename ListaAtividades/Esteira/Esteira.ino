const int botaoA = 3;
const int sensor = 4;
const int esteira = 2;

int contador = 0;

// Estados
bool rodando = false;
bool pausado = false;

unsigned long tempoPausa = 0;

// Controle de borda (sensor)
bool ultimoSensor = HIGH;

// Controle de clique do botão
bool ultimoBotaoA = HIGH;

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(sensor, INPUT_PULLUP);
  pinMode(esteira, OUTPUT);
}

void loop() {

  //  DETECÇÃO DE CLIQUE (borda) do botão A
  bool leituraBotao = digitalRead(botaoA);

  if (ultimoBotaoA == HIGH && leituraBotao == LOW) {
    // só executa uma vez por clique
    rodando = true;
    contador = 0;
    pausado = false;
  }

  ultimoBotaoA = leituraBotao;

  //  SISTEMA PARADO
  if (!rodando) {
    digitalWrite(esteira, LOW);
    return;
  }

  //  PAUSA DE 3 SEGUNDOS
  if (pausado) {
    digitalWrite(esteira, LOW);

    if (millis() - tempoPausa >= 3000) {
      pausado = false;
    }

    return;
  }

  //  ESTEIRA RODANDO
  digitalWrite(esteira, HIGH);

  //  LEITURA DO SENSOR
  bool leituraSensor = digitalRead(sensor);

  // Detecta passagem da caixa (borda)
  if (ultimoSensor == HIGH && leituraSensor == LOW) {
    contador++;

    //  Só pausa quando chega exatamente em múltiplos de 5
    if (contador % 5 == 0 && contador < 20) {
      pausado = true;
      tempoPausa = millis();
    }
  }

  ultimoSensor = leituraSensor;

  //  PARA TUDO EM 20 CAIXAS
  if (contador >= 20) {
    rodando = false;
    digitalWrite(esteira, LOW);
  }
}