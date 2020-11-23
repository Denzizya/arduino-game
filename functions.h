//Определение кнопки
class WireSensor {
  public:
    WireSensor() : _pin{0} {};
    void SetPin(uint8_t pin) {
      _pin = pin;
      pinMode(pin, INPUT_PULLUP);
    }
    boolean Value() const {
      boolean _ret = ( digitalRead(_pin) && HIGH );
      return _ret;
    }
  private:
    uint8_t _pin;
};
WireSensor wires[WIRE_PINS_COUNT];







/*
void Buzz(int delayMs = 100, int frequency = BUZZER_FREQUENCY) {
  tone(BUZZER_PIN, frequency);
  delay(delayMs);
  noTone(BUZZER_PIN);
}

/*
//Нажатие кнопки
int buttonClick(int button_pin, int frequency_button, bool ok = false) //(Пин кнопки, частота дребезга, увеличивать нажатия при задержке кнопки)
{
  if (digitalRead(button_pin) == LOW && !button_click_arr[button_pin][1])
  {
    if (button_click_arr[button_pin][0] > frequency_button)
    {
      button_click_arr[button_pin][1] = true;
      button_click_arr[button_pin][0] = 0;
      return true;
    }
  }
  if (!ok)
  {
    if (button_click_arr[button_pin][0] > (frequency_button + frequency_button + 20))
    {
      button_click_arr[button_pin][1] = false;
      button_click_arr[button_pin][0] = 0;
    }
  }

  if (digitalRead(button_pin) == HIGH)
  {
    button_click_arr[button_pin][1] = false;
    button_click_arr[button_pin][0] = 0;
  }
  ++button_click_arr[button_pin][0];
  return false;
}
*/


/*
//Определение кнопки
int SelectButton()
{
  if (buttonClick(BUTTON_ONE, frequency_button))
  {
    return BUTTON_ONE;
  }
  else if (buttonClick(BUTTON_TWO, frequency_button))
  {
    return BUTTON_TWO;
  }
  else if (buttonClick(BUTTON_THRE, frequency_button))
  {
    return BUTTON_THRE;
  }
  else if (buttonClick(BUTTON_FOUR, frequency_button))
  {
    return BUTTON_FOUR;
  }
  else if (buttonClick(BUTTON_FIVE, frequency_button))
  {
    return BUTTON_FIVE;
  }
  else if (buttonClick(BUTTON_SIX, frequency_button))
  {
    return BUTTON_SIX;
  }
  else if (buttonClick(BUTTON_SEVEN, frequency_button))
  {
    return BUTTON_SEVEN;
  }
  else if (buttonClick(BUTTON_EGHT, frequency_button))
  {
    return BUTTON_EGHT;
  }
  else if (buttonClick(BUTTON_NINE, frequency_button))
  {
    return BUTTON_NINE;
  }
  else if (buttonClick(BUTTON_TEN, frequency_button))
  {
    return BUTTON_TEN;
  }
  return false;
}
/*
  //Нажатие кнопки
  int buttonClick(int button_pin, int frequency_button)
  {
  if (digitalRead(button_pin) == LOW && !button_click_arr[button_pin][1])
  {
    if (button_click_arr[button_pin][0] > frequency_button)
    {
      button_click_arr[button_pin][1] = true;
      button_click_arr[button_pin][0] = 0;
      Buzz();
      return true;
    }
    ++button_click_arr[button_pin][0];
  }

  if (digitalRead(button_pin) == HIGH)
  {
    button_click_arr[button_pin][1] = false;
    button_click_arr[button_pin][0] = 0;
  }
  return false;
  }
*/

/*
void SetupNegativeTime()
{
  if (runTimer == 1)
  {
    lcd.clear();
    lcd.print("TIMER=");
    //Start timer
    for (int timer = globalTimer; timer > 0; --timer) {
      if (timer >= 10) {
        lcd.setCursor(6, 0);
      } else {
        lcd.setCursor(6, 0);
        lcd.print("0");
        lcd.setCursor(7, 0);
      }
      lcd.print(timer);
      lcd.print(" SECOND!");
      delay(1000);
    }
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print(" TIMER ALERT!");
    runTimer = 0;
  }
  runTimer = 0;
  lcd.noDisplay();
  delay(250);
  for (int duration = 0; duration < 100; duration ++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(500);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(500);
  }
  lcd.display();
  delay(250);
  
    if (buttonClick(BUTTON_OK, 3, true))
    {
      --globalState;
      runTimer = 1;
    }
  
}
*/
