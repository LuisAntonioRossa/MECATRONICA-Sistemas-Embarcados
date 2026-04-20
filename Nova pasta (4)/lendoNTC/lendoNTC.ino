//lendo NTC
const int pinoNTC = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int leitura = analogRead(pinoNTC);
  
  // Conversão rudimentar para Celsius (depende do seu resistor de pull-up)
  // Para precisão total, usa-se a equação de Steinhart-Hart
  float temperatura = leitura * (5.0 / 1023.0) * 10.0; 

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");
  delay(1000);
}