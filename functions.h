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

#if DEVICE == 1

#else
//LED индикация
class LedIndication {
  public:
    LedIndication() : _pin{0} {};
    void SetPin(uint8_t pin) {
      _pin = pin;
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }
    uint8_t Pin() const {
      return _pin;
    }
    boolean On() const {
      digitalWrite(_pin, HIGH);
    }
    boolean Off() const {
      digitalWrite(_pin, LOW);
    }
  private:
    uint8_t _pin;
};
LedIndication led[WIRE_PINS_COUNT_LED];
#endif

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

//LED режим капля
void LedOne(int i)
{
  if (i > 0 && i < 5 || i > 15)
  {
    ++sw;
  }
  switch (sw)
  {
    case 4: digitalWrite(led[(i - 4)].Pin(), LOW);
    case 3: digitalWrite(led[(i - 3)].Pin(), 60);
    case 2: digitalWrite(led[(i - 2)].Pin(), 125);
    case 1: digitalWrite(led[(i - 1)].Pin(), 190);
    case 0: digitalWrite(led[i].Pin(), 255); break;

    case 5: digitalWrite(led[(i - 1)].Pin(), 190);
    case 6: digitalWrite(led[(i - 2)].Pin(), 125);
    case 7: digitalWrite(led[(i - 3)].Pin(), 60);
    case 8: digitalWrite(led[(i - 4)].Pin(), LOW);
  }
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

//Чтение тумблеров
void buttonRead()
{
  //Сброс замедления времени
  if ((millis() - setupMiddleTimeMillis) > 60000)
  {
    if (setupGame[8] > 0)
    {
      --setupGame[9];
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
      if (setupGame[3] == i)  //Номер кнопки которая остановит игру с победой.
      {
        globalState += 2;
      }
      else if (setupGame[5] == i)   //Номер кнопки которая остановит отсчет на определеное время.
      {
        long stopTime = (setupGame[6] * 60) * 1000;
        speedTime = stopTime;
        setupGame[5] = 20;
      }
      else if (setupGame[7] == i) //Номер кнопки замедляющий отсчет
      {
        speedTime *= setupGame[8];
      }
      else
      {
        setupGame[0] -= setupGame[4];
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
      if (setupGame[2] > 0 && setupGame[2] < 11)
      {
        --setupGame[2];
      }
      else if (setupGame[2] == 0)
      {
        ++globalState; //Завершили игру Поражение
      }

      setupGame[0] -= 600;
      if (setupGame[0] < 3)
      {
        setupGame[0] = 2;
      }

      pass = 0;
      stringLength = 0;
      lcd.setCursor(0, 1);
      lcd.print(F("Pass:  ????????"));
    }
    else
    {
      globalState += 2; //Завершили игру Победа
    }
  }
}

//==============================================================

//Чтение данных с блютуз
String ReadFromStream(Stream &stream)
{
  String ret{};
  if (stream.available())
  {
    ret.reserve(stream.available());
  }
  while (stream.available() > 0)
  {
    ret += (char)stream.read();
  }
  return ret;
}

//Сравнения имени mac, rssi, name с указаными
bool CheckBluetoothDevice(const String &mac, int rssi, const String &name)
{
  Serial.print("name -> ");
  Serial.println(name);
  if (name == VALID_NAME && rssi > MIN_VALID_RSSI)
  {
    if (!USE_BLUETOOTH_MACS)
      return true;

    for (uint8_t i = 0; i < MACS_COUNT; ++i)
    {
      if (mac == VALID_MACS[i])
        return true;
    }
  }
  return false;
}

//Поиск в строк в данных
String ExtractSubstring(const String &s, char separator, unsigned int startIdx)
{
  auto endIdx = s.indexOf(separator, startIdx);
  if (~endIdx)
  {
    return s.substring(startIdx, endIdx);
  }
  return {};
}

//Поиск устройств
bool ProcessBluetooth()
{
  static unsigned long time = millis();
  if (millis() - time > SCAN_DELAY_MS)
  {
    Serial1.print(F("AT+SCAN1"));
    time = millis();
  }
  auto s = ReadFromStream(Serial1);
  Serial.print("ProcessBluetooth -> ");
  Serial.println(s);
  if (!s.startsWith(F("+DEV")))
    Serial.println("+DEV");
  return false;

  auto mac = ExtractSubstring(s, ',', 7);
  Serial.print("mac -> ");
  Serial.println(mac);
  if (mac.length() == 0)
    return false;

  auto rssi = ExtractSubstring(s, ',', 7 + mac.length() + 1);
  Serial.print("rssi -> ");
  Serial.println(rssi);
  if (rssi.length() == 0)
    return false;

  auto name = s.substring(7 + mac.length() + rssi.length() + 2);
  name.trim();
  Serial.print("name -> ");
  Serial.println(name);
  if (name.length() == 0)
    return false;

  return CheckBluetoothDevice(mac, rssi.toInt(), name);
}

bool ValidBluetooth()
{
  static unsigned long time = millis();
  static bool state = false;

  if (ProcessBluetooth())
  {
    state = true;
    time = millis();
  }
  else if (millis() - time > ATTEMPTS_TO_DISCONNECT * SCAN_DELAY_MS)
  {
    state = false;
  }
  return state;
}

bool BluetoothSerch()
{
  if (ValidBluetooth())
  {
    globalState += 2; //Завершили игру Победа
  }
}

void Buzzer()
{
  tone(BUZZER_PIN, 1800);
  delay(50);
  tone(BUZZER_PIN, 150);
  delay(50);
  noTone(BUZZER_PIN);
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
    if (setupGame[5] == 20)
    {
      speedTime = 1000;
    }

    /*
        if (yar > 19)
        {
          yar = 0;
        }
        LedOne(yar);
        ++yar;
    */
    BluetoothSerch(); //Поиск Блютуз
    Buzzer();
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
