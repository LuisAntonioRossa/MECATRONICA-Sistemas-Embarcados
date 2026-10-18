/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Seguidor de linha

Autor: Luis Antônio e Marco Moser
Data: 22/06/2023
Versão: 2.0

************************************************************************ */

//====================[ MOTOR DIREITO ]====================

const int pino_INA = 9;      // PWM velocidade
const int pino_IN1 = 8;      // Sentido A
const int pino_IN2 = 10;     // Sentido B


//====================[ MOTOR ESQUERDO ]====================

const int pino_INB = 11;     // PWM velocidade
const int pino_IN3 = 12;     // Sentido A
const int pino_IN4 = 13;     // Sentido B


//====================[ SENSORES ]====================

const int S1 = 6;            // Extrema esquerda
const int S2 = 5;            // Esquerda
const int S3 = 4;            // Centro
const int S4 = 3;            // Direita
const int S5 = 2;            // Extrema direita

//====================[ VELOCIDADES ]====================

// Frente reta
const int velocidadeReta = 200;

// Curvas
const int curvaLeve = 100;
const int curvaForte = 50;
const int curvaMaxima = 0;

const int velocidadeAlta = 255;


//====================[ CONTROLE ]====================

// Guarda o último lado onde a linha foi encontrada
// -1 = esquerda
//  0 = centro
//  1 = direita

int ultimoLado = 0;



void setup()
{
  // Motores
  pinMode(pino_INA, OUTPUT);
  pinMode(pino_IN1, OUTPUT);
  pinMode(pino_IN2, OUTPUT);

  pinMode(pino_INB, OUTPUT);
  pinMode(pino_IN3, OUTPUT);
  pinMode(pino_IN4, OUTPUT);


  // Sensores
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);


  // Define o sentido inicial
  motoresFrente();
}



void loop()
{
  // Leitura dos sensores
  int s1 = digitalRead(S1);
  int s2 = digitalRead(S2);
  int s3 = digitalRead(S3);
  int s4 = digitalRead(S4);
  int s5 = digitalRead(S5);



  //====================[ LINHA CENTRAL ]====================

  if (s3 == HIGH && s1 == LOW && s2 == LOW &&
      s4 == LOW && s5 == LOW)
  {
    mover(velocidadeReta, velocidadeReta);
    ultimoLado = 0;
  }


  //====================[ CURVAS ESQUERDA ]====================

  else if (s1 == HIGH && s2 == HIGH)
  {
    // Curva máxima
    mover(curvaMaxima, velocidadeAlta);
    ultimoLado = -1;
  }

  else if (s1 == HIGH)
  {
    // Curva forte
    mover(curvaForte, velocidadeAlta);
    ultimoLado = -1;
  }

  else if (s2 == HIGH)
  {
    // Curva leve
    mover(curvaLeve, velocidadeAlta - 25);
    ultimoLado = -1;
  }



  //====================[ CURVAS DIREITA ]====================

  else if (s4 == HIGH && s5 == HIGH)
  {
    // Curva máxima
    mover(velocidadeAlta, curvaMaxima);
    ultimoLado = 1;
  }

  else if (s5 == HIGH)
  {
    // Curva forte
    mover(velocidadeAlta, curvaForte);
    ultimoLado = 1;
  }

  else if (s4 == HIGH)
  {
    // Curva leve
    mover(velocidadeAlta - 25, curvaLeve);
    ultimoLado = 1;
  }



  //====================[ PERDEU A LINHA ]====================

  else
  {
    // Procura a linha no último lado conhecido

    if (ultimoLado == -1)
    {
      mover(curvaMaxima, velocidadeAlta);
    }

    else if (ultimoLado == 1)
    {
      mover(velocidadeAlta, curvaMaxima);
    }

    else
    {
      mover(0, 0);
    }
  }
}



//====================[ SENTIDO DOS MOTORES ]====================

void motoresFrente()
{
  // Motor direito
  digitalWrite(pino_IN1, HIGH);
  digitalWrite(pino_IN2, LOW);


  // Motor esquerdo
  digitalWrite(pino_IN3, HIGH);
  digitalWrite(pino_IN4, LOW);
}



//====================[ CONTROLE DE VELOCIDADE ]====================

void mover(int velEsq, int velDir)
{
  motoresFrente();


  // Motor esquerdo
  analogWrite(pino_INB, velEsq);


  // Motor direito
  analogWrite(pino_INA, velDir);
}