//Воспроизведение треков
void PlaySound(byte number)
{
  if (!audioConnected)
    return;
  //  if((millis() - timeWaitPlay) > 200)
  //  {
  audio.playMp3Folder(number);
  timeWaitPlay = millis();
  //  }
}

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
    uint8_t Value() {
      if (digitalRead(_pin) == LOW && !_connect)
      {
        if (_frequency > _frequency_button)
        {
          _connect = true;
          _frequency = 0;
          return true;
        }
      }
      if (digitalRead(_pin) == HIGH)
      {
        _connect = false;
        _frequency = 0;
      }
      ++_frequency;
      return false;
    }
  private:
    uint8_t _pin;
    uint8_t _processed;
    uint8_t _frequency_button = 20;
    uint8_t _frequency = 0;
    bool _connect = false;
};
WireSensor wires[WIRE_PINS_COUNT_BUTTON];

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

  if (hours == 1 && minutes == 0 && seconds == 0 && !timeMin60)
  {
    PlaySound(TREK16);
    timeMin60 = true;
    DEBUG("60 min -> trek: 16");
  }
  else if (hours == 0 && minutes == 50 && seconds == 0 && !timeMin50)
  {
    PlaySound(TREK17);
    timeMin50 = true;
    DEBUG("50 min -> trek: 17");
  }
  else if (hours == 0 && minutes == 40 && seconds == 0 && !timeMin40)
  {
    PlaySound(TREK18);
    bool timeMin40 = true;
    DEBUG("40 min -> trek: 18");
  }
  else if (hours == 0 && minutes == 30 && seconds == 0 && !timeMin30)
  {
    PlaySound(TREK19);
    bool timeMin30 = true;
    DEBUG("30 min -> trek: 19");
  }
  else if (hours == 0 && minutes == 20 && seconds == 0 && !timeMin20)
  {
    PlaySound(TREK20);
    bool timeMin20 = true;
    DEBUG("20 min -> trek: 20");
  }
  else if (hours == 0 && minutes == 15 && seconds == 0 && !timeMin15)
  {
    PlaySound(TREK21);
    bool timeMin15 = true;
    DEBUG("15 min -> trek: 21");
  }
  else if (hours == 0 && minutes == 10 && seconds == 0 && !timeMin10)
  {
    PlaySound(TREK22);
    bool timeMin10 = true;
    DEBUG("10 min -> trek: 22");
  }
  else if (hours == 0 && minutes == 5 && seconds == 0 && !timeMin5)
  {
    PlaySound(TREK23);
    bool timeMin5 = true;
    DEBUG("5 min -> trek: 23");
  }
  else if (hours == 0 && minutes == 4 && seconds == 0 && !timeMin4)
  {
    PlaySound(TREK24);
    bool timeMin4 = true;
    DEBUG("4 min -> trek: 24");
  }
  else if (hours == 0 && minutes == 3 && seconds == 0 && !timeMin3)
  {
    PlaySound(TREK25);
    bool timeMin3 = true;
    DEBUG("3 min -> trek: 25");
  }
  else if (hours == 0 && minutes == 2 && seconds == 0 && !timeMin2)
  {
    PlaySound(TREK26);
    bool timeMin2 = true;
    DEBUG("2 min -> trek: 26");
  }
  else if (hours == 0 && minutes == 1 && seconds == 0 && !timeMin1)
  {
    PlaySound(TREK27);
    bool timeMin1 = true;
    DEBUG("1 min -> trek: 27");
  }
  else if (hours == 0 && minutes == 0 && seconds == 30 && !timeSec30)
  {
    PlaySound(TREK28);
    bool timeSec30 = true;
    DEBUG("30 sec -> trek: 28");
  }
  else if (hours == 0 && minutes == 0 && seconds == 20 && !timeSec20)
  {
    PlaySound(TREK29);
    bool timeSec20 = true;
    DEBUG("20 sec -> trek: 29");
  }
  else if (hours == 0 && minutes == 0 && seconds == 15 && !timeSec15)
  {
    PlaySound(TREK30);
    bool timeSec15 = true;
    DEBUG("15 sec -> trek: 30");
  }
  else if (hours == 0 && minutes == 0 && seconds == 10 && !timeSec10)
  {
    PlaySound(TREK31);
    bool timeSec10 = true;
    DEBUG("10 sec -> trek: 31");
  }
  else if (hours == 0 && minutes == 0 && seconds == 5 && !timeSec5)
  {
    PlaySound(TREK32);
    bool timeSec5 = true;
    DEBUG("5 sec -> trek: 32");
  }

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
  for (uint8_t i = 0; i < (WIRE_PINS_COUNT_BUTTON - 3); ++i) {
    auto &w = wires[i];
    if (w.Value() && !w.Processed())
    {
      if (setupGame[3] == i)  //Номер кнопки которая остановит игру с победой.
      {
        PlaySound(TREK33);
        DEBUG("trek: 33");
        globalState += 2;
        DEBUG("Button");
      }
      else if (setupGame[5] == i) //Номер кнопки которая остановит отсчет на определеное время.
      {
        long stopTime = (setupGame[6] * 60) * 1000;
        speedTime = stopTime;
        setupGame[5] = 20;
        PlaySound(TREK10);
        DEBUG("trek: 10");
      }
      else if (setupGame[7] == i) //Номер кнопки замедляющий отсчет
      {
        speedTime *= setupGame[8];
        PlaySound(TREK11);
        DEBUG("trek: 11");
      }
      else  //Отнимаем определенное количество времени
      {
        if (setupGame[0] >  setupGame[4])
        {
          setupGame[0] -= setupGame[4];
        }
        else
        {
          setupGame[0] = 0;
        }
        PlaySound(TREK9);
        DEBUG("trek: 9");
      }
      rele();
      w.MarkProcessed();
    }
  }

  if (wires[10].Value() && wires[11].Value()) //Левая и правая кнопка
  {
    acsselButton = (int)(setupGame[10] + (setupGame[10] * 1.3));
  }
  else
  {
    acsselButton = setupGame[10];
  }

  if (wires[12].Value()) //Ключ
  {
    PlaySound(TREK33);
    DEBUG("trek: 33");
    globalState += 2;
    DEBUG("Key");
  }
}

