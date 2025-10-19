/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/
//#include <DallasTemperature.h>
#include <Arduino.h>
#include"Temperature.h"
#include <esp_now.h>
#include <WiFi.h>
#include <OneWire.h>

// ЗАМЕНИТЕ МАС-АДРЕСОМ ПЛАТЫ-ПОЛУЧАТЕЛЯ
uint8_t broadcastAddress[] = {0xE8, 0x6B, 0xEA, 0xD4, 0x1F, 0x8C};

// Номер пина Arduino с подключенным датчиком
OneWire ds(4); // Объект OneWire

//--------------------------------------------

int temperature = 0; // Глобальная переменная для хранения значение температуры с датчика DS18B20

long lastUpdateTime = 0; // Переменная для хранения времени последнего считывания с датчика
const int TEMP_UPDATE_TIME = 1000; // Определяем периодичность проверок

// const uint8_t vanRoom = 1;
// const uint8_t mojPlace = 3;
 float tmor = 0;
 int voda = 1000;
int detectTemperature();
bool getVoda(uint8_t vlaga);
String uzel();

Temperature tmp;

// Структура в скетче платы-отправителя
// должна совпадать с оной для получателя
typedef struct struct_message {
  char a [32];//[32];
  int b;
  float c;
  String d;
  bool e;
} struct_message;
 
// Создаем структуру сообщение myData
struct_message myData;
 
// Обратная функция отправки
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // Запускаем монитор порта
  Serial.begin(115200);
 
  // Выбираем режим WiFi
  WiFi.mode(WIFI_STA);
 
  // Запускаем протокол ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
 pinMode(1, INPUT_PULLUP);
 pinMode(3, INPUT_PULLUP);   
  // Регистрируем отправку сообщение
  esp_now_register_send_cb(OnDataSent);
  
  // Указываем получателя
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  //tmp.settemp();
}
 
void loop() {

  //temperature = 
  temperature = detectTemperature(); // Определяем температуру от датчика DS18b20
  
  tmp.setVlagaMoj();
  tmp.setVlagaVan();

  voda= tmp.getUzel();
  
  // Т.к. переменная temperature имеет тип int, дробная часть будет просто
  // Указываем данные, которые будем отправлять
  strcpy(myData.a, "a");
  myData.b = tmp.getSensor();// оставил старое
  myData.c = temperature;//10.2;
  myData.d = uzel();
  myData.e = getVoda(voda);
 
  // Отправляем сообщение
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(5000);
}  


int detectTemperature(){

  byte data[2];
  ds.reset();
  ds.write(0xCC);
  ds.write(0x44);

  if (millis() - lastUpdateTime > TEMP_UPDATE_TIME)
  {
    lastUpdateTime = millis();
    ds.reset();
    ds.write(0xCC);
    ds.write(0xBE);
    data[0] = ds.read();
    data[1] = ds.read();

    // Формируем значение
    temperature = (data[1] << 8) + data[0]; temperature = temperature >> 4;
  } return temperature;
}
bool getVoda(uint8_t vlaga) {
  bool flag;
  if(!vlaga){
    flag = false;
  } else flag = true;
// tmp.setVlagaMoj();
// tmp.setVlagaVan();
// voda= tmp.getUzel();

  return flag;
}

String uzel(){
  String pok;
  switch (voda)
  {
  case 1: pok = "Mojka"; break;
  case 2: pok = "Vanna"; break;
  case 3: pok = " Dubl"; break;
  default:pok = "Suho"; break;
  } return pok;
}
