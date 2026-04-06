int pin_sensor = A0;
int valor_sensor = 0;
const int led1 = 9;
const int led2 = 10;
const int led3 = 11;

void setup() {
 pinMode(pin_sensor, INPUT);
 Serial.begin(115200);
 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);
 pinMode(led3, OUTPUT);

}

void loop() {
  valor_sensor = analogRead(pin_sensor);
  float valor_tensao = (valor_sensor * 5.0)/1023;
  Serial.print("valor analogico = ");
  Serial.print(valor_sensor);
 
  if (valor_sensor >= 4) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }
  else if (valor_sensor >=3) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
  }
  else if (valor_sensor >= 2) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
  }
  else if (valor_sensor >= 1) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  } else { 
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
}

