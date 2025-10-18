#include <Arduino.h>
//#include"Temperature.h"
//#include <DallasTemperature.h>

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
// Номер пина Arduino с подключенным датчиком

//--------------------------------------------
#include <OneWire.h>

OneWire ds(8); // Объект OneWire

int temperature = 0; // Глобальная переменная для хранения значение температуры с датчика DS18B20

long lastUpdateTime = 0; // Переменная для хранения времени последнего считывания с датчика
const int TEMP_UPDATE_TIME = 1000; // Определяем периодичность проверок



 float tmor = 0;

//Temperature tmp;

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
  //tmp.settemp();
}
 
void loop() {

    detectTemperature(); // Определяем температуру от датчика DS18b20
  Serial.println(temperature); // Выводим полученное значение температуры
  // Т.к. переменная temperature имеет тип int, дробная часть будет просто
  // Указываем данные, которые будем отправлять
  strcpy(myData.a, "a");
  myData.b = random(1,20);// оставал старое
  myData.c = 10.2;
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
  }
} 

/*
#include <DallasTemperature.h>

// Номер пина Arduino с подключенным датчиком
#define PIN_DS18B20 8

// Создаем объект OneWire
OneWire oneWire(PIN_DS18B20);

// Создаем объект DallasTemperature для работы с сенсорами, передавая ему ссылку на объект для работы с 1-Wire.
DallasTemperature dallasSensors(&amp;oneWire);

// Специальный объект для хранения адреса устройства
DeviceAddress sensorAddress;

void loop(void){
  // Запрос на измерения датчиком температуры

  Serial.print("Измеряем температуру...");
  dallasSensors.requestTemperatures(); // Просим ds18b20 собрать данные
  Serial.println("Выполнено");

  //  Запрос на получение сохраненного значения температуры
  printTemperature(sensorAddress);

  // Задержка для того, чтобы можно было что-то разобрать на экране
  delay(1000);
}

// Вспомогательная функция печати значения температуры для устрйоства
void printTemperature(DeviceAddress deviceAddress){
  float tempC = dallasSensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.println(tempC);
}

// Вспомогательная функция для отображения адреса датчика ds18b20
void printAddress(DeviceAddress deviceAddress){
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

*/