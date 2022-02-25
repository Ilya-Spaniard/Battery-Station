#include <max6675.h> // Подключаем библиотеку для работы с термодатчиком MAX6675
#include <LiquidCrystal_I2C.h> // Подключаем библиотеку для работы с LCD дисплеем по шине I2C
#include <Wire.h> // Подключаем библиотеку для работы с шиной I2C

LiquidCrystal_I2C lcd1(0x27, 20, 4); // Показывает значение напряжения на аккумуляторе
LiquidCrystal_I2C lcd2(0x26, 20, 4); // Показывает значение напряжение на аккумуляторе + температуру

int thermoDO = 2; //он же SO
int thermoCS = 3;
int thermoCLK = 4; //он же SCK
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 5; //пин для питания
int gndPin = 6; //пин для земли

void setup()
{

    pinMode(vccPin, OUTPUT);
    digitalWrite(vccPin, HIGH);

    pinMode(gndPin, OUTPUT);
    digitalWrite(gndPin, LOW);

    lcd1.init(); // Инициируем работу с дисплеем LCD 1
    lcd2.init(); // Инициируем работу с дисплеем LCD 2
    lcd1.backlight(); // Включаем подсветку дисплея LCD 1
    lcd2.backlight(); // Включаем подсветку дисплея LCD 2
}

void loop()
{

    double T = thermocouple.readCelsius();
    float voltage = (float)(analogRead(0) * 5.0) / 1024;
    lcd2.print(voltage);

    if (T >= 39.50)
    {
        lcd1.print("Attention!");
        lcd1.setCursor(0, 1);
        lcd1.print("Temp. exceeded!");
        lcd1.setCursor(0, 3);
        lcd1.print(T);
    }

    delay(1000);
}