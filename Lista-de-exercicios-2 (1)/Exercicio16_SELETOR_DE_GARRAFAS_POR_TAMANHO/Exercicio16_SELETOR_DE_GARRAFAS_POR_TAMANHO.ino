// Exercício 16 - SELETOR DE GARRAFAS POR TAMANHO


// Entradas: botaoLiga(liga), botaoDesliga(desliga), A(sensor pequena), B(sensor média),
//           C(sensor grande), chave seletora P/M/G
// Saídas: motorEsteira(motor esteira), alarme(alarme)
// Lógica: esteira transporta; se tipo errado detectado -> para + alarme
//         operador retira garrafa -> religar em botaoLiga
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE]
    -> botaoLiga (liga): motorEsteira=ON; estado=S1_TRANSPORTANDO

  [S1_TRANSPORTANDO]  motorEsteira=ON
    -> detecta garrafa:
         SE modo==P e sensor A: OK (continua)
         SE modo==P e (B ou C): motorEsteira=OFF; alarme=ON; estado=S2_ALARME
         SE modo==M e sensor B: OK (B ativo, A pode estar)
         SE modo==M e C: motorEsteira=OFF; alarme=ON; estado=S2_ALARME
         (sensor só A sem B não é M)
         SE modo==G e C ativo: OK
         SE modo==G e (A ou B sem C): motorEsteira=OFF; alarme=ON; estado=S2_ALARME
    -> botaoDesliga (desliga): motorEsteira=OFF; estado=S0_IDLE

  [S2_ALARME]  motorEsteira=OFF, alarme=ON
    -> botaoLiga (após retirar garrafa): alarme=OFF; motorEsteira=ON; estado=S1_TRANSPORTANDO
    -> botaoDesliga: alarme=OFF; estado=S0_IDLE

PSEUDO-CÓDIGO:
  // Sensores óticos A,B,C: garrafa P ativa só A; M ativa A e B; G ativa A,B e C
  estado=IDLE
  LOOP:
    SE botaoDesliga: motorEsteira=OFF;alarme=OFF; IDLE
    SE IDLE: SE botaoLiga: motorEsteira=ON; estado=TRANSPORTANDO
    SE TRANSPORTANDO:
      SE botaoDesliga: motorEsteira=OFF; IDLE
      lê A, B, C, e modo:
        SE modo==P: SE B ou C: ALARME
        SE modo==M: SE C: ALARME; SE só A (sem B): ALARME
        SE modo==G: SE !C: ALARME (se alguma garrafa detectada mas não G)
    SE ALARME: motorEsteira=OFF;alarme=ON; SE botaoLiga: alarme=OFF;motorEsteira=ON;TRANSPORTANDO
*/

#define E16_L    22   // liga
#define E16_D    23   // desliga
#define E16_A    24   // sensor pequena
#define E16_B    25   // sensor média
#define E16_C    26   // sensor grande
#define E16_SEL0 27   // chave seletora bit0 (P=00, M=01, G=10 ou similar)
#define E16_SEL1 28   // chave seletora bit1
#define E16_E    30   // motor esteira
#define E16_AL   31   // alarme

// Codificação da chave: P=0b01, M=0b10, G=0b11 (ou conforme hardware)
// Aqui usamos: SEL0=LOW,SEL1=LOW -> P; SEL0=HIGH -> M; SEL1=HIGH -> G
const int MODO_P = 0;
const int MODO_M = 1;
const int MODO_G = 2;
enum Estado_Ex16 { E16_IDLE, E16_TRANSPORTANDO, E16_ALARME };

Estado_Ex16 estadoEx16 = E16_IDLE;

int ex16_lerModo() {
  bool sel0 = digitalRead(E16_SEL0);
  bool sel1 = digitalRead(E16_SEL1);
  if (sel1)  return MODO_G;
  if (sel0)  return MODO_M;
  return MODO_P;
}

void ex16_setup() {
  for (int p : {E16_L,E16_D}) pinMode(p, INPUT_PULLUP);
  for (int p : {E16_A,E16_B,E16_C,E16_SEL0,E16_SEL1}) pinMode(p, INPUT);
  for (int p : {E16_E,E16_AL}) pinMode(p, OUTPUT);
}

