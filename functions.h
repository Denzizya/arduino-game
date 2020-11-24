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
  if ((millis() - setupTimeLastMillis) > 1000)
  {
    cursorZeroStr = 8;
    cursorOneStr = 4;
    lcd.setCursor(cursorOneStr, 1);
    lcd.print(F("********"));
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Time -> 00:00"));
  lcd.setCursor(4, 1);
  lcd.print(F("********"));
}

String ConstructTimeString(unsigned long secs) {
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
