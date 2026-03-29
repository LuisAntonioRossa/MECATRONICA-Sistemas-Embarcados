/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: contador simples

Autor: Luis Antônio
Data: 29/03/2026
Versão: 1.0

************************************************************************ */
const int botao = 2;      
unsigned long int contador = 0;      
bool valorbotao = 1;      
bool ultimoestadobotao = 1;    
unsigned long timer = 0;     
unsigned long debouncetimer = 50;    

void setup() {
  pinMode(botao, INPUT_PULLUP);     
  Serial.begin(115200);     
}

void loop() {
  int valorlido = digitalRead(botao);    

  if(valorlido != ultimoestadobotao)    
  {
    timer = millis();     
  }
  
  if((millis() - timer) > debouncetimer)     
  {
    if(valorlido != valorbotao)    
    {
      valorbotao = valorlido;    

      if(valorbotao == LOW)    
      {
       contador++;    
       Serial.print("contagem: ");    
       Serial.println(contador);    
      }
    }
  }
  ultimoestadobotao = valorlido;     
}