#include "libraries.h"
#include "const.h"
#include "functions.h"
#include "menu.h"

void setup()
{

  Serial.begin(115200);
  Serial1.begin(9600); //Плеер

  //Акселерометр
  mpu.initialize();
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);

  // Иницилизация LCD
  lcd.begin();
  lcd.backlight();

#if DEVICE == 1

#else
  //Определение блютуз
  Serial2.begin(BLUETOOTH_BAUDRATE);
  Serial2.print("AT+HOSTEN1");
  delay(100);
  if (!ReadFromStream(Serial2).startsWith(F("+OK")))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("Bluetooth failed"));
    lcd.setCursor(4, 1);
    lcd.print(F("Check it"));

    while (true) {}
  }
  Serial2.print("AT+POWR0");
#endif

  // Определение параметра подавления дребезга контактов на клавиатуре
  keypad.setDebounceTime(frequency_button);

  //Кнопки деактивации
  for (uint8_t i = 0; i < WIRE_PINS_COUNT_BUTTON; ++i)
  {
    wires[i].SetPin(WIRE_PINS_BUTTON[i]);
  }

#if DEVICE == 1

#else
  //LED
  for (uint8_t i = 0; i < WIRE_PINS_COUNT_LED; ++i)
  {
    led[i].SetPin(WIRE_PINS_LED[i]);
  }
#endif

  showHello();  //Запуск меню приветствия.

  //Плеер
  audio.setTimeOut(1000);
  if (!audio.begin(Serial1)) {
    audioConnected = 0;
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Audio failed");
    lcd.setCursor(0, 1);
    lcd.print("Check wires/card");
    delay(3000);
  } else {
    audio.setTimeOut(5000);
    delay(1000);
    audioConnected = 1;
    audio.volume(AUDIO_VOLUME);
    delay(1000);
  }

  //Реле
  pinMode(RELAY_PINS, OUTPUT);
  digitalWrite(RELAY_PINS, OFF);
  pinMode(RELAY_GAME_OVER, OUTPUT);
  digitalWrite(RELAY_GAME_OVER, OFF);
 
  //Buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  Serial2.print("AT+RST");
  delay(1200);
  ReadFromStream(Serial2);
  Serial.println("Bluetooth is ready");

  if (EEPROM.read(0) != 255 && EEPROM.read(0) > 0)
  {
    int cellEeprom = 0;
    for (uint8_t i = 0; i < adress; ++i)
    {
      if (i == 0 || i == 1 || i == (adress - 1)) {
        setupGame[i] = EEPROMReadlong(cellEeprom);
        cellEeprom += 3;
      }
      else
      {
        setupGame[i] = EEPROM.read(cellEeprom);
      }

      Serial.println("====LOAD====");
      Serial.println(setupGame[i]);

      ++cellEeprom;
      delay(1);
    }

    //Чувствительность акселерометра
    acsselButton = setupGame[10];

    globalState = 15;
    ShowSave();    //Меню сохраненные настройки
  }
  else
  {
    showTextBombTime();   //Меню установки времени игры
  }
}

void loop()
{
  switch (globalState)
  {
    case 0: SetupBombTime(); break;           //Установка времени игры
    case 1: SetupPassword(); break;           //Ввод пароля
    case 2: SetupAttempts(); break;           //Количество попыток ввода пароля
    case 3: SetupCorrectToggle(); break;      //Номер кнопки останавливающей таймер
    case 4: SetupIncorrectToogle(); break;    //Сколько минут отнять
    case 5: SetupStopToogle(); break;         //Номер кнопки замедляющий отсчет
    case 6: SetupStopTime(); break;           //Заморозка таймера
    case 7: SetupSlomoToogle(); break;        //Номер кнопки замедляющий отсчет
    case 8: SetupSlomoTime(); break;          //Во сколько раз медленее будет отсчет.
    case 9: SetupTimeEfect(); break;          //Сколько минут будет действовать этот эффект.
    case 10: SetupSensitivity(); break;       //Чуствительность акселерометра.
    case 11: SetupSensitivityTime(); break;   //Во сколько раз должен ускориться отсчет при срабатывании модуля.
    case 12: SetupSensitivityEfect(); break;  //Отрезок времени для ускорения.
    case 13: SetupPoint(); break;             //Активация блютуза.
    case 14: SetupPointMenu(); break;         //Выбор параметров блютуз
    case 15: SetupSave(); break;              //Запрос восстановление данных
    case 16: SetupAnyPress(); break;          //Ожидания старта
    case 17: timerGame(); break;              //Начало игры
    case 18: GameOver(); break;               //Конец игры Поражение
    case 19: GameWin(); break;                //Конец игры Победа
  }
  if (globalState == 17) LedOne();
}
