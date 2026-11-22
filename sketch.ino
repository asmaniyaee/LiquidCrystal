#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8, 7);

const char L0[] PROGMEM = "He love me not,";
const char L1[] PROGMEM = "he loves me";
const char L2[] PROGMEM = "He holds me tight then lets me go";
const char L3[] PROGMEM = "You gotta say that you're sorry at the end of the night";
const char L4[] PROGMEM = "Wake up in the morning,";
const char L5[] PROGMEM = "everything's alright";
const char L6[] PROGMEM = "At the end of the story,";
const char L7[] PROGMEM = " you're holdin' me tight";
const char L8[] PROGMEM = "I don't need to worry";
const char L9[] PROGMEM = "am I out of my mind?";


const char* const lyrics[] PROGMEM = { L0, L1, L2, L0, L1, L2, L0, L1, L2, L0, L1, L2, L3, L4, L5, L6, L7, L8,};


const int LINE_COUNT = sizeof(lyrics) / sizeof(lyrics[0]);
const int COLS = 16;
char buf[64];
String prevLine = "";

void typeLine(String s, int row) {
  for (int i = 0; i < (int)s.length(); i++) {
    lcd.setCursor(i, row);
    lcd.print(s[i]);
    delay(70);
  }
}

void scrollLine(String s, int row) {
  for (int p = 0; p <= (int)s.length() - COLS; p++) {
    lcd.setCursor(0, row);
    lcd.print(s.substring(p, p + COLS));
    delay(300);
  }
}

void showLine(String s) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(prevLine.substring(0, COLS));

  if (s.length() <= COLS) {
    typeLine(s, 1);
  } else {
    lcd.setCursor(0, 1);
    lcd.print(s.substring(0, COLS));
    delay(600);
    scrollLine(s, 1);
  }
  delay(1200);
  prevLine = s;
}

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  for (int i = 0; i < LINE_COUNT; i++) {
    strcpy_P(buf, (char*)pgm_read_word(&lyrics[i]));
    showLine(String(buf));
  }
  prevLine = "";
  lcd.clear();
  delay(1500);
}
