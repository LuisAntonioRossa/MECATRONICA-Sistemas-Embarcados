// Exercício 4 - SELETOR DE ALTURA DE PEÇAS (Xing-Ling)


// Entradas: botaoStart(START), botaoStop(STOP), sensorCaixaBaixa(caixa alta), sensorCaixaAlta(caixa baixa),
//           sensorAlturaBaixa(sensor altura baixa), sensorAlturaAlta(sensor altura alta)
// Saídas: Q1(esteira esteira altas), Q2(esteira esteira baixas), Q3(Ligada)
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE]
    -> botaoStart(START): Ligada=ON; estado=S1_AGUARDA_PECA (timer 2s estabilização)

  [S1_AGUARDA_PECA]  esteira=ON (esteira liga com peça)
    -> timer>=2s: lê sensorAlturaBaixa e sensorAlturaAlta; estado=S2_CLASSIFICA

  [S2_CLASSIFICA]
    -> SE sensorAlturaAlta ativo (alta): esteira direciona altas; estado=S3_AGUARDA_CAIXA_ALTA
    -> SE !sensorAlturaAlta (baixa):     esteira direciona baixas; estado=S3_AGUARDA_CAIXA_BAIXA

  [S3_AGUARDA_CAIXA_ALTA]
    -> sensorCaixaBaixa ativo: esteira=OFF; Ligada=ON (pronto novo ciclo); estado=S0_IDLE

  [S3_AGUARDA_CAIXA_BAIXA]
    -> sensorCaixaAlta ativo: esteira=OFF; Ligada=ON (pronto novo ciclo); estado=S0_IDLE

  botaoStop(STOP) a qualquer momento -> S0_IDLE; Ligada=OFF

PSEUDO-CÓDIGO:
  estado=S0_IDLE; Ligada=OFF
  LOOP:
    SE botaoStop: Ligada=OFF; esteira=OFF; estado=S0_IDLE
    SE estado==S0_IDLE:
      SE botaoStart: Ligada=ON; tInicio=millis(); estado=S1_AGUARDA_PECA
    SE S1_AGUARDA_PECA:
      esteira=ON
      SE timer>=2s: lê sensores; estado=S2_CLASSIFICA
    SE S2_CLASSIFICA:
      SE sensorAlturaAlta: direciona alta; estado=S3_AGUARDA_ALTA
      SENÃO: direciona baixa; estado=S3_AGUARDA_BAIXA
    SE S3_AGUARDA_ALTA: SE sensorCaixaBaixa: esteira=OFF; estado=S0_IDLE
    SE S3_AGUARDA_BAIXA: SE sensorCaixaAlta: esteira=OFF; estado=S0_IDLE
*/

#define E4_B1_START  A0
#define E4_B0_STOP   A1
#define E4_S1_ALTA   A2
#define E4_S2_BAIXA  A3
#define E4_S3_SENS   A4
#define E4_S4_SENS   A5
const int E4_Q1_ALTA = 60;
const int E4_Q2_BAIXA = 61;
const int E4_Q3_LIGADA = 62;
enum Estado_Ex4 { E4_IDLE, E4_AGUARDA_PECA, E4_CLASSIFICA,
                  E4_AGUARDA_CAIXA_ALTA, E4_AGUARDA_CAIXA_BAIXA };

Estado_Ex4 estadoEx4 = E4_IDLE;
unsigned long tInicioEx4 = 0;
bool pecaAlta4 = false;

void ex4_setup() {
  pinMode(E4_B1_START,  INPUT_PULLUP);
  pinMode(E4_B0_STOP,   INPUT_PULLUP);
  pinMode(E4_S1_ALTA,   INPUT);
  pinMode(E4_S2_BAIXA,  INPUT);
  pinMode(E4_S3_SENS,   INPUT);
  pinMode(E4_S4_SENS,   INPUT);
  pinMode(E4_Q1_ALTA,   OUTPUT);
  pinMode(E4_Q2_BAIXA,  OUTPUT);
  pinMode(E4_Q3_LIGADA, OUTPUT);
}

void ex4_loop() {
  bool b1Start = !digitalRead(E4_B1_START);
  bool b0Stop  = !digitalRead(E4_B0_STOP);
  bool s1Alta  = digitalRead(E4_S1_ALTA);
  bool s2Baixa = digitalRead(E4_S2_BAIXA);
  bool s3      = digitalRead(E4_S3_SENS);
  bool s4      = digitalRead(E4_S4_SENS);
  unsigned long agora = millis();

  if (b0Stop) {
    estadoEx4 = E4_IDLE;
    digitalWrite(E4_Q1_ALTA,   LOW);
    digitalWrite(E4_Q2_BAIXA,  LOW);
    digitalWrite(E4_Q3_LIGADA, LOW);
    return;
  }

  switch (estadoEx4) {
    case E4_IDLE:
      digitalWrite(E4_Q1_ALTA,  LOW);
      digitalWrite(E4_Q2_BAIXA, LOW);
      if (b1Start) {
        digitalWrite(E4_Q3_LIGADA, HIGH);
        tInicioEx4 = agora;
        estadoEx4 = E4_AGUARDA_PECA;
      }
      break;

    case E4_AGUARDA_PECA:
      // esteira ligada, aguarda estabilização 2s
      if (agora - tInicioEx4 >= 2000UL) {
        pecaAlta4 = s4;  // lê classificação
        estadoEx4 = E4_CLASSIFICA;
      }
      break;

    case E4_CLASSIFICA:
      if (pecaAlta4) {
        digitalWrite(E4_Q1_ALTA,  HIGH);
        digitalWrite(E4_Q2_BAIXA, LOW);
        estadoEx4 = E4_AGUARDA_CAIXA_ALTA;
      } else {
        digitalWrite(E4_Q1_ALTA,  LOW);
        digitalWrite(E4_Q2_BAIXA, HIGH);
        estadoEx4 = E4_AGUARDA_CAIXA_BAIXA;
      }
      break;

    case E4_AGUARDA_CAIXA_ALTA:
      if (s1Alta) {
        digitalWrite(E4_Q1_ALTA, LOW);
        estadoEx4 = E4_IDLE;
      }
      break;

    case E4_AGUARDA_CAIXA_BAIXA:
      if (s2Baixa) {
        digitalWrite(E4_Q2_BAIXA, LOW);
        estadoEx4 = E4_IDLE;
      }
      break;
  }
}


