const int led1 = 2;
const int bot = 3;

int nivel =0;
bool ultimoEstado = HIGH;

void setup (){
  pinMode(bot, INPUT_PULLUP);
}
void loop (){
  bool estado = digitalRead(bot);
  
  if(ultimoEstado == HIGH && estado == LOW){
    nivel++;
    if(nivel > 4)nivel = 0;
  }
  
  ultimoEstado = estado; 
  
  int brilho = nivel * 63; // 0, 63, 126, 252
  analogWrite(led1, brilho);
}
  
 