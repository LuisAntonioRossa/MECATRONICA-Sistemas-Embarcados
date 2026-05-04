//Laço de repetição do while //
int tentativa = 0;
void setup() {
 Serial.begin(9600);
 do{
 Serial.println("Tentando conectar...");
 tentativa++;
 delay(1000);
 }while(tentativa < 3);
}
void loop() {
}
