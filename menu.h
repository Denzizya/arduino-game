//Приветствие
void showHello() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello game!");
}

//Установка времени игры
void showTextBombTime()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Bomb time, min:"));
  cursorOneStr = 5;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("00:00"));
  lcd.setCursor(cursorOneStr, 1);
}

//Ввод пароля
void ShowPassword()
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print(F("Password:"));
  cursorOneStr = 4;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("00000000"));
  lcd.setCursor(cursorOneStr, 1);
}

//Ускорение отсчета  при вводе неверного пароля
ShowIncorrectPassword()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Incorrect Pass:"));
  cursorOneStr = 7;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("00"));
  lcd.setCursor(cursorOneStr, 1);
}

//Количество попыток ввода пароля
void ShowAttempts()
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print(F("Attempts:"));
  cursorOneStr = 7;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("00"));
  lcd.setCursor(cursorOneStr, 1);
}

//Номер кнопки останавливающей таймер ( 1-10 )
void ShowCorrectToggle()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Correct toggle:"));
  cursorOneStr = 7;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("_"));
  lcd.setCursor(cursorOneStr, 1);
  setupGame[globalState] = 100;
}

//Если нажимаем 65-значит время убавится на  65 процентов от оставшегося
void ShowIncorrectToogle()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("IncorrectToogle:"));
  cursorOneStr = 0;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("   time   =   00"));
  lcd.setCursor(cursorOneStr, 1);
}

//Номер кнопки замедляющий отсчет
void ShowStopToogle()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print(F("Stop toogle:"));
  cursorOneStr = 7;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("_"));
  lcd.setCursor(cursorOneStr, 1);
  setupGame[globalState] = 100;
}

//Заморозка таймера
void ShowStopTime()
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print(F("Stop time:"));
  cursorOneStr = 7;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("00"));
  lcd.setCursor(cursorOneStr, 1);
}

//Номер кнопки замедляющий отсчет
void ShowSlomoToogle()
{
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(F("Slomo toogle:"));
  cursorOneStr = 7;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("_"));
  lcd.setCursor(cursorOneStr, 1);
  setupGame[globalState] = 100;
}

//Во сколько раз медленее  будет отсчет.
void ShowSlomoTime()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print(F("Slomo time:"));
  cursorOneStr = 7;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("00"));
  lcd.setCursor(cursorOneStr, 1);
}

//Сколько минут будет действовать этот эффект.
void ShowTimeEfect()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print(F("Time effect:"));
  cursorOneStr = 7;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("00"));
  lcd.setCursor(cursorOneStr, 1);
}

//Чуствительность акселеометра.
void ShowSensitivity()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print(F("Sensitivity:"));
  cursorOneStr = 7;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("0"));
  lcd.setCursor(cursorOneStr, 1);
}

//Во сколько раз должен ускориться отсчет при срабатывании модуля.
void ShowSensitivityTime()
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print(F("Set time:"));
  cursorOneStr = 7;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("00"));
  lcd.setCursor(cursorOneStr, 1);
}

//Отрезок времени для ускорения.
void ShowSensitivityEfect()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("TIME ( sec ) :"));
  cursorOneStr = 0;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("      =    00"));
  lcd.setCursor(cursorOneStr, 1);
}

//Включение блютуз.
void ShowPoint()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Point:"));
  lcd.setCursor(0, 1);
  lcd.print(F("* no       # yes"));
}

//Сохраненные настройки
void ShowSave()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Play again?  --*"));
  lcd.setCursor(0, 1);
  lcd.print(F("New game.    --#"));
}

//Выбор параметров блютуз
void ShowPointMenu()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Password:   *"));
  lcd.setCursor(0, 1);
  lcd.print(F("Inactive:   #"));
}

//Ожидания старта
void ShowAnyPress()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Press any"));
  lcd.setCursor(0, 1);
  lcd.print(F("button please..."));
}
//=================================================================================================================//