void ex16_loop() {
  bool l  = !digitalRead(E16_L);
  bool d  = !digitalRead(E16_D);
  bool sA = digitalRead(E16_A);
  bool sB = digitalRead(E16_B);
  bool sC = digitalRead(E16_C);
  int modo = ex16_lerModo();

  if (d && estadoEx16 != E16_IDLE) {
    estadoEx16 = E16_IDLE;
    digitalWrite(E16_E, LOW); digitalWrite(E16_AL, LOW);
    return;
  }

  switch (estadoEx16) {
    case E16_IDLE:
      digitalWrite(E16_E, LOW); digitalWrite(E16_AL, LOW);
      if (l) { digitalWrite(E16_E, HIGH); estadoEx16 = E16_TRANSPORTANDO; }
      break;

    case E16_TRANSPORTANDO: {
      bool garrafaDetectada = sA || sB || sC;
      bool alarme = false;

      if (garrafaDetectada) {
        if (modo == MODO_P && (sB || sC)) alarme = true;       // detectou M ou G -> alarme
        if (modo == MODO_M && (sC || !sB)) alarme = true;      // detectou G ou P -> alarme
        if (modo == MODO_G && !sC) alarme = true;              // detectou P ou M -> alarme
      }

      if (alarme) {
        digitalWrite(E16_E, LOW);
        digitalWrite(E16_AL, HIGH);
        estadoEx16 = E16_ALARME;
      }
      break;
    }

    case E16_ALARME:
      digitalWrite(E16_E, LOW);
      digitalWrite(E16_AL, HIGH);
      if (l) {  // operador retirou garrafa e religou
        digitalWrite(E16_AL, LOW);
        digitalWrite(E16_E, HIGH);
        estadoEx16 = E16_TRANSPORTANDO;
      }
      break;
  }
}


// ============================================================
// MAIN SETUP & LOOP (selecione o exercício desejado)
// ============================================================
// Descomente apenas UM dos blocos abaixo para carregar o exercício

// #define EXERCICIO 1   // Controle de Bomba
// #define EXERCICIO 2   // Misturador de Tinta
// #define EXERCICIO 3   // Envasamento/Coroamento
// #define EXERCICIO 4   // Seletor Altura de Peças
// #define EXERCICIO 5   // Cortador de Chapas
// #define EXERCICIO 6   // Transporte Desnível
// #define EXERCICIO 7   // Separador Pequenas/Grandes
// #define EXERCICIO 8   // Seletor por Material
// #define EXERCICIO 9   // Abastecedor Automático
// #define EXERCICIO 10  // Furadeira Automática
// #define EXERCICIO 11  // Pasteurizadora
// #define EXERCICIO 12  // Sistema de Resfriamento
// #define EXERCICIO 13  // Transportadora (limite 5 peças)
// #define EXERCICIO 14  // Dobrador de Cantoneiras
// #define EXERCICIO 15  // Prensa de Segurança
#define EXERCICIO 16     // Seletor de Garrafas

void setup() {
  #if EXERCICIO == 1
    ex1_setup();
  #elif EXERCICIO == 2
    ex2_setup();
  #elif EXERCICIO == 3
    ex3_setup();
  #elif EXERCICIO == 4
    ex4_setup();
  #elif EXERCICIO == 5
    ex5_setup();
  #elif EXERCICIO == 6
    ex6_setup();
  #elif EXERCICIO == 7
    ex7_setup();
  #elif EXERCICIO == 8
    ex8_setup();
  #elif EXERCICIO == 9
    ex9_setup();
  #elif EXERCICIO == 10
    ex10_setup();
  #elif EXERCICIO == 11
    ex11_setup();
  #elif EXERCICIO == 12
    ex12_setup();
  #elif EXERCICIO == 13
    ex13_setup();
  #elif EXERCICIO == 14
    ex14_setup();
  #elif EXERCICIO == 15
    ex15_setup();
  #elif EXERCICIO == 16
    ex16_setup();
  #endif
}

void loop() {
  #if EXERCICIO == 1
    ex1_loop();
  #elif EXERCICIO == 2
    ex2_loop();
  #elif EXERCICIO == 3
    ex3_loop();
  #elif EXERCICIO == 4
    ex4_loop();
  #elif EXERCICIO == 5
    ex5_loop();
  #elif EXERCICIO == 6
    ex6_loop();
  #elif EXERCICIO == 7
    ex7_loop();
  #elif EXERCICIO == 8
    ex8_loop();
  #elif EXERCICIO == 9
    ex9_loop();
  #elif EXERCICIO == 10
    ex10_loop();
  #elif EXERCICIO == 11
    ex11_loop();
  #elif EXERCICIO == 12
    ex12_loop();
  #elif EXERCICIO == 13
    ex13_loop();
  #elif EXERCICIO == 14
    ex14_loop();
  #elif EXERCICIO == 15
    ex15_loop();
  #elif EXERCICIO == 16
    ex16_loop();
  #endif
}

// ============================================================
// EXERCÍCIOS FSM - Sistemas Digitais - SATC
// Todos os exercícios usam millis() em vez de delay()
// ============================================================


