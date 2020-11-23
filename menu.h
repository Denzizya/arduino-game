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
  lcd.print(F("Time efect:"));
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
  lcd.print(F("IncorrectToogle:"));
  cursorOneStr = 0;
  lcd.setCursor(cursorOneStr, 1);
  lcd.print(F("   time   =   00"));
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

//Выбор параметров блютуз
ShowPointMenu()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Password:   *"));
  lcd.setCursor(0, 1);
  lcd.print(F("Inactive:   #"));
}

//Ожидания старта
ShowAnyPress()
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
    }
  }
  char key = keypad.getKey();
  if (key == '#' && setupGame[globalState] < 100)
  {
    ++globalState;
    ShowIncorrectToogle();
  }
}

//Если нажимаем 65-значит время убавится на  65 процентов от оставшегося
void SetupIncorrectToogle()
{
  static uint8_t stringLength = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

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
    }
  }
  char key = keypad.getKey();
  if (key == '#' && setupGame[globalState] < 100)
  {
    ++globalState;
    ShowStopTime();
  }
}

//Заморозка времени в минутах.
void SetupStopTime()
{
  static uint8_t stringLength = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

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
    }
  }
  char key = keypad.getKey();
  if (key == '#' && setupGame[globalState] < 100)
  {
    ++globalState;
    ShowSlomoTime();
  }
}