//Установить таймер
void SetupBombTime()
{
  static uint8_t stringLength = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if ((key != '*') && (key != '#'))
  {
    if (stringLength < 5)
    {
      if (stringLength == 0)
      {
        timeStringHour += (key - 48) * 10;
      }
      if (stringLength == 1)
      {
        timeStringHour += (key - 48);
      }
      if (stringLength == 2)
      {
        ++stringLength;
      }
      if (stringLength == 3)
      {
        timeStringMin += (key - 48) * 10;
      }
      if (stringLength == 4)
      {
        timeStringMin += (key - 48);
      }
      lcd.setCursor(stringLength + cursorOneStr, 1);
      lcd.print(key);
      ++stringLength;
    }
  }
  if (key == '*')
  {
    stringLength = 0;
    timeStringHour = 0;
    timeStringMin = 0;
    lcd.setCursor(cursorOneStr, 1);
    lcd.print(F("00:00"));
  }
  if ((key == '#') && ((timeStringHour > 0) || (timeStringMin > 0)))
  {
    long gameTimeSec = timeStringHour * 60 + timeStringMin;
    setupGame[globalState] = gameTimeSec * 1000;
    ++globalState;
    ShowPassword();
  }
}

//Установка пароля
void SetupPassword()
{
  static uint8_t stringLength = 0;

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
        case 7: setupGame[globalState] += (key - 48) * 3;
        case 6: setupGame[globalState] += (key - 48) * 3;
        case 5: setupGame[globalState] += (key - 48) * 3;
        case 4: setupGame[globalState] += (key - 48) * 3;
        case 3: setupGame[globalState] += (key - 48) * 3;
        case 2: setupGame[globalState] += (key - 48) * 3;
        case 1: setupGame[globalState] += (key - 48) * 3;
        case 0: setupGame[globalState] += (key - 48) * 3;
      }
      lcd.setCursor(stringLength + cursorOneStr, 1);
      lcd.print(key);
      ++stringLength;
    }
  }
  if (key == '*')
  {
    setupGame[globalState] = 0;
    stringLength = 0;
    lcd.setCursor(cursorOneStr, 1);
    lcd.print(F("00000000"));
  }
  if (key == '#' && setupGame[globalState] > 0)
  {
    ++globalState;
    ShowIncorrectPassword();
  }
}

//Установка пароля
void SetupIncorrectPassword()
{
  static uint8_t stringLength = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if ((key != '*') && (key != '#'))
  {
    if (stringLength < 2)
    {
      if (stringLength == 0) setupGame[globalState] = (key - 48) * 10;
      if (stringLength == 1) setupGame[globalState] += (key - 48);
      lcd.setCursor(stringLength + cursorOneStr, 1);
      lcd.print(key);
      ++stringLength;
    }
  }
  if (key == '*')
  {
    setupGame[globalState] = 0;
    stringLength = 0;
    lcd.setCursor(cursorOneStr, 1);
    lcd.print(F("00"));
  }
  if (key == '#' && setupGame[globalState] > 0)
  {
    ++globalState;
    ShowAttempts();
  }
}

//Количество попыток ввода пароля
void SetupAttempts()
{
  static uint8_t stringLength = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if ((key != '*') && (key != '#'))
  {
    if (stringLength < 2)
    {
      if (stringLength == 0) setupGame[globalState] = (key - 48) * 10;
      if (stringLength == 1) setupGame[globalState] += (key - 48);
      lcd.setCursor(stringLength + cursorOneStr, 1);
      lcd.print(key);
      ++stringLength;
    }
  }
  if (key == '*')
  {
    setupGame[globalState] = 0;
    stringLength = 0;
    lcd.setCursor(cursorOneStr, 1);
    lcd.print(F("00"));
  }
  if (key == '#')
  {
    if (setupGame[globalState] > 10)
    {
      setupGame[globalState] = 0;
      stringLength = 0;
      lcd.setCursor(cursorOneStr, 1);
      lcd.print(F("00"));
    }
    else
    {
      ++globalState;
      ShowCorrectToggle();
    }
  }
}

//Номер кнопки останавливающей таймер ( 1-10 )
void SetupCorrectToggle()
{
  for (uint8_t i = 0; i < WIRE_PINS_COUNT; ++i) {
    auto &w = wires[i];
    if (!w.Value()) {
      setupGame[globalState] = i;
      lcd.setCursor(cursorOneStr, 1);
      lcd.print(setupGame[globalState]);
      rele();
    }
  }
  char key = keypad.getKey();
  if (key == '#' && setupGame[globalState] < 100)
  {
    ++globalState;
    ShowIncorrectToogle();
    rele();
  }
}

