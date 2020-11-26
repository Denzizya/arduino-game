#define DEVICE 0

LiquidCrystal_I2C lcd(0x27, 16, 2);

/*** Кнопки / Клавиатура ***/
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 3
char KEYPAD_KEYS[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'},
};


#if DEVICE == 1
uint8_t KEYPAD_ROW_PINS[KEYPAD_ROWS] = {13, A5, A4, A3};
uint8_t KEYPAD_COL_PINS[KEYPAD_COLS] = {A2, A1, A0};
uint8_t WIRE_PINS_BUTTON[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
#else
uint8_t KEYPAD_COL_PINS[KEYPAD_COLS] = {A2, A1, A0};
uint8_t KEYPAD_ROW_PINS[KEYPAD_ROWS] = {A6, A5, A4, A3};
uint8_t WIRE_PINS_BUTTON[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

/*** LED ***/
uint8_t WIRE_PINS_LED[] = {52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22};
const uint8_t WIRE_PINS_COUNT_LED = sizeof(WIRE_PINS_LED) / sizeof(uint8_t);
#endif
Keypad keypad(makeKeymap(KEYPAD_KEYS), KEYPAD_ROW_PINS, KEYPAD_COL_PINS, KEYPAD_ROWS, KEYPAD_COLS);

const uint8_t WIRE_PINS_COUNT_BUTTON = sizeof(WIRE_PINS_BUTTON) / sizeof(uint8_t);

uint8_t frequency_button = 20;  //Скорось нажатия кнопки
/*
  int button_click_arr[20][2];  //Масив настройки дребезга кнопки
*/
//==========================================================================//


/*** RELE ***/
#define RELAY_PINS 12
#define ON  LOW
#define OFF HIGH

/*** BUZZER ***/
//#define BUZZER_PIN 13
//#define BUZZER_FREQUENCY 200


/*** Timer ***/
unsigned long setupTimeLastMillis;	//Метка времени
unsigned long speedTime = 1000;		  //Скорость таймера
unsigned long setupMiddleTimeMillis;//Таймер замедления

/**********************/
uint8_t globalState = 0;          //Пункт меню
bool globalStateButton = false;   //Вывод меню
const uint8_t adress = 15;        //Количество параметров
long setupGame[adress];           //Сохранение параметров
uint8_t globalTimer = 0;          //Тайвер установки времени

uint8_t cursorZeroStr = 0;  //Курсор нулевой строки
uint8_t cursorOneStr = 0;   //Курсор первой строки
