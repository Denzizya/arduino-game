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

void ShowTimerLcd()
{

  uint8_t timeStringMin = setupGame[0] / 1000 / 60;
  uint8_t timeStringSec;
  String view = String(timeStringMin);
  lcd.setCursor(cursorZeroStr, 0);
  lcd.print(view);

}

void timerGame()
{
  if(setupGame[0] == 0)
  {
	++globalState; // Конец игры
  }

  viewZeroString(); //Показываем время таймера
  readButton();		//Считываем нажатие тумблеров
  readPassword();	//Ввод пароля
}

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

//===========================================================================================//

//Отображение остчета времени
bool viewZeroString()
{
if ((millis() - setupTimeLastMillis) > speedTime)
  {
    lcd.setCursor(cursorZeroStr, 0);
    lcd.print(ConstructTimeString(unsigned long setupGame[0]));
    setupTimeLastMillis = millis();
	--setupGame[0];
    return true;
  }
  return false;
}

//Чтение тумблеров
void readButton()
{
  for (uint8_t i = 0; i < WIRE_PINS_COUNT; ++i) {
    auto &w = wires[i];
    if (!w.Value())
	{
		if(setupGame[4] == i)
		{
			//Номер кнопки останавливающей таймер ( 1-10 )
		}
		else if (setupGame[6] == i)
		{
			//Номер кнопки которая остановит отсчет на определеное время.
		}
		else if (setupGame[8] == i)
		{
			//Номер кнопки замедляющий отсчет
		}
		else
		{
			//Ускоряем таймер
		}
	}
  }
}

//Чтение пароля
void readPassword()
{
  static uint8_t stringLength = 0;
  static uint8_t pass = 0;

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  rele();

  if ((key != '*') && (key != '#'))
  {
    if (stringLength < 2)
    {
      if (stringLength == 0) pass = (key - 48) * 10;
      if (stringLength == 1) pass += (key - 48);
      lcd.setCursor(stringLength + cursorOneStr, 1);
      lcd.print(key);
      ++stringLength;
    }
  }
  if (key == '*')
  {
    pass = 0;
    stringLength = 0;
    lcd.setCursor(cursorOneStr, 1);
    lcd.print(F("????????"));
  }
  if (key == '#' && setupGame[globalState] > 0)
  {
	  if(globalState[1] != pass){ //Пароль не верный
		globalState[2]; //Ускорение отсчета  при вводе неверного пароля
		--globalState[3]; //Количество попыток ввода пароля
	  }
	  else
	  {
		  ++globalState; //Завершили игру
	  }
  }	
}