//Во сколько раз медленее будет отсчет.
void SetupSlomoTime()
{
  static uint8_t stringLength = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

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
    lcd.print(F("    time   =   00"));
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

  if (key == '*')
  {
    setupGame[globalState] = 0;
    globalState += 2;
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
SetupPointMenu()
{
  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  if (key == '*')
  {
    setupGame[globalState] = 0;
    ++globalState;
    ShowAnyPress();
  }
  if (key == '#')
  {
    setupGame[globalState] = 1;
    ++globalState;
    ShowAnyPress();
  }
}

//Ожидания старта
SetupAnyPress()
{
  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  ++globalState;
}

StartGame()
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

/*
  if (buttonClick(BUTTON_PLUS, frequency_button))
  {
    ++setupGame[0];
    if (setupGame[0] == 10)
      frequency_button -= 8;
    if (setupGame[0] == 100)
      frequency_button -= 5;
  }
  else if (setupGame[0] > 0)
  {
    if (buttonClick(BUTTON_MINUS, frequency_button))
    {
      --setupGame[0];
      if (setupGame[0] == 9 || setupGame[0] == 99)
      {

        if (setupGame[0] == 9)
          frequency_button += 8;
        if (setupGame[0] == 99)
          frequency_button += 5;

        lcd.print("                ");
      }
    }
    if (buttonClick(BUTTON_OK, frequency_button, true)) // true - параметр удержания
    {
      ++globalState;
    }
  }
  /*
    if (digitalRead(BUTTON_PLUS) == HIGH && digitalRead(BUTTON_MINUS) == HIGH && digitalRead(BUTTON_OK) == HIGH)
    {
      if (millis() > setupTimeLastMillis)
      {
        lcd.print(setupGame[0]);
        if (millis() > (setupTimeLastMillis + 500))
        {
          setupTimeLastMillis = millis() + 500;
        }
      }
      else
      {
        lcd.print(F("                "));
      }
    }
    else
    {
      lcd.print(setupGame[0]);
    }

  }

  //Кнопка деактивации
  void Password()
  {
  if (!globalStateButton)
  {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Password:");
    lcd.setCursor(5, 1);
    lcd.print(setupGame[1]);
  }
  else
  {
    lcd.setCursor(5, 1);
    if (buttonClick(BUTTON_PLUS, frequency_button))
    {
      ++setupGame[1];
      if (setupGame[1] == 10)
        frequency_button -= 8;
      if (setupGame[1] == 100)
        frequency_button -= 5;
    }
    else if (setupGame[1] > 0)
    {
      if (buttonClick(BUTTON_MINUS, frequency_button))
      {
        --setupGame[1];
        if (setupGame[1] == 9 || setupGame[1] == 99)
        {

          if (setupGame[1] == 9)
            frequency_button += 8;
          if (setupGame[1] == 99)
            frequency_button += 5;

          lcd.print("                ");
        }
      }
      if (buttonClick(BUTTON_OK, frequency_button, true)) // true - параметр удержания
      {
        ++globalState;
      }
    }

    if (digitalRead(BUTTON_PLUS) == HIGH && digitalRead(BUTTON_MINUS) == HIGH && digitalRead(BUTTON_OK) == HIGH)
    {
      if (millis() > setupTimeLastMillis)
      {
        lcd.print(setupGame[1]);
        if (millis() > (setupTimeLastMillis + 500))
        {
          setupTimeLastMillis = millis() + 500;
        }
      }
      else
      {
        lcd.print(F("                "));
      }
    }
    else
    {
      lcd.print(setupGame[1]);
    }
  }
  }
  /*
  void IncorrectPassword()
  {
  if (!globalStateButton)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Incorrect Pass:");
    lcd.setCursor(5, 1);
    lcd.print(setupGame[2]);
  }
  else
  {
    lcd.setCursor(5, 1);
    if (buttonClick(BUTTON_PLUS, frequency_button))
    {
      ++setupGame[2];
      if (setupGame[2] == 10)
        frequency_button -= 8;
      if (setupGame[2] == 100)
        frequency_button -= 5;
    }
    else if (setupGame[2] > 0)
    {
      if (buttonClick(BUTTON_MINUS, frequency_button))
      {
        --setupGame[2];
        if (setupGame[2] == 9 || setupGame[2] == 99)
        {

          if (setupGame[2] == 9)
            frequency_button += 8;
          if (setupGame[2] == 99)
            frequency_button += 5;

          lcd.print("                ");
        }
      }
      if (buttonClick(BUTTON_OK, frequency_button, true)) // true - параметр удержания
      {
        ++globalState;
      }
    }

    if (digitalRead(BUTTON_PLUS) == HIGH && digitalRead(BUTTON_MINUS) == HIGH && digitalRead(BUTTON_OK) == HIGH)
    {
      if (millis() > setupTimeLastMillis)
      {
        lcd.print(setupGame[2]);
        if (millis() > (setupTimeLastMillis + 500))
        {
          setupTimeLastMillis = millis() + 500;
        }
      }
      else
      {
        lcd.print(F("                "));
      }
    }
    else
    {
      lcd.print(setupGame[2]);
    }
  }
  }
  /*
  void Attempts()
  {
  if (!globalStateButton)
  {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Attemps:");
    lcd.setCursor(5, 1);
    lcd.print(setupGame[2]);
  }
  else
  {
    lcd.setCursor(5, 1);
    if (buttonClick(BUTTON_PLUS, frequency_button))
    {
      ++setupGame[2];
      if (setupGame[2] == 10)
        frequency_button -= 8;
      if (setupGame[2] == 100)
        frequency_button -= 5;
    }
    else if (setupGame[2] > 0)
    {
      if (buttonClick(BUTTON_MINUS, frequency_button))
      {
        --setupGame[2];
        if (setupGame[2] == 9 || setupGame[2] == 99)
        {

          if (setupGame[2] == 9)
            frequency_button += 8;
          if (setupGame[2] == 99)
            frequency_button += 5;

          lcd.print("                ");
        }
      }
      if (buttonClick(BUTTON_OK, frequency_button, true)) // true - параметр удержания
      {
        ++globalState;
      }
    }

    if (digitalRead(BUTTON_PLUS) == HIGH && digitalRead(BUTTON_MINUS) == HIGH && digitalRead(BUTTON_OK) == HIGH)
    {
      if (millis() > setupTimeLastMillis)
      {
        lcd.print(setupGame[2]);
        if (millis() > (setupTimeLastMillis + 500))
        {
          setupTimeLastMillis = millis() + 500;
        }
      }
      else
      {
        lcd.print(F("                "));
      }
    }
    else
    {
      lcd.print(setupGame[2]);
    }
  }

  }
*/
