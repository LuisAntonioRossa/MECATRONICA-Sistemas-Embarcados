const int PIN_NTC = A0;
const int LED_ALERTA = 13;

unsigned long tSensor = 0;
unsigned long tLed = 0;
bool estadoLed = LOW;

float tempAtual = 0;

// Função void para ler o sensor (executa a cada 1 segundo)
void lerSensor() {
  if (millis() - tSensor >= 1000) {
    tSensor = millis();
    tempAtual = analogRead(PIN_NTC) * 0.488; 
    Serial.print("Monitorando: ");
    Serial.println(tempAtual);
  }
}

// Função void para piscar o LED sem travar o código
void gerenciarAlarme(float t) {
  if (t > 30.0) {
    // Pisca o LED a cada 200ms se a temp estiver alta
    if (millis() - tLed >= 200) {
      tLed = millis();
      estadoLed = !estadoLed; // Inverte o estado (HIGH/LOW)
      digitalWrite(LED_ALERTA, estadoLed);
    }
  } else {
    digitalWrite(LED_ALERTA, LOW);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_ALERTA, OUTPUT);
}

void loop() {
  lerSensor();        // Executa sua lógica interna baseada em millis()
  gerenciarAlarme(tempAtual); 
}