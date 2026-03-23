
const int pin_botao = 2;
bool botao = false;
//
void setup(){
  pinMode(pin_botao, INPUT_PULLUP);
  Serial.begin(115200); // Definição da velocidade
}
void loop() {
  botao = digitalRead(pin_botao);
  if (botao == LOW) {
    Serial.println("Botao pressionado!");
  }
}