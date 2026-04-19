/*
Ex2 - Botão liga/desliga (toggle)
*/
const int led=3, bot=2;
bool sistema=false, ultimo=HIGH;

void setup(){
 pinMode(led,OUTPUT);
 pinMode(bot,INPUT_PULLUP);
}
void loop(){
 bool l=digitalRead(bot);
 if(ultimo==HIGH && l==LOW) sistema=!sistema;
 ultimo=l;
 digitalWrite(led,sistema);
}