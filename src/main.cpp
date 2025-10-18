#include <Arduino.h>
#include"Temperature.h"

/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/
 
#include <esp_now.h>
#include <WiFi.h>
 
// ЗАМЕНИТЕ МАС-АДРЕСОМ ПЛАТЫ-ПОЛУЧАТЕЛЯ
uint8_t broadcastAddress[] = {0xE8, 0x6B, 0xEA, 0xD4, 0x1F, 0x8C};
 //E8:6B:EA:D4:1F:8C
 float tmor = 0;

Temperature tmp;

// Структура в скетче платы-отправителя
// должна совпадать с оной для получателя
typedef struct struct_message {
  char a [2];//[32];
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
  tmp.settemp();
}
 
void loop() {
  // Указываем данные, которые будем отправлять
  strcpy(myData.a, "a");
  myData.b = random(1,20);// оставал старое
  myData.c = tmp.gettemp();
  myData.d = "Vanna";
  myData.e = false;
 
  // Отправляем сообщение
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);
}   