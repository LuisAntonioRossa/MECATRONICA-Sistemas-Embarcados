const int led_vermelho = 5;			
const int led_verde = 6;			
const int led_amarelo = 7;			
char led;					
//
const int pin_botaoA = 2;
const int pin_botaoB = 3;
bool botaoA = false;
bool botaoB = false;
//
void setup(){
  pinMode(led_vermelho, OUTPUT);		
  pinMode(led_verde, OUTPUT);			
  pinMode(led_amarelo, OUTPUT);
  //
  pinMode(pin_botaoA, INPUT_PULLUP);
  pinMode(pin_botaoB, INPUT_PULLUP);
  Serial.begin(115200); // Definição da velocidade
}
void loop() {
  botaoA = digitalRead(pin_botaoA);
  botaoB = digitalRead(pin_botaoB);
  if (botaoA == 0 && botaoB == 0) { //A e B pressionado liga vermelho
    digitalWrite(led_vermelho, HIGH);
  } else {
    digitalWrite(led_vermelho, LOW);
  }
  if (botaoA ==0 || botaoB ==0) { // A ou B pressionado liga verde
    digitalWrite(led_verde, HIGH);
  } else {
    digitalWrite(led_verde, LOW);
  }
  if (botaoA ==0 ^ botaoB ==0) { // A XOR B pressionado liga amarelo
    digitalWrite(led_amarelo, HIGH);
  } else {
    digitalWrite(led_amarelo, LOW);
  }
  
}