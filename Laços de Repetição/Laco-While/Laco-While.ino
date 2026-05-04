//Laço de repetição While Exemplo Marcos//

int botao = 2;
void setup() {
 pinMode(botao, INPUT);
 Serial.begin(9600);
 while(digitalRead(botao) == LOW){
 Serial.println("Aguardando botão...");
 delay(500);
 }
 Serial.println("Botão pressionado");
}
void loop() {
}