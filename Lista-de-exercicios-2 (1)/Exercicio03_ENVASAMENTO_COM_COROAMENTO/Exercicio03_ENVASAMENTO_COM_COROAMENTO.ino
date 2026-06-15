// Exercício 3 - ENVASAMENTO COM COROAMENTO


// Entradas: START(botaoStart), STOP(botaoStop), FT(falta tampinha),
//           ST1(sensor tampinha), SP1(posição P1), ST2(sensor tampa P2),
//           SR(início curso coroador), SA(fim curso coroador)
// Saídas: esteiraGarrafas(esteira garrafas), coroador(motor coroamento), FC(alarme falha)
// Contador de garrafas (limite 24)
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE]
    -> START e !FT -> [S1_ESTEIRA_ON]

  [S1_ESTEIRA_ON]  esteiraGarrafas=ON
    -> SP1 detecta garrafa -> [S2_PARA_M1]

  [S2_PARA_M1]  esteiraGarrafas=OFF
    -> verifica ST2 simultaneamente
    -> SE !ST2 em P2: estado=S_ALARME_FC (após coroamento)
    -> SE ST1 ok: estado=[S3_COROA] (inicia timer 2s)

  [S3_COROA]  coroador=ON, puxa tampinha
    -> SA (fim de curso avançado) -> espera 2s -> [S4_RETORNA]

  [S4_RETORNA]  coroador recua
    -> SR (início = recuado) -> verifica ST2

  [S4b_VERIF_TAMPA]
    -> SE ST2 ok: contGarrafas++; SE >=24: S_FIM; senão: S1_ESTEIRA_ON
    -> SE !ST2: S_ALARME_FC

  [S_ALARME_FC]  FC=ON, esteiraGarrafas=OFF
    -> START (operador reinicia) -> S0_IDLE

  [S_FIM]  24 garrafas completas
    -> START -> zera contador -> S0_IDLE
    -> STOP  -> S0_IDLE

  (STOP a qualquer momento -> S0_IDLE)

PSEUDO-CÓDIGO:
  estado=S0_IDLE; contGarrafas=0; atingiu24=false
  LOOP:
    SE STOP: estado=S0_IDLE; esteiraGarrafas=OFF; coroador=OFF; FC=OFF
    SE estado==S0_IDLE:
      esteiraGarrafas=OFF; coroador=OFF; FC=OFF
      SE START e !FT: estado=S1_ESTEIRA_ON
        SE atingiu24: zera contGarrafas; atingiu24=false
    SE S1_ESTEIRA_ON: esteiraGarrafas=ON; SE SP1: esteiraGarrafas=OFF; estado=S2_PARA_M1
    SE S2_PARA_M1: salva estadoST2; SE SA: tInicio=millis(); estado=S3_COROA
    SE S3_COROA: coroador=ON; SE timer>=2s: estado=S4_RETORNA
    SE S4_RETORNA: coroador recua (lógica direção); SE SR: estado=S4b_VERIF
    SE S4b_VERIF:
      SE estadoST2 ok: contGarrafas++; SE>=24: atingiu24=true; S_FIM
                        senão: estado=S1_ESTEIRA_ON
      SE !estadoST2: estado=S_ALARME_FC
    SE S_ALARME_FC: FC=ON; SE START: FC=OFF; estado=S0_IDLE
    SE S_FIM: SE START: zera; estado=S0_IDLE
*/
const int E3_START = 40;
const int E3_STOP = 41;
const int E3_FT = 42;
const int E3_ST1 = 43;
const int E3_SP1 = 44;
const int E3_ST2 = 45;
const int E3_SR = 46;
const int E3_SA = 47;
const int E3_M1 = 50;
const int E3_CR = 51;
const int E3_FC = 52;
enum Estado_Ex3 { E3_IDLE, E3_ESTEIRA_ON, E3_PARA_M1,
                  E3_COROA, E3_RETORNA, E3_VERIF_TAMPA,
                  E3_ALARME_FC, E3_FIM };

Estado_Ex3 estadoEx3 = E3_IDLE;
unsigned long tInicioEx3 = 0;
int contGarrafasEx3 = 0;
bool atingiu24 = false;
bool st2NoMomentoParada = false;

void ex3_setup() {
  pinMode(E3_START, INPUT_PULLUP);
  pinMode(E3_STOP,  INPUT_PULLUP);
  pinMode(E3_FT,    INPUT);
  pinMode(E3_ST1,   INPUT);
  pinMode(E3_SP1,   INPUT);
  pinMode(E3_ST2,   INPUT);
  pinMode(E3_SR,    INPUT);
  pinMode(E3_SA,    INPUT);
  pinMode(E3_M1,    OUTPUT);
  pinMode(E3_CR,    OUTPUT);
  pinMode(E3_FC,    OUTPUT);
}

void ex3_loop() {
  bool start = !digitalRead(E3_START);
  bool stop  = !digitalRead(E3_STOP);
  bool ft    = digitalRead(E3_FT);
  bool st1   = digitalRead(E3_ST1);
  bool sp1   = digitalRead(E3_SP1);
  bool st2   = digitalRead(E3_ST2);
  bool sr    = digitalRead(E3_SR);
  bool sa    = digitalRead(E3_SA);
  unsigned long agora = millis();

  if (stop && estadoEx3 != E3_ALARME_FC && estadoEx3 != E3_FIM) {
    estadoEx3 = E3_IDLE;
    digitalWrite(E3_M1, LOW);
    digitalWrite(E3_CR, LOW);
    digitalWrite(E3_FC, LOW);
    return;
  }

  switch (estadoEx3) {
    case E3_IDLE:
      digitalWrite(E3_M1, LOW);
      digitalWrite(E3_CR, LOW);
      digitalWrite(E3_FC, LOW);
      if (start && !ft) {
        if (atingiu24) { contGarrafasEx3 = 0; atingiu24 = false; }
        estadoEx3 = E3_ESTEIRA_ON;
      }
      break;

    case E3_ESTEIRA_ON:
      digitalWrite(E3_M1, HIGH);
      if (sp1) {
        digitalWrite(E3_M1, LOW);
        st2NoMomentoParada = st2;
        estadoEx3 = E3_PARA_M1;
      }
      break;

    case E3_PARA_M1:
      if (sa) {
        tInicioEx3 = agora;
        estadoEx3 = E3_COROA;
      }
      break;

    case E3_COROA:
      digitalWrite(E3_CR, HIGH);
      if (agora - tInicioEx3 >= 2000UL) {
        estadoEx3 = E3_RETORNA;
      }
      break;

    case E3_RETORNA:
      digitalWrite(E3_CR, LOW);
      if (sr) estadoEx3 = E3_VERIF_TAMPA;
      break;

    case E3_VERIF_TAMPA:
      if (!st2NoMomentoParada) {
        estadoEx3 = E3_ALARME_FC;
      } else {
        contGarrafasEx3++;
        if (contGarrafasEx3 >= 24) {
          atingiu24 = true;
          estadoEx3 = E3_FIM;
        } else {
          estadoEx3 = E3_ESTEIRA_ON;
        }
      }
      break;

    case E3_ALARME_FC:
      digitalWrite(E3_FC, HIGH);
      if (start) {
        digitalWrite(E3_FC, LOW);
        estadoEx3 = E3_IDLE;
      }
      break;

    case E3_FIM:
      if (start) {
        contGarrafasEx3 = 0;
        atingiu24 = false;
        estadoEx3 = E3_IDLE;
      }
      break;
  }
}


