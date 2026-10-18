#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define SENSOR1 5
#define SENSOR2 17
#define SENSOR3 18
#define SENSORDIferente 19


uint8_t MAC_RECEPTOR[] = {
  0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC
};


OneWire oneWire(SENSOR1);
DallasTemperature sensor(&oneWire);


struct Temperatura {
  float sensor1;
};

Temperatura temperatura;


void envio(const wifi_tx_info_t *info, esp_now_send_status_t status)
{
  if (status == ESP_NOW_SEND_SUCCESS) {
    Serial.println("Dados enviados!");
  } else {
    Serial.println("Erro no envio!");
  }
}


void setup()
{
  Serial.begin(115200);

  
  sensor.begin();

  
  WiFi.mode(WIFI_STA);

  
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao iniciar ESP-NOW!");
    return;
  }

  esp_now_register_send_cb(envio);


  esp_now_peer_info_t peer = {};

  memcpy(peer.peer_addr, MAC_RECEPTOR, 6);

  peer.channel = 0;
  peer.encrypt = false;

  if (esp_now_add_peer(&peer) != ESP_OK) {
    Serial.println("Erro ao adicionar ESP receptor!");
    return;
  }

  Serial.println("ESP EMISSOR PRONTO!");
}


void loop()
{

  sensor.requestTemperatures();

 
  temperatura.sensor1 = sensor.getTempCByIndex(0);

  
  Serial.print("Temperatura: ");
  Serial.print(temperatura.sensor1);
  Serial.println(" C");

  esp_now_send(
    MAC_RECEPTOR,
    (uint8_t *)&temperatura,
    sizeof(temperatura)
  );

 
  delay(2000);
}