//Чтение пароля
bool ReadPassword(bool writePass = true)
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
      lcd.print(key);
      ++stringLength;
    }
  }
  if (key == '*' || !writePass)
  {
    pass = 0;
    stringLength = 0;
    lcd.setCursor(0, 1);
    lcd.print(F("Pass:  00000000 "));
  }
  if (key == '#' && pass > 0)
  {
    if (setupGame[1] != pass)
    {
      //Количество попыток ввода пароля
      if (setupGame[2] > 0 && setupGame[2] < 11)
      {
        --setupGame[2];
        if (setupGame[2] == 3)  //3 попытки ввода пароля
        {
          PlaySound(TREK5);
          DEBUG("trek: 5");
        }
        else if (setupGame[2] == 2) //2 попытки ввода пароля
        {
          PlaySound(TREK6);
          DEBUG("trek: 6");
        }
        else if (setupGame[2] == 1) //1 попытки ввода пароля
        {
          PlaySound(TREK7);
          DEBUG("trek: 7");
        }
      }
      else if (setupGame[2] == 0)
      {
        ++globalState; //Завершили игру Поражение
      }
      else
      {
        PlaySound(TREK3);
        DEBUG("trek: 3");
      }

      if (setupGame[0] > 600)
      {
        setupGame[0] -= 600;
      }
      else
      {
        setupGame[0] = 2;
      }

      pass = 0;
      stringLength = 0;
      lcd.setCursor(0, 1);
      lcd.print(F("Pass:  00000000 "));

    }
    else
    {
      globalState += 2; //Завершили игру Победа
      DEBUG("Password");
      PlaySound(TREK4);
      DEBUG("trek: 4");
    }
  }
}

