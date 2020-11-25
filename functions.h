//Определение кнопки
class WireSensor {
  public:
    WireSensor() : _pin{0}, _processed{0} {};
    void SetPin(uint8_t pin) {
      _pin = pin;
      pinMode(pin, INPUT_PULLUP);
    }
    uint8_t Pin() const {
      return _pin;
    }
    void MarkProcessed() {
      _processed = 1;
    }
    uint8_t Processed() const {
      return _processed;
    }
    boolean Value() const {
      boolean _ret = ( digitalRead(_pin) && HIGH );
      return _ret;
    }
  private:
    uint8_t _pin;
    uint8_t _processed;
};
WireSensor wires[WIRE_PINS_COUNT_BUTTON];

//LED индикация
class LedIndication {
  public:
    LedIndication() : _pin{0}, _processed{0} {};
    void SetPin(uint8_t pin) {
      _pin = pin;
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }
    uint8_t Pin() const {
      return _pin;
    }
    void MarkProcessed() {
      _processed = 1;
    }
    uint8_t Processed() const {
      return _processed;
    }
    boolean Value() const {
      boolean _ret = ( digitalRead(_pin) && HIGH );
      return _ret;
    }
  private:
    uint8_t _pin;
    uint8_t _processed;
};
LedIndication led[WIRE_PINS_COUNT_LED_ONE];

//Реле
void rele()
{
  digitalWrite(RELAY_PINS, ON);
  delay(5);
  digitalWrite(RELAY_PINS, OFF);
}

//Запись данных EEPROM
void EEPROMWritelong(int address, long value)
{
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);

  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}

//Чтение данных EEPROM
long EEPROMReadlong(long address)
{
  //Read the 4 bytes from the eeprom memory.
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);

  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

//Секунды в строку (час:мин:сек)
String ConstructTimeString(unsigned long secs)
{
  uint8_t hours = secs / 3600;
  uint8_t minutes = secs / 60 - hours * 60;
  uint8_t seconds = secs % 60;

  char str[9];
  sprintf(str, "%02d", hours);
  sprintf(str + 2, ":%02d", minutes);
  sprintf(str + 5, ":%02d", seconds);
  str[8] = 0;

  return String(str);
}

//Отображение остчета времени
bool viewZeroString()
{
  if ((millis() - setupTimeLastMillis) > speedTime)
  {
    Serial.println(speedTime);
    setupGame[0] -= 1;
    lcd.setCursor(cursorZeroStr, 0);
    lcd.print(ConstructTimeString(setupGame[0]));
    setupTimeLastMillis = millis();

    //Сброс заморозки времени
    if (setupGame[6] == 20)
    {
      speedTime = 1000;
    }
  }
}

//Чтение тумблеров
void buttonRead()
{
  if ((millis() - setupMiddleTimeMillis) > 60000)
  {
    if (setupGame[9] > 0)
    {
      --setupGame[10]; 
    }
    else
    {
      speedTime = 1000;
    }
    setupMiddleTimeMillis = millis();
  }
  for (uint8_t i = 0; i < WIRE_PINS_COUNT_BUTTON; ++i) {
    auto &w = wires[i];
    if (!w.Value() && !w.Processed())
    {
      if (setupGame[4] == i)
      {
        long minusTime = (setupGame[0] * setupGame[5]) / 100;
        setupGame[0] -= minusTime;
      }
      else if (setupGame[6] == i)   //Номер кнопки которая остановит отсчет на определеное время.
      {
        long stopTime = (setupGame[7] * 60) * 1000;
        speedTime = stopTime;
        setupGame[6] = 20;
      }
      else if (setupGame[8] == i) //Номер кнопки замедляющий отсчет
      {
        speedTime *= setupGame[9];
      }
      else
      {
        long correctSpeedTime = 140;
        if (correctSpeedTime < speedTime) {
          speedTime -= correctSpeedTime;
        }
        else
        {
          speedTime = 1;
        }
      }
      rele();
      w.MarkProcessed();
    }
  }
}

//Чтение пароля
void readPassword()
{
  static uint8_t stringLength = 0;
  static long pass = 0;
  static long realPass = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if ((key != '*') && (key != '#'))
  {
    if (stringLength < 8)
    {
      switch (stringLength)
      {
        case 7: pass += (key - 48) * 3;
        case 6: pass += (key - 48) * 3;
        case 5: pass += (key - 48) * 3;
        case 4: pass += (key - 48) * 3;
        case 3: pass += (key - 48) * 3;
        case 2: pass += (key - 48) * 3;
        case 1: pass += (key - 48) * 3;
        case 0: pass += (key - 48) * 3;
      }
      lcd.setCursor(stringLength + cursorOneStr, 1);
      lcd.print(F("*"));
      ++stringLength;
    }
  }
  if (key == '*')
  {
    pass = 0;
    stringLength = 0;
    lcd.setCursor(0, 1);
    lcd.print(F("Pass:  ????????"));
  }
  if (key == '#' && pass > 0)
  {
    if (setupGame[1] != pass)
    {
      //Количество попыток ввода пароля
      if (setupGame[3] > 0 && setupGame[3] < 11)
      {
        long correctSpeedTime = setupGame[2] * 60;
        setupGame[0] -= correctSpeedTime;
        --setupGame[3];
      }
      else if (setupGame[3] == 0)
      {
        ++globalState; //Завершили игру
      }
      pass = 0;
      stringLength = 0;
      lcd.setCursor(0, 1);
      lcd.print(F("Pass:  ????????"));
    }
    else
    {
      globalState += 2; //Завершили игру
    }
  }
}

//=====================================================================================//

void timerGame()
{
  viewZeroString(); //Показываем время таймера
  buttonRead();     //Считываем нажатие тумблеров
  readPassword();   //Ввод пароля

  //Время вышло.
  if (setupGame[0] == 0)
  {
    ++globalState;
  }
}
