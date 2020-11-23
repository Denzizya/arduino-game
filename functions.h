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
