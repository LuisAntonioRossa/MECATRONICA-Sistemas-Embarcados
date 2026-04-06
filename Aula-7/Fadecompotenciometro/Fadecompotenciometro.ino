const int potPin = A0;  // Pino do potenciômetro
const int ledPin = 9;   // Pino PWM do LED

void setup() {
  pinMode(ledPin, OUTPUT); // Configura o pino do LED como saída
  // Serial.begin(9600);   // Opcional: para depuração
}

void loop() {
  int potValue = analogRead(potPin);        // Lê o potenciômetro (0 a 1023)
  int brightness = map(potValue, 0, 1023, 0, 255); // Mapeia para 0-255
  
  analogWrite(ledPin, brightness);          // Define o brilho do LED
  
  // Pequeno delay para estabilidade
  delay(10);
}