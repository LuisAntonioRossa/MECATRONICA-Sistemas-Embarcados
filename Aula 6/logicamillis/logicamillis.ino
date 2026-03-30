unsigned long tempo_anterior = 0;
const long intervalo = 1000;
bool estado = 0;
const int ledPin = 8;
const int ledPin2 = 9;
const int ledPin3 = 10;
const int ledPin4 = 11;c:\Users\luis.266322\Documents\Arduino\logicamillis

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  unsigned long tempo_atual = millis();
if (tempo_atual - tempo_anterior >= intervalo) {
  estado = !estado;
  digitalWrite(ledPin, estado);
  digitalWrite(ledPin2, estado);
  digitalWrite(ledPin3, estado);
  digitalWrite(ledPin4, estado);
  tempo_anterior = tempo_atual;
  Serial.println("1 segundo");
}

}
