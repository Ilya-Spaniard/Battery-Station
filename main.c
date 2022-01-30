#include <Wire.h>                    // Подключаем библиотеку для работы с шиной I2C
#include <LiquidCrystal_I2C.h>       // Подключаем библиотеку для работы с LCD дисплеем по шине I2C
LiquidCrystal_I2C lcd1(0x27, 20, 4); // Показывает значение напряжения на аккумуляторе
LiquidCrystal_I2C lcd1(0x26, 20, 4); // Показывает значение напряжение на аккумуляторе + температуру

void setup()
{
    lcd1.init();      // Инициируем работу с дисплеем LCD 1
    lcd2.init();      // Инициируем работу с дисплеем LCD 2
    lcd1.backlight(); // Включаем подсветку дисплея LCD 1
    lcd1.print("Adress 0x27");
    lcd2.backlight(); // Включаем подсветку дисплея LCD 2
    lcd2.print("Adress 0x26");
}

void loop()
{
}