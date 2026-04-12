const int botao = 3;
const int ntc = A0;

const int aquecimento = 2; // LED 1
const int faixa = 4;       // LED 2

bool sistemaLigado = false; // controla se o sistema está ativo
bool aquecendo = false;     //  memória da histerese

bool ultimoBotao = HIGH; // para detectar clique

void setup() {
  pinMode(botao, INPUT_PULLUP);
  pinMode(aquecimento, OUTPUT);
  pinMode(faixa, OUTPUT);
}

void loop() {

  //  DETECÇÃO DE CLIQUE DO BOTÃO
  bool leitura = digitalRead(botao);

  if (ultimoBotao == HIGH && leitura == LOW) {
    sistemaLigado = !sistemaLigado; // liga/desliga sistema
  }

  ultimoBotao = leitura;

  //  SE SISTEMA DESLIGADO
  if (!sistemaLigado) {
    digitalWrite(aquecimento, LOW);
    digitalWrite(faixa, LOW);
    return; // para o resto do código
  }

  //  LEITURA DO SENSOR
  int valor = analogRead(ntc);

  // valores simulados (ajustáveis)
  int temp150 = 400; // equivalente a "150°C simulado"
  int temp160 = 600;  // equivalente a "160°C simulado"

  // HISTERSESE (PARTE MAIS IMPORTANTE)
  if (valor <= temp150) {
    aquecendo = true;
  }

  if (valor >= temp160) {
    aquecendo = false;
  }

  // aplica no LED
  digitalWrite(aquecimento, aquecendo);

  //  LED indica faixa ideal
  if (valor >= temp150 && valor <= temp160) {
    digitalWrite(faixa, HIGH);
  } else {
    digitalWrite(faixa, LOW);
  }
}