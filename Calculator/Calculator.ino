#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};

byte rowPins[ROWS] = {12, 11, 10, 9};
byte colPins[COLS] = {8, 7, 6, 5};
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int rs = 0, en = 1, d4 = 2, d5 = 3, d6 = 4, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int Num1 = 0, Num2 = 0;
double Number = 0;
char key, action;
bool result = false;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Simple ");
  lcd.setCursor(0, 1);
  lcd.print("Calculator");
  delay(2000);
  lcd.clear();
}

void loop() {
  key = kpd.getKey();
  if (key != NO_KEY) processKey();
  if (result) calculateResult();
  displayResult();
}

void processKey() {
  if (key == 'C') {  // Reset
    Number = Num1 = Num2 = 0;
    result = false;
    lcd.clear();
  } else if (key >= '0' && key <= '9') {  // Integer Input Only
    Number = (Number * 10) + (key - '0');
  } else if (key == '=') {  // Equals
    Num2 = Number;
    result = true;
  } else if (key == '+' || key == '-' || key == '*' || key == '/') {  // Operations
    Num1 = Number;
    Number = 0;
    result = false;
    action = key;
  }
}

void calculateResult() {
  switch (action) {
    case '+': Number = Num1 + Num2; break;
    case '-': Number = Num1 - Num2; break;
    case '*': Number = Num1 * Num2; break;
    case '/': Number = (Num2 != 0) ? ((double)Num1 / Num2) : 0.0; break;
  }
  result = false;
}

void displayResult() {
  lcd.setCursor(0, 0);
  lcd.print("Exp: ");lcd.print(Num1); lcd.print(action); lcd.print(Num2);
  if (result) { lcd.print("="); lcd.print(Number, 2); }
  lcd.setCursor(0, 1);
  lcd.print("Result: "); lcd.print(Number, 2);
}
