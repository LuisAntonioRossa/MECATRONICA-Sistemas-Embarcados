//Leitura automatica de 4 sensores//
int sensores[4] = {A0, A1, A2, A3};

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(analogRead(sensores[i]));
  }
  Serial.println("------------------------");
  delay(500);
}