/*
Ex1 - Piscar LED com millis
Objetivo: Controle de tempo sem delay
*/
const int led=3;
unsigned long t=0;
int intervalo=500;
bool estado=false;

void setup(){pinMode(led,OUTPUT);}
void loop(){
 unsigned long agora=millis();
 if(agora-t>=intervalo){
  t=agora;
  estado=!estado;
  digitalWrite(led,estado);
 }
}