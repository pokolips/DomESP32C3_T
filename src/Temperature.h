#pragma once

#include <GyverDS18.h>

GyverDS18Single ds(4);  // пин 4

class Temperature
{
private:
  float _termo = 10;
  int _voda = 0;
  int pinSensor = 1;
public:

void settemp() {
    ds.requestTemp();  // первый запрос на измерение
}

float gettemp() {
    if (ds.ready()) {         // измерения готовы по таймеру
        if (ds.readTemp()) {  // если чтение успешно
            Serial.print("temp: ");
            Serial.println(ds.getTemp());
            _termo = ds.getTemp();
        } else {
            Serial.println("read error");
        }

        ds.requestTemp();  // запрос следующего измерения
    } return _termo;
}

int getVlaga(){
_voda = analogRead(pinSensor);
return _voda;
}
//     Temperature(/* args */);
//     ~Temperature();
 };

// Temperature::Temperature(/* args */)
// {
// }

// Temperature::~Temperature()
// {
// }





