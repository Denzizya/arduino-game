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

  //Return the recomposed long by using bitshift.
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}