//Если нажимаем 65-значит время убавится на  65 процентов от оставшегося
void SetupIncorrectToogle()
{
  static uint8_t stringLength = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if ((key != '*') && (key != '#'))
  {
    if (stringLength < 2)
    {
      if (stringLength == 0) setupGame[globalState] = (key - 48) * 10;
      if (stringLength == 1) setupGame[globalState] += (key - 48);
      lcd.setCursor(stringLength + 14, 1);
      lcd.print(key);
      ++stringLength;
    }
  }
  if (key == '*')
  {
    setupGame[globalState] = 0;
    stringLength = 0;
    lcd.setCursor(cursorOneStr, 1);
    lcd.print(F("   time   =   00"));
  }
  if (key == '#')
  {
    ++globalState;
    ShowStopToogle();
  }
}

//Номер кнопки которая остановит отсчет на определеное время.
void SetupStopToogle()
{
  for (uint8_t i = 0; i < WIRE_PINS_COUNT; ++i) {
    auto &w = wires[i];
    if (!w.Value() && setupGame[4] != i) {
      setupGame[globalState] = i;
      lcd.setCursor(cursorOneStr, 1);
      lcd.print(setupGame[globalState]);
      rele();
    }
  }
  char key = keypad.getKey();
  if (key == '#' && setupGame[globalState] < 100)
  {
    ++globalState;
    ShowStopTime();
    rele();
  }
}

//Заморозка времени в минутах.
void SetupStopTime()
{
  static uint8_t stringLength = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if ((key != '*') && (key != '#'))
  {
    if (stringLength < 2)
    {
      if (stringLength == 0) setupGame[globalState] = (key - 48) * 10;
      if (stringLength == 1) setupGame[globalState] += (key - 48);
      lcd.setCursor(stringLength + cursorOneStr, 1);
      lcd.print(key);
      ++stringLength;
    }
  }
  if (key == '*')
  {
    setupGame[globalState] = 0;
    stringLength = 0;
    lcd.setCursor(cursorOneStr, 1);
    lcd.print(F("00"));
  }
  if (key == '#')
  {
    if (setupGame[globalState] > 99)
    {
      setupGame[globalState] = 0;
      stringLength = 0;
      lcd.setCursor(cursorOneStr, 1);
      lcd.print(F("00"));
    }
    else
    {
      ++globalState;
      ShowSlomoToogle();
    }
  }
}

//Номер кнопки замедляющий отсчет
void SetupSlomoToogle()
{
  for (uint8_t i = 0; i < WIRE_PINS_COUNT; ++i) {
    auto &w = wires[i];
    if (!w.Value() && setupGame[4] != i && setupGame[6] != i) {
      setupGame[globalState] = i;
      lcd.setCursor(cursorOneStr, 1);
      lcd.print(setupGame[globalState]);
      rele();
    }
  }
  char key = keypad.getKey();
  if (key == '#' && setupGame[globalState] < 100)
  {
    ++globalState;
    ShowSlomoTime();
    rele();
  }
}

//Во сколько раз медленее будет отсчет.
void SetupSlomoTime()
{
  static uint8_t stringLength = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if ((key != '*') && (key != '#'))
  {
    if (stringLength < 2)
    {
      if (stringLength == 0) setupGame[globalState] = (key - 48) * 10;
      if (stringLength == 1) setupGame[globalState] += (key - 48);
      lcd.setCursor(stringLength + cursorOneStr, 1);
      lcd.print(key);
      ++stringLength;
    }
  }
  if (key == '*')
  {
    setupGame[globalState] = 0;
    stringLength = 0;
    lcd.setCursor(cursorOneStr, 1);
    lcd.print(F("00"));
  }
  if (key == '#')
  {
    ++globalState;
    ShowTimeEfect();
  }
}

//Сколько минут будет действовать этот эффект.
void SetupTimeEfect()
{
  static uint8_t stringLength = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if ((key != '*') && (key != '#'))
  {
    if (stringLength < 2)
    {
      if (stringLength == 0) setupGame[globalState] = (key - 48) * 10;
      if (stringLength == 1) setupGame[globalState] += (key - 48);
      lcd.setCursor(stringLength + cursorOneStr, 1);
      lcd.print(key);
      ++stringLength;
    }
  }
  if (key == '*')
  {
    setupGame[globalState] = 0;
    stringLength = 0;
    lcd.setCursor(cursorOneStr, 1);
    lcd.print(F("00"));
  }
  if (key == '#')
  {
    ++globalState;
    ShowSensitivity();
  }
}

