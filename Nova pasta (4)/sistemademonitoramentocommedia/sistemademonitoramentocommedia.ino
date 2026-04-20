const int PIN_NTC = A0;
unsigned long tempoAnterior = 0; // Armazena o último tempo registrado
const long intervalo = 500;       // Intervalo de leitura (ms)

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long tempoAtual = millis();

  // Verifica se já passou o tempo necessário
  if (tempoAtual - tempoAnterior >= intervalo) {
    tempoAnterior = tempoAtual; // Atualiza o marco de tempo

    int leitura = analogRead(PIN_NTC);
    float temp = leitura * 0.488; // Exemplo de conversão linear
    
    Serial.print("Temperatura: ");
    Serial.println(temp);
  }

  // O código aqui fora continua rodando SEM PARAR!
  // Você poderia ler botões ou controlar motores simultaneamente.
}