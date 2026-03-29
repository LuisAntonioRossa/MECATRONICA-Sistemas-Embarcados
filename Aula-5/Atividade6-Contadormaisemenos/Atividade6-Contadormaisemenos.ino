/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Contador mais e menos

Autor: Luis Antônio
Data: 29/03/2026
Versão: 1.0

************************************************************************ */
const int botao1 = 2;     
const int botao2 = 3; 

int contador = 0;    

bool valorbotao1 = HIGH;    
bool valorbotao2 = HIGH;    
bool ultimoestadobotao1 = 1;     
bool ultimoestadobotao2 = 1; 
    
unsigned long timer1 = 0;     
unsigned long timer2 = 0;    
unsigned long debouncetimer = 50;    

void setup() {
  pinMode(botao1, INPUT_PULLUP);     
  pinMode(botao2, INPUT_PULLUP);     
  Serial.begin(115200);    
}

void loop() {
  int valorlido1 = digitalRead(botao1);     
  int valorlido2 = digitalRead(botao2);   

  if(valorlido1 != ultimoestadobotao1)     
  {
    timer1 = millis();    
  }
  
  if((millis() - timer1) > debouncetimer)     
  {
    if(valorlido1 != valorbotao1)    
    {
      valorbotao1 = valorlido1;    

    if(valorbotao1 == LOW)    
    {
      contador++;     
      Serial.print("contagem: ");    
      Serial.println(contador);     
    }
    }
  }
  if(valorlido2 != ultimoestadobotao2)     
  {
    timer2 = millis();     
  }
  
  if((millis() - timer2) > debouncetimer)      
  {
    if(valorlido2 != valorbotao2)     
    {
      valorbotao2 = valorlido2;     

    if(valorbotao2 == LOW)    
    {
      contador--;     
      Serial.print("contagem: ");     
      Serial.println(contador);     
    }
    }
  }
  ultimoestadobotao1 = valorlido1;      
  ultimoestadobotao2 = valorlido2;      
}