//Чуствительность акселеометра. Где ноль модуль не активен и 9 максимальная чуствительность.
void SetupSensitivity()
{
  static uint8_t stringLength = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if ((key != '*') && (key != '#'))
  {
    if (stringLength < 1)
    {
      setupGame[globalState] = (key - 48);
      lcd.setCursor(stringLength + cursorOneStr, 1);
      lcd.print(key);
      ++stringLength;
    }
  }
  if (key == '*')
  {
    setupGame[globalState] = 0;
    stringLength = 0;
    lcd.setCursor(cursorOneStr, 1);
    lcd.print(F("0"));
  }
  if (key == '#')
  {
    if (setupGame[globalState] > 0)
    {
      ++globalState;
      ShowSensitivityTime();
    }
    else
    {
      globalState += 3;
      ShowPoint();
    }
  }
}

//Во сколько раз должен ускориться отсчет при срабатывании модуля.
void SetupSensitivityTime()
{
  static uint8_t stringLength = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if ((key != '*') && (key != '#'))
  {
    if (stringLength < 2)
    {
      if (stringLength == 0) setupGame[globalState] = (key - 48) * 10;
      if (stringLength == 1) setupGame[globalState] += (key - 48);
      lcd.setCursor(stringLength + cursorOneStr, 1);
      lcd.print(key);
      ++stringLength;
    }
  }
  if (key == '*')
  {
    setupGame[globalState] = 0;
    stringLength = 0;
    lcd.setCursor(cursorOneStr, 1);
    lcd.print(F("00"));
  }
  if (key == '#')
  {
    ++globalState;
    ShowSensitivityEfect();
  }
}

//Отрезок времени для ускорения.
void SetupSensitivityEfect()
{
  static uint8_t stringLength = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if ((key != '*') && (key != '#'))
  {
    if (stringLength < 2)
    {
      if (stringLength == 0) setupGame[globalState] = (key - 48) * 10;
      if (stringLength == 1) setupGame[globalState] += (key - 48);
      lcd.setCursor(stringLength + 14, 1);
      lcd.print(key);
      ++stringLength;
    }
  }
  if (key == '*')
  {
    setupGame[globalState] = 0;
    stringLength = 0;
    lcd.setCursor(cursorOneStr, 1);
    lcd.print(F("      =    00"));
  }
  if (key == '#')
  {
    ++globalState;
    ShowPoint();
  }
}

//Активация блютуза.
void SetupPoint()
{
  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if (key == '*')
  {
    setupGame[globalState] = 0;
    globalState += 3;
    ShowAnyPress();
  }
  if (key == '#')
  {
    setupGame[globalState] = 1;
    ++globalState;
    ShowPointMenu();
  }
}

//Выбор параметров блютуз
void SetupPointMenu()
{
  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if (key == '#')
  {
    setupGame[globalState] = 0;
    globalState += 2;
    ShowAnyPress();
  }
  if (key == '*')
  {
    setupGame[globalState] = 1;
    globalState += 2;
    ShowAnyPress();
  }
}

//Запрос восстановление данных
void SetupSave()
{
  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if (key == '#')
  {
    setupGame[globalState] = 0;
    globalState = 0;
    showTextBombTime();
    EEPROM.write(0, 255);
  }
  if (key == '*')
  {
    ++globalState;
    ShowAnyPress();
  }
}

//Ожидания старта
void SetupAnyPress()
{
  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  for (uint8_t i = 0; i < adress; ++i) {
    EEPROM.write(i, setupGame[i]);
    delay(4);
  }
  ++globalState;
}

void StartGame()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("*******************"));
  lcd.setCursor(0, 1);
  lcd.print(F("*******************"));
  Serial.println(setupGame[0]);
  Serial.println(setupGame[1]);
  Serial.println(setupGame[2]);
  Serial.println(setupGame[3]);
  Serial.println(setupGame[4]);
  Serial.println(setupGame[5]);
  Serial.println(setupGame[6]);
  Serial.println(setupGame[7]);
  Serial.println(setupGame[8]);
  Serial.println(setupGame[9]);
  Serial.println(setupGame[10]);
  Serial.println(setupGame[11]);
  Serial.println(setupGame[12]);
  Serial.println(setupGame[13]);
  Serial.println(setupGame[14]);
  Serial.println(setupGame[15]);
  Serial.println(setupGame[16]);
  Serial.println(setupGame[17]);
  ++globalState;
}
