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

#if DEVICE == 1

#else
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
#endif

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
void ButtonRead()
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
        if (audioConnected)
        {
          audio.play(8);
        }
      }
      else if (setupGame[5] == i)   //Номер кнопки которая остановит отсчет на определеное время.
      {
        long stopTime = (setupGame[6] * 60) * 1000;
        speedTime = stopTime;
        setupGame[5] = 20;
        if (audioConnected)
        {
          audio.play(10);
        }
      }
      else if (setupGame[7] == i) //Номер кнопки замедляющий отсчет
      {
        speedTime *= setupGame[8];
        if (audioConnected)
        {
          audio.play(11);
        }
      }
      else
      {
        setupGame[0] -= setupGame[4];
        if (audioConnected)
        {
          audio.play(9);
        }
      }
      rele();
      w.MarkProcessed();
    }
  }
}

//Чтение пароля
void ReadPassword()
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
        if (setupGame[2] == 3 && audioConnected)
        {
          audio.play(5);
        }
        else if (setupGame[2] == 2 && audioConnected)
        {
          audio.play(6);
        }
        else if (setupGame[2] == 1 && audioConnected)
        {
          audio.play(7);
        }
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
      if (audioConnected)
      {
        audio.play(3);
      }
    }
    else
    {
      globalState += 2; //Завершили игру Победа
      if (audioConnected)
      {
        audio.play(4);
      }
    }
  }
}

//==============================================================
#if DEVICE == 1

#else
//Чтение данных с блютуз
String ReadFromStream(Stream &stream)
{
  String ret{};
  if (stream.available())
  {
    ret.reserve(stream.available());
  }
  while (stream.available() > 1)
  {
    ret += (char)stream.read();
  }
  return ret;
}

//Сравнения имени mac, rssi, name с указаными
bool CheckBluetoothDevice(int rssi, const String &name)
{
  Serial.print("name -> ");
  Serial.println(name);

  Serial.println("========================END===============================");
  if (name == VALID_NAME && rssi > MIN_VALID_RSSI)
  {
    return true;
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
  static unsigned long timeScan = millis();
  if (millis() - timeScan > SCAN_DELAY_MS)
  {
    Serial2.print(F("AT+SCAN1"));
    timeScan = millis();
  }

  String s = ReadFromStream(Serial2);

  int pos = s.indexOf("=") + 1;
  if (!pos)
    return false;

  Serial.println(s);

  String mac = ExtractSubstring(s, ',', pos);
  String rssi = ExtractSubstring(s, ',', pos + mac.length() + 1);
  Serial.print("rssi -> ");
  Serial.println(rssi);
  if (rssi.length() == 0)
    return false;

  String name = s.substring(pos + mac.length() + rssi.length() + 2);
  name.trim();
  if (name.length() == 0)
    return false;

  return CheckBluetoothDevice(rssi.toInt(), name);
}

bool BluetoothSerch()
{
  static bool state = false;

  if (ProcessBluetooth())
  {
    state = true;
  }
  return state;
}
#endif
//===============================================================================

//Акселерометр
void CheckAccel()
{
  static bool init = false;
  if (!init)
  {
    mpu.getAcceleration(&ax, &ay, &az);
    init = true;
  }

  //На сколько секунд ускоряем
  if (speedAccel)
  {
    if ((millis() - timeAccel) > (setupGame[12] * 1000))
    {
      speedTime = 1000;
      speedAccel = false;
    }
  }

  int16_t x, y, z;
  mpu.getAcceleration(&x, &y, &z);
  float dx = x * 1.0f - ax;
  float dy = y * 1.0f - ay;
  float dz = z * 1.0f - az;
  ax = x;
  ay = y;
  az = z;
  auto length = sqrt(dx * dx + dy * dy + dz * dz) / 1000;
  if (length > setupGame[10]) //Чувствотельность
  {
    speedTime = (int)(speedTime / setupGame[11]); //Скорость отсчета
    speedAccel = true;
    timeAccel = millis();
    if (audioConnected)
    {
      audio.play(2);
    }
  }
}

//===============================================================================
void Buzzer()
{
  tone(BUZZER_PIN, 1800);
  delay(50);
  tone(BUZZER_PIN, 150);
  delay(50);
  noTone(BUZZER_PIN);
}

//===============================================================================

//Отображение остчета времени
bool ViewZeroString()
{
  if ((millis() - setupTimeLastMillis) > speedTime)
  {
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
    Buzzer();
  }
}
//=====================================================================================//

void timerGame()
{
  ViewZeroString(); //Показываем время таймера
  ButtonRead();     //Считываем нажатие тумблеров

  if (setupGame[10] > 0)
  {
    CheckAccel();     //Акселерометр
  }

  if (setupGame[13] == 1)
  {
    if (BluetoothSerch()) //Поиск Блютуз
    {
      if (setupGame[14] == 0)
      {
        if (!ViewMenuPass)
        {
          lcd.setCursor(0, 1);
          lcd.print(F("Pass:  ????????"));
          ViewMenuPass = true;
          timeMenuPass = millis();
        }
      }
      else
      {
        globalState += 2;
      }
    }
    else
    {
      if (ViewMenuPass && (millis() - timeMenuPass) > 3000)
      {
        lcd.setCursor(0, 1);
        lcd.print(F("****************"));
        ViewMenuPass = false;
      }
    }
    if (ViewMenuPass)
    {
      ReadPassword();   //Ввод пароля
    }
  }
  else
  {
    ReadPassword();   //Ввод пароля
  }

  //Время вышло.
  if (setupGame[0] == 0)
  {
    ++globalState;
  }
}
