int pin_sensor = A0;
int valor_sensor = 0;

void setup() {
  pinMode(pin_sensor, INPUT);
  Serial.begin(115200);
}

void loop() {
  valor_sensor = analogRead(pin_sensor);
  Serial.print("valor analogico = ");
  Serial.print(valor_sensor);
  delay(200);
}