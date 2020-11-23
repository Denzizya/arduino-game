#define DEVICE 1

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
#else
uint8_t KEYPAD_COL_PINS[KEYPAD_COLS] = {A2, A1, A0};
uint8_t KEYPAD_ROW_PINS[KEYPAD_ROWS] = {A6, A5, A4, A3};
#endif
Keypad keypad(makeKeymap(KEYPAD_KEYS), KEYPAD_ROW_PINS, KEYPAD_COL_PINS, KEYPAD_ROWS, KEYPAD_COLS);

//==========================================================================//
/*** LED ***/

/*** RELE ***/
#define RELAY_PINS 12
#define ON  LOW
#define OFF HIGH

/*** BUZZER ***/
//#define BUZZER_PIN 13
//#define BUZZER_FREQUENCY 200


/*** timer ***/
unsigned long setupTimeLastMillis = millis();
//unsigned long ledLastMillis;
//unsigned long ledLastMillis;

/**********************/
uint8_t globalState = 0;          //Пункт меню
bool globalStateButton = false;   //Вывод меню
const int adress = 16;            //Количество параметров
long setupGame[adress];           //Сохранение параметров
int globalTimer = 0;              //Тайвер установки времени
int cursorOneStr = 0;

int timeStringHour = 0; //Часы
int timeStringMin = 0;  //Минуты

#if DEVICE == 1
uint8_t WIRE_PINS[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
#else
uint8_t WIRE_PINS[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
#endif
const uint8_t WIRE_PINS_COUNT = sizeof(WIRE_PINS) / sizeof(uint8_t);

int frequency_button = 20;    //Скорось нажатия кнопки

/*
  int button_click_arr[20][2];  //Масив настройки дребезга кнопки
*/


int runTimer = 1;
int runFor = 60; // time in seconds
//int buzzerPin = 13;
//    int relayPin=4;
int data = 0;
