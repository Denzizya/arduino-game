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
  lcd.print(F("Bomb time:"));
  cursorOneStr = 7;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("000"));
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
  lcd.setCursor(0, 0);
  lcd.print(F("Time effect/min:"));
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
  lcd.print(F("Accel Time:"));
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

//Начинаем игру.
void ShowTimerGame()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Time -> 00:00:00"));
  cursorZeroStr = 8;
  lcd.setCursor(cursorZeroStr, 0);
  lcd.print(ConstructTimeString(setupGame[0]));
  cursorOneStr = 7;
  lcd.setCursor(0, 1);
  lcd.print(F("Pass:  ????????"));
  setupTimeLastMillis = millis();
  audio.play(1);
}

//Конец игры Поражение
void GameOver()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Time -> 00:00:00"));
  lcd.setCursor(0, 1);
  lcd.print(F("                "));
  lcd.setCursor(3, 1);
  lcd.print(F("Game Over!"));
  globalState += 2;
}

//Конец игры Победа
void GameWin()
{
  lcd.setCursor(0, 1);
  lcd.print(F("Bomb Deactiva..."));
  ++globalState;
}
//=================================================================================================================//

//Установить таймер
void SetupBombTime()
{
  static uint8_t timeStringLength = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if ((key != '*') && (key != '#'))
  {
    if (timeStringLength < 3)
    {
      if (timeStringLength == 0)
      {
        setupGame[globalState] = (key - 48) * 100;
      }
      if (timeStringLength == 1)
      {
        setupGame[globalState] += (key - 48) * 10;
      }
      if (timeStringLength == 2)
      {
        setupGame[globalState] += (key - 48);
      }
      lcd.setCursor(timeStringLength + cursorOneStr, 1);
      lcd.print(key);
      ++timeStringLength;
    }
  }
  else if (key == '*')
  {
    timeStringLength = 0;
    setupGame[globalState] = 0;
    lcd.setCursor(cursorOneStr, 1);
    lcd.print(F("000"));
  }
  else if ((key == '#') && (setupGame[globalState] > 0))
  {
    setupGame[globalState] *= 60;
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
    else if (setupGame[globalState] == 0)
    {
      setupGame[globalState] = 100;
      ++globalState;
      ShowCorrectToggle();
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
  for (uint8_t i = 0; i < WIRE_PINS_COUNT_BUTTON; ++i) {
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
    setupGame[globalState] *= 60;
    ++globalState;
    ShowStopToogle();
  }
}

//Номер кнопки которая остановит отсчет на определеное время.
void SetupStopToogle()
{
  for (uint8_t i = 0; i < WIRE_PINS_COUNT_BUTTON; ++i) {
    auto &w = wires[i];
    if (!w.Value() && setupGame[3] != i) {
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
  for (uint8_t i = 0; i < WIRE_PINS_COUNT_BUTTON; ++i) {
    auto &w = wires[i];
    if (!w.Value() && setupGame[3] != i && setupGame[5] != i) {
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
      switch (setupGame[globalState])
      {
        case 1: setupGame[globalState] = 9; break;
        case 2: setupGame[globalState] = 8; break;
        case 3: setupGame[globalState] = 7; break;
        case 4: setupGame[globalState] = 6; break;
        case 5: setupGame[globalState] = 5; break;
        case 6: setupGame[globalState] = 4; break;
        case 7: setupGame[globalState] = 3; break;
        case 8: setupGame[globalState] = 2; break;
        case 9: setupGame[globalState] = 1; break;
      }
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
    if (setupGame[globalState] > 20 || setupGame[globalState] < 2)
    {
      setupGame[globalState] = 0;
      stringLength = 0;
      lcd.setCursor(cursorOneStr, 1);
      lcd.print(F("00"));
    }
    else
    {
      ++globalState;
      ShowSensitivityEfect();
    }
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
      lcd.setCursor(stringLength + 11, 1);
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
    memset(setupGame, 0, sizeof(setupGame));
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

  int cellEeprom = 0;
  for (uint8_t i = 0; i < adress; ++i) {
    if (i == 0 || i == 1) {
      EEPROMWritelong(cellEeprom, setupGame[i]);
      cellEeprom += 3;
    }
    else
    {
      EEPROM.write(cellEeprom, setupGame[i]);
    }
    ++cellEeprom;
    delay(1);
  }

  ++globalState;
  setupTimeLastMillis = millis();
  ShowTimerGame();
}
