#include <max6675.h> // Подключаем библиотеку для работы с термодатчиком MAX6675
#include <LiquidCrystal_I2C.h> // Подключаем библиотеку для работы с LCD дисплеем по шине I2C
#include <Wire.h> // Подключаем библиотеку для работы с шиной I2C

#define S0 10 // Управляющий Pin 0 (фиолетовый) 
#define S1 11 // Управляющий Pin 1 (коричневый) 
#define S2 12 // Управляющий Pin 2 (коричневый) 
#define S3 13 // Управляющий Pin 3 (фиолетовый) 
#define SIG A0 // Pin для сччитывания напряжения (синий)
#define thermoDO 2
#define thermoCS 3
#define thermoCLK 4
#define vccPin 5
#define gndPin 6
#define relPin 9 //Управляющий Pin для реле

LiquidCrystal_I2C lcd1(0x27, 20, 4); // Показывает значение напряжения на аккумуляторе
LiquidCrystal_I2C lcd2(0x26, 20, 4); // Показывает температуру
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup()
{
    //Назначаем уровни напряжения для питания и земли
    pinMode(vccPin, OUTPUT);
    digitalWrite(vccPin, HIGH);
    pinMode(gndPin, OUTPUT);
    digitalWrite(gndPin, LOW);

    lcd1.init(); // Инициируем работу с дисплеем LCD 1
    lcd2.init(); // Инициируем работу с дисплеем LCD 2
    lcd1.backlight(); // Включаем подсветку дисплея LCD 1
    lcd2.backlight(); // Включаем подсветку дисплея LCD 2

    //Назначаем уровни напряжения для управляющих пинов мультиплексора
    pinMode(S0, OUTPUT); 
    pinMode(S1, OUTPUT); 
    pinMode(S2, OUTPUT); 
    pinMode(S3, OUTPUT);   
    digitalWrite(S0, LOW);
    digitalWrite(S1, LOW);
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
}

void loop()
{
  //Вывод напряжения на дисплей lcd1
  for(int i = 0; i < 12; i++)
  { 
    if (i == 3)
    {
      lcd1.setCursor(0, 1);
    }
    if (i == 6)
    {
      lcd1.setCursor(0, 2);
    }
    if (i == 9)
    {
      lcd1.setCursor(0, 3);
    }
    lcd1.print(i + 1);
    lcd1.print("-");
    lcd1.print(readMux(i), 1);
    lcd1.print(" ");
    if(readMux(i) < 1.7)
    {
        digitalWrite(relPin, HIGH);
    }
  }
  
  if(readTemp() > 39.00)
  {
    lcd2.clear();
    lcd2.print("t > 40");
    digitalWrite(relPin, HIGH);
  }
  else
  {
    lcd2.setCursor(0, 1);
    lcd2.print("t = ");
    lcd2.print(readTemp());
  }
  delay(10000);
}

double readMux(int channel) //Функция возвращающая значения напряжения
{
  int controlPin[] = {S0, S1, S2, S3};
  //Задаём каналы мультиплексора
  int muxChannel[12][4]={
    {0,0,0,0},
    {1,0,0,0},
    {0,1,0,0},
    {1,1,0,0},
    {0,0,1,0},
    {1,0,1,0},
    {0,1,1,0},
    {1,1,1,0},
    {0,0,0,1},
    {1,0,0,1},
    {0,1,0,1},
    {1,1,0,1},
  };

  for(int i = 0; i < 4; i++)
  {
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
  double voltage = (double)(analogRead(SIG) * 5.0) / 1024; //Получаем значение напряжения
  return voltage;
}

double readTemp()//Функция для определения температуры
{
  double T = thermocouple.readCelsius(); //Получаем значение температуры в градусах Цельсия
  return T;
}