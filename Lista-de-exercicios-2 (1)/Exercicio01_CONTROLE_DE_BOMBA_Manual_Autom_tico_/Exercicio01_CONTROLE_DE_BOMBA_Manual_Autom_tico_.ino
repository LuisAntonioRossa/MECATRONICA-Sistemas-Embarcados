// Exercício 1 - CONTROLE DE BOMBA (Manual / Automático)


// Entradas: btnAM(modo), btnLIGA, btnDESL, sensorAlto, sensorBaixo
// Saída: BOMBA
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [IDLE] --btnAM(Manual)--> [MANUAL_AGUARDA]
  [IDLE] --btnAM(Auto)---> [AUTO_AGUARDA]

  [MANUAL_AGUARDA] --btnLIGA--> [MANUAL_LIGADA]
  [MANUAL_AGUARDA] --btnAM-->   [IDLE]

  [MANUAL_LIGADA] --btnDESL--> [MANUAL_AGUARDA]
  [MANUAL_LIGADA] --btnAM-->   [IDLE]

  [AUTO_AGUARDA] --sensorBaixo--> [AUTO_TIMER_LIGA]   (inicia timer 10s)
  [AUTO_AGUARDA] --btnAM-->        [IDLE]

  [AUTO_TIMER_LIGA] --timer>=10s--> [AUTO_LIGADA]

  [AUTO_LIGADA] --sensorAlto--> [AUTO_TIMER_DESLIGA]  (inicia timer 10s)

  [AUTO_TIMER_DESLIGA] --timer>=10s--> [AUTO_AGUARDA]

PSEUDO-CÓDIGO:
  estado = IDLE
  LOOP:
    SE estado == IDLE:
      SE btnAM pressionado em Manual: estado = MANUAL_AGUARDA
      SE btnAM pressionado em Auto:   estado = AUTO_AGUARDA

    SE estado == MANUAL_AGUARDA:
      BOMBA = OFF
      SE btnLIGA: estado = MANUAL_LIGADA

    SE estado == MANUAL_LIGADA:
      BOMBA = ON
      SE btnDESL: estado = MANUAL_AGUARDA

    SE estado == AUTO_AGUARDA:
      BOMBA = OFF
      SE sensorBaixo: tInicio=millis(); estado = AUTO_TIMER_LIGA

    SE estado == AUTO_TIMER_LIGA:
      SE millis()-tInicio >= 10000: BOMBA=ON; estado = AUTO_LIGADA

    SE estado == AUTO_LIGADA:
      BOMBA = ON
      SE sensorAlto: tInicio=millis(); estado = AUTO_TIMER_DESLIGA

    SE estado == AUTO_TIMER_DESLIGA:
      SE millis()-tInicio >= 10000: BOMBA=OFF; estado = AUTO_AGUARDA
*/

// --- Pinos ---
#define PIN_MODO_AM    2   // chave seletora (HIGH=Auto, LOW=Manual)
#define PIN_LIGA       3   // botão LIGA (manual)
#define PIN_DESL       4   // botão DESL (manual)
#define PIN_SENSOR_ALT 5   // boia nível alto
#define PIN_SENSOR_BAI 6   // boia nível baixo
#define PIN_BOMBA      7   // saída bomba

enum Estado_Ex1 { IDLE, MAN_AGUARDA, MAN_LIGADA,
                  AUTO_AGUARDA, AUTO_TIMER_LIGA,
                  AUTO_LIGADA, AUTO_TIMER_DESLIGA };

Estado_Ex1 estadoEx1 = IDLE;
unsigned long tInicioEx1 = 0;
bool modoAnteriorEx1 = false;

void ex1_setup() {
  pinMode(PIN_MODO_AM,    INPUT);
  pinMode(PIN_LIGA,       INPUT_PULLUP);
  pinMode(PIN_DESL,       INPUT_PULLUP);
  pinMode(PIN_SENSOR_ALT, INPUT);
  pinMode(PIN_SENSOR_BAI, INPUT);
  pinMode(PIN_BOMBA,      OUTPUT);
}

void ex1_loop() {
  bool modoAuto    = digitalRead(PIN_MODO_AM);
  bool btnLiga     = !digitalRead(PIN_LIGA);
  bool btnDesl     = !digitalRead(PIN_DESL);
  bool nivelAlto   = digitalRead(PIN_SENSOR_ALT);
  bool nivelBaixo  = digitalRead(PIN_SENSOR_BAI);
  unsigned long agora = millis();

  // Detecta mudança de modo -> volta ao IDLE
  if (modoAuto != modoAnteriorEx1 && estadoEx1 != IDLE) {
    estadoEx1 = IDLE;
    digitalWrite(PIN_BOMBA, LOW);
  }
  modoAnteriorEx1 = modoAuto;

  switch (estadoEx1) {
    case IDLE:
      digitalWrite(PIN_BOMBA, LOW);
      if (!modoAuto) estadoEx1 = MAN_AGUARDA;
      else           estadoEx1 = AUTO_AGUARDA;
      break;

    case MAN_AGUARDA:
      digitalWrite(PIN_BOMBA, LOW);
      if (btnLiga) estadoEx1 = MAN_LIGADA;
      break;

    case MAN_LIGADA:
      digitalWrite(PIN_BOMBA, HIGH);
      if (btnDesl) estadoEx1 = MAN_AGUARDA;
      break;

    case AUTO_AGUARDA:
      digitalWrite(PIN_BOMBA, LOW);
      if (nivelBaixo) {
        tInicioEx1 = agora;
        estadoEx1 = AUTO_TIMER_LIGA;
      }
      break;

    case AUTO_TIMER_LIGA:
      if (agora - tInicioEx1 >= 10000UL) {
        estadoEx1 = AUTO_LIGADA;
      }
      break;

    case AUTO_LIGADA:
      digitalWrite(PIN_BOMBA, HIGH);
      if (nivelAlto) {
        tInicioEx1 = agora;
        estadoEx1 = AUTO_TIMER_DESLIGA;
      }
      break;

    case AUTO_TIMER_DESLIGA:
      if (agora - tInicioEx1 >= 10000UL) {
        digitalWrite(PIN_BOMBA, LOW);
        estadoEx1 = AUTO_AGUARDA;
      }
      break;
  }
}


