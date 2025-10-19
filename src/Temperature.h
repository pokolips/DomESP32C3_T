#pragma once

// #include <OneWire.h>
// //#include <DallasTemperature.h>
// //#define PIN_DS18B20 8
// // Создаем объект OneWire
// //OneWire oneWire(PIN_DS18B20);
// OneWire ds(8); // Объект OneWire

// // Создаем объект DallasTemperature для работы с сенсорами, передавая ему ссылку на объект для работы с 1-Wire.
// //DallasTemperature dallasSensors(&amp;oneWire);

// // Специальный объект для хранения адреса устройства
// //DeviceAddress sensorAddress;
// //------------------------------------
class Temperature
{
private:
  float _termo = 10;
  uint8_t _vodaV = 0;
  uint8_t _vodaM = 0;
  uint8_t _voda = 0;
  const uint8_t vanRoom = 1;
const uint8_t mojPlace = 3;
  int pinSensorV = 1;
  int pinSensorM = 3;
  int _vlaga = 1000;

public:
int getSensor(){
analogRead (pinSensorV);
if (analogRead (pinSensorV) > 1000){
_vlaga = 1000;
} return _vlaga;

}
void setVlagaVan(){
   if(analogRead(vanRoom) < 700){
    _vodaV = 1;
  } else _vodaV = 0;
  delay(20);
}
void setVlagaMoj(){
if(analogRead(mojPlace) < 700){
    _vodaM = 1;
  } else _vodaM = 0;
  delay(20);
}
 uint8_t getUzel(){
if(_vodaM == 1 && _vodaV == 1){
  _voda = 3;
} else if(_vodaM == 1){
  _voda = 2;
} if( _vodaV == 1){
  _voda = 1;
} else if( _vodaV == 0 && _vodaM== 0 ){
  _voda = 0;}

    return _voda;
 }
// void settemp() {
//     ds.requestTemp();  // первый запрос на измерение
// }

// // float gettemp() {
// //     if (ds.ready()) {         // измерения готовы по таймеру
// //         if (ds.readTemp()) {  // если чтение успешно
// //             Serial.print("temp: ");
// //             Serial.println(ds.getTemp());
// //             _termo = ds.getTemp();
// //         } else {
// //             Serial.println("read error");
// //         }

// //         ds.requestTemp();  // запрос следующего измерения
// //     } return _termo;
// // }

// // int getVlaga(){
// // _voda = analogRead(pinSensor);
// // return _voda;
// // }
// //---------------------------------------
// //     Temperature(/* args */);
// //     ~Temperature();
};

// // Temperature::Temperature(/* args */)
// // {
// // }

// // Temperature::~Temperature()
// // {
// // }


// #include <OneWire.h>

// OneWire ds(8); // Объект OneWire

// int temperature = 0; // Глобальная переменная для хранения значение температуры с датчика DS18B20

// long lastUpdateTime = 0; // Переменная для хранения времени последнего считывания с датчика
// const int TEMP_UPDATE_TIME = 1000; // Определяем периодичность проверок

// void setup(){
//   Serial.begin(9600);
// }

// void loop(){
//   detectTemperature(); // Определяем температуру от датчика DS18b20
//   Serial.println(temperature); // Выводим полученное значение температуры
//   // Т.к. переменная temperature имеет тип int, дробная часть будет просто отбрасываться
// }

// int detectTemperature(){

//   byte data[2];
//   ds.reset();
//   ds.write(0xCC);
//   ds.write(0x44);

//   if (millis() - lastUpdateTime > TEMP_UPDATE_TIME)
//   {
//     lastUpdateTime = millis();
//     ds.reset();
//     ds.write(0xCC);
//     ds.write(0xBE);
//     data[0] = ds.read();
//     data[1] = ds.read();

//     // Формируем значение
//     temperature = (data[1] << 8) + data[0]; temperature = temperature >> 4;
//   }
// }