//==============================================================
//Чтение данных с блютуз
String ReadFromStream(Stream & stream)
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

//Поиск в строк в данных
String ExtractSubstring(const String & s, char separator, unsigned int startIdx)
{
  auto endIdx = s.indexOf(separator, startIdx);
  if (~endIdx)
  {
    return s.substring(startIdx, endIdx);
  }
  return {};
}

//Поиск устройств
bool BluetoothSerch()
{
  DEBUG("BluetoothSerch1");
  if ((millis() - timeScan) > SCAN_DELAY_MS)
  {
    Serial2.print(F("AT+SCAN1"));
    DEBUG("BluetoothSerch2");
    timeScan = millis();
    timeReadScan = millis();
  }

  if ((millis() - timeReadScan) > 10)
  {
    DEBUG("BluetoothSerch3");
    timeReadScan = millis();
    String s = ReadFromStream(Serial2);

    int pos = s.indexOf("=") + 1;
    if (!pos)return false;

    if ((millis() - startBluetoothtMillis) < 3000) {
      return false;
    }

    String mac = ExtractSubstring(s, ',', pos);
    String rssi = ExtractSubstring(s, ',', pos + mac.length() + 1);
    if (rssi.length() == 0)
      return false;

    String name = s.substring(pos + mac.length() + rssi.length() + 2);
    name.trim();
    if (name.length() == 0)
      return false;

    if (name == VALID_NAME && (int)&rssi > MIN_VALID_RSSI)
    {
      if (!ViewSetupPass) //Ввод пароля блютуз
      {
        lcd.setCursor(0, 1);
        lcd.print(F("Pass:  00000000 "));
        ViewSetupPass = true;
        PlaySound(TREK12);
        DEBUG("trek: 12");
      }
      timePass = millis();
      return true;
    }

    if (name == VALID_NAME_NETRAL && (int)&rssi > MIN_VALID_RSSI)
    {
      if (!ViewMenuPass)  //Вывод пароля блютуз
      {
        lcd.setCursor(0, 1);
        lcd.print(F("Pass:  00000000 "));
        lcd.setCursor(7, 1);
        lcd.print(setupGame[15]);
        PlaySound(TREK13);
        DEBUG("trek: 13");
      }

      ViewMenuPass = true;
      timePass = millis();
    }
  }
  return false;
}

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
  if (length > acsselButton) //Чувствотельность
  {
    speedTime = (int)(speedTime / setupGame[11]); //Скорость отсчета
    speedAccel = true;
    timeAccel = millis();
    if ((millis() - playAccel) > 2000)
    {
      PlaySound(TREK2);
      DEBUG("trek: 2");
      playAccel = millis();
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
void ViewZeroString()
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
    Buzzer();
  }
}

//===================================================================================

void timerGame()
{
  ViewZeroString(); //Показываем время таймера
  ButtonRead();     //Считываем нажатие тумблеров

  if (setupGame[10] > 0)
  {
    CheckAccel();     //Акселерометр
  }

  if (setupGame[13] == 0)
  {
    ReadPassword();   //Ввод пароля
  }
  else
  {
    if (BluetoothSerch()) //Поиск Блютуз
    {
      if (setupGame[14] == 0)
      {
        globalState += 2;
        DEBUG("Bluetooth POINT_BOMB");
      }
      else
      {
        ReadPassword();   //Ввод пароля
      }
    }
    else
    {
      if (ViewSetupPass || ViewMenuPass)
      {
        if ((millis() - timePass) > (SCAN_DELAY_MS + 1000))
        {
          lcd.setCursor(0, 1);
          lcd.print(F("****************"));
          ViewSetupPass = false;
          ViewMenuPass = false;
          ReadPassword(false);
        }
        else if (ViewSetupPass)
        {
          ReadPassword();
        }
      }
    }
  }

  //Время вышло.
  if (setupGame[0] == 0)
  {
    ++globalState;
  }
}
