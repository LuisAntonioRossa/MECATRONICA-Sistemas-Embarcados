/*
Ex5 - NTC com alarme piscando
*/
int led=3, ntc=A1;
unsigned long t=0;

void setup(){pinMode(led,OUTPUT);}
void loop(){
 int temp=analogRead(ntc);
 if(temp>600){
  if(millis()-t>200){
   t=millis();
   digitalWrite(led,!digitalRead(led));
  }
 } else digitalWrite(led,LOW);
}