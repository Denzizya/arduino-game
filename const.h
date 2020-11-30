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

uint8_t KEYPAD_COL_PINS[KEYPAD_COLS] = {A2, A1, A0};
uint8_t KEYPAD_ROW_PINS[KEYPAD_ROWS] = {A6, A5, A4, A3};
uint8_t WIRE_PINS_BUTTON[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, A8, A9, A10};

/*** LED ***/
uint8_t WIRE_PINS_LED[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 44, 45, 46};
const uint8_t WIRE_PINS_COUNT_LED = sizeof(WIRE_PINS_LED) / sizeof(uint8_t);

// bluetooth settings
#define BLUETOOTH_BAUDRATE 115200
#define SCAN_DELAY_MS 2000  //Пауза между поиском
#define MIN_VALID_RSSI -90  //Дитанция, чем меньше тем ближе
#define VALID_NAME F("BOMB_POINT")  //Что ищем
#define VALID_NAME_NETRAL F("BOMB_NETRAL")  //Что ищем

unsigned long timeReadScan = millis();  //Перезапуск сканирования
unsigned long timeScan = millis();      //Задержка на сканирование

Keypad keypad(makeKeymap(KEYPAD_KEYS), KEYPAD_ROW_PINS, KEYPAD_COL_PINS, KEYPAD_ROWS, KEYPAD_COLS);

const uint8_t WIRE_PINS_COUNT_BUTTON = sizeof(WIRE_PINS_BUTTON) / sizeof(uint8_t);

uint8_t frequency_button = 20;  //Скорось нажатия кнопки

//Акселерометр
MPU6050 mpu(0x68);
int16_t ax, ay, az;
long timeAccel;
bool speedAccel = false;
int acsselButton;
unsigned long playAccel;

//Плеер 
DFRobotDFPlayerMini audio{};
#define AUDIO_VOLUME 30 // min = 0, max = 30
uint8_t audioConnected = 0;

//==========================================================================//
/***MENU***/
bool ViewMenuPass = false;  //Вывод меню блютуза нейтрали с паролем
unsigned long timePass;     //Вывод меню ввода пароля
bool ViewSetupPass = false; //Вывод меню ввода пароля

/*** RELE ***/
#define RELAY_PINS 42
#define ON  LOW
#define OFF HIGH

/*** BUZZER ***/
#define BUZZER_PIN 13

/*** Timer ***/
unsigned long setupTimeLastMillis;	//Метка времени
unsigned long speedTime = 1000;		  //Скорость таймера
unsigned long setupMiddleTimeMillis;//Таймер замедления

/**************************************************************/
uint8_t globalState = 0;          //Пункт меню
bool globalStateButton = false;   //Вывод меню
const uint8_t adress = 16;        //Количество параметров
long setupGame[adress];           //Сохранение параметров
uint8_t globalTimer = 0;          //Тайвер установки времени

uint8_t cursorZeroStr = 0;  //Курсор нулевой строки
uint8_t cursorOneStr = 0;   //Курсор первой строки


/*********** LED ****************/
long timeLed;     
uint8_t indexLed = 0;
uint8_t sw = 0; //Позиция яркой капли
