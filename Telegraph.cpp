#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int buttonPin = A0;
int ledPin = 6;

// Timing
unsigned long pressStart = 0;
unsigned long lastRelease = 0;

bool isPressed = false;
bool letterDone = false;
bool spaceAdded = false;

String currentSymbol = "";
String outputText = "";

// Morse dictionary
String morseLetters[][2] = {
  {".-", "A"}, {"-...", "B"}, {"-.-.", "C"}, {"-..", "D"},
  {".", "E"}, {"..-.", "F"}, {"--.", "G"}, {"....", "H"},
  {"..", "I"}, {".---", "J"}, {"-.-", "K"}, {".-..", "L"},
  {"--", "M"}, {"-.", "N"}, {"---", "O"}, {".--.", "P"},
  {"--.-", "Q"}, {".-.", "R"}, {"...", "S"}, {"-", "T"},
  {"..-", "U"}, {"...-", "V"}, {".--", "W"}, {"-..-", "X"},
  {"-.--", "Y"}, {"--..", "Z"}
};

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Morse Ready");
  delay(1500);
  lcd.clear();
}

void loop() {

  bool state = digitalRead(buttonPin) == LOW;
  unsigned long now = millis();

  // BUTTON PRESS START
  if(state && !isPressed) {
    isPressed = true;
    pressStart = now;
    digitalWrite(ledPin, HIGH);

    letterDone = false;
    spaceAdded = false;
  }

  // BUTTON RELEASE
  if(!state && isPressed) {
    isPressed = false;
    digitalWrite(ledPin, LOW);

    unsigned long duration = now - pressStart;

    if(duration < 300) {
      currentSymbol += ".";
    } else {
      currentSymbol += "-";
    }

    lastRelease = now;
    updateLCD();
  }

  // LETTER GAP
  if(!isPressed && currentSymbol.length() > 0 && !letterDone) {
    if(now - lastRelease > 700) {
      decodeSymbol();
      currentSymbol = "";
      updateLCD();
      letterDone = true;
    }
  }

  // WORD GAP
  if(!isPressed && letterDone && !spaceAdded) {
    if(now - lastRelease > 1500) {
      outputText += " ";
      updateLCD();
      spaceAdded = true;
    }
  }
}

// DECODE FUNCTION
void decodeSymbol() {
  for(int i = 0; i < 26; i++) {
    if(currentSymbol == morseLetters[i][0]) {
      outputText += morseLetters[i][1];
      return;
    }
  }
  outputText += "?";
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(currentSymbol);
  lcd.setCursor(0, 1);

  int len = outputText.length();
  if(len > 16) {
    lcd.print(outputText.substring(len - 16));
  } else {
    lcd.print(outputText);
  }
}
