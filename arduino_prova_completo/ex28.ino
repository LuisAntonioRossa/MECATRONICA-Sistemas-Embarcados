/*
Ex3 - Temporizador 3s
*/
const int led=3, bot=2;
unsigned long inicio=0;
bool ativo=false, ult=HIGH;

void setup(){
 pinMode(led,OUTPUT);
 pinMode(bot,INPUT_PULLUP);
}
void loop(){
 bool l=digitalRead(bot);
 if(ult==HIGH && l==LOW){
  inicio=millis();
  ativo=true;
 }
 ult=l;

 if(ativo){
  if(millis()-inicio<3000) digitalWrite(led,HIGH);
  else{digitalWrite(led,LOW); ativo=false;}
 }
}