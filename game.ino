#include "libraries.h"
#include "const.h"
#include "functions.h"
#include "menu.h"

void setup() {

  Serial.begin(115200);

  // Иницилизация LCD
  lcd.begin();
  lcd.backlight();

  // Определение параметра подавления дребезга контактов на клавиатуре
  keypad.setDebounceTime(frequency_button);

  //Кнопки деактивации
  for (uint8_t i = 0; i < WIRE_PINS_COUNT; ++i) {
    wires[i].SetPin(WIRE_PINS[i]);
  }

  //Реле
  pinMode(RELAY_PINS, OUTPUT);
  digitalWrite(RELAY_PINS, OFF);

  showHello();
  delay(2000);

  if (EEPROM.read(0) != 255 && EEPROM.read(0) > 0)
  {
    int cellEeprom = 0;
    for (uint8_t i = 0; i < adress; ++i) {
      if (i == 0 || i == 1) {
        setupGame[i] = EEPROMReadlong(cellEeprom);
        cellEeprom += 3;
      }
      else
      {
        setupGame[i] = EEPROM.read(cellEeprom);
      }
      ++cellEeprom;
      delay(1);
    }
    globalState = 16;
    ShowSave();    //Меню сохраненные настройки
  }
  else
  {
    showTextBombTime();   //Меню установки времени игры
  }
}

void loop() {
  switch (globalState) {
    case 0: SetupBombTime(); break;           //Установка времени игры
    case 1: SetupPassword(); break;           //Ввод пароля
    case 2: SetupIncorrectPassword(); break;  //Ускорение отсчета  при вводе неверного пароля
    case 3: SetupAttempts(); break;           //Количество попыток ввода пароля
    case 4: SetupCorrectToggle(); break;      //Номер кнопки останавливающей таймер ( 1-10 )
    case 5: SetupIncorrectToogle(); break;    //Если нажимаем 65-значит время убавится на  65 процентов от оставшегося
    case 6: SetupStopToogle(); break;         //Номер кнопки замедляющий отсчет
    case 7: SetupStopTime(); break;           //Заморозка таймера
    case 8: SetupSlomoToogle(); break;        //Номер кнопки замедляющий отсчет
    case 9: SetupSlomoTime(); break;          //Во сколько раз медленее  будет отсчет.
    case 10: SetupTimeEfect(); break;         //Сколько минут будет действовать этот эффект.
    case 11: SetupSensitivity(); break;       //Чуствительность акселерометра.
    case 12: SetupSensitivityTime(); break;   //Во сколько раз должен ускориться отсчет при срабатывании модуля.
    case 13: SetupSensitivityEfect(); break;  //Отрезок времени для ускорения.
    case 14: SetupPoint(); break;             //Активация блютуза.
    case 15: SetupPointMenu(); break;         //Выбор параметров блютуз
    case 16: SetupSave(); break;              //Запрос восстановление данных
    case 17: SetupAnyPress(); break;          //Ожидания старта
    case 18: StartGame(); break;              //Начало игры
  }
  //if (globalState < 12) ledWave();
}
