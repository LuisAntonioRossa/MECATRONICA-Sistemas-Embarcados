/*
Ex4 - Potenciômetro controla brilho
*/
int led=3, pot=A0;

void setup(){pinMode(led,OUTPUT);}
void loop(){
 int v=analogRead(pot);
 int pwm=map(v,0,1023,0,255);
 analogWrite(led,pwm);
}