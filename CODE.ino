/**
   SMART Arduino Door Lock System
   DLD Project 2026
*/

#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

/* ---------------- LCD ---------------- */

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

/* ---------------- SERVO ---------------- */
/* ---------------- SERVO ---------------- */

Servo lockServo;

#define SERVO_PIN 6
#define LOCK_POS 0
#define UNLOCK_POS 180
// Servo lockServo;

// #define SERVO_PIN 6
// #define LOCK_POS 0
// #define UNLOCK_POS 180

/* ---------------- BUZZER + LEDs ---------------- */

#define BUZZER_PIN 13
#define GREEN_LED A4
#define RED_LED A5

/* ---------------- PASSWORD ---------------- */

String password = "1234";

/* ---------------- SECURITY ---------------- */

int wrongAttempts = 0;

/* ---------------- KEYPAD ---------------- */

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {5,4,3,2};
byte colPins[COLS] = {A3,A2,A1,A0};

Keypad keypad = Keypad(
  makeKeymap(keys),
  rowPins,
  colPins,
  ROWS,
  COLS
);

/* ================================================= */
/* ---------------- STARTUP SCREEN ----------------- */
/* ================================================= */

void startupScreen() {

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("SMART SECURITY");

  lcd.setCursor(2,1);
  lcd.print("BS_AI 2026");

  /* Startup LED + buzzer animation */

  for(int i=0; i<3; i++) {

    digitalWrite(GREEN_LED,HIGH);
    digitalWrite(RED_LED,HIGH);

    tone(BUZZER_PIN,1000);

    delay(200);

    digitalWrite(GREEN_LED,LOW);
    digitalWrite(RED_LED,LOW);

    noTone(BUZZER_PIN);

    delay(200);
  }

  lcd.clear();

  lcd.setCursor(3,0);
  lcd.print("SYSTEM");

  lcd.setCursor(4,1);
  lcd.print("READY");

  tone(BUZZER_PIN,1500);

  delay(500);

  noTone(BUZZER_PIN);

  delay(1500);

  lcd.clear();
}

/* ================================================= */
/* ---------------- GET PASSWORD ------------------- */
/* ================================================= */

String getPassword() {

  String entered = "";

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Enter Password");

  lcd.setCursor(0,1);

  while(entered.length() < 4) {

    char key = keypad.getKey();

    if(key >= '0' && key <= '9') {

      entered += key;

      lcd.print("*");

      tone(BUZZER_PIN,800);

      delay(80);

      noTone(BUZZER_PIN);
    }
  }

  return entered;
}

/* ================================================= */
/* ---------------- CHANGE PASSWORD ---------------- */
/* ================================================= */

void changePassword() {

  String newPass = "";

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("New Password");

  lcd.setCursor(0,1);

  while(newPass.length() < 4) {

    char k = keypad.getKey();

    if(k >= '0' && k <= '9') {

      newPass += k;

      lcd.print("*");

      tone(BUZZER_PIN,1000);

      delay(80);

      noTone(BUZZER_PIN);
    }
  }

  password = newPass;

  lcd.clear();

  lcd.setCursor(1,0);
  lcd.print("Password Set");

  digitalWrite(GREEN_LED,HIGH);

  tone(BUZZER_PIN,1200);

  delay(1000);

  noTone(BUZZER_PIN);

  digitalWrite(GREEN_LED,LOW);

  delay(1000);
}

/* ================================================= */
/* ---------------- UNLOCK DOOR -------------------- */
/* ================================================= */

void unlockDoor() {

  lcd.clear();

  lcd.setCursor(2,0);
  lcd.print("ACCESS OK");

  digitalWrite(RED_LED,LOW);
  digitalWrite(GREEN_LED,HIGH);

  tone(BUZZER_PIN,1200);

  lcd.setCursor(0,1);
  lcd.print("Opening Door");

  /* Smooth Servo Unlock */

  for(int pos = LOCK_POS; pos <= UNLOCK_POS; pos++) {

    lockServo.write(pos);

    delay(15);
  }

  delay(500);

  noTone(BUZZER_PIN);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("A=New Password");

  lcd.setCursor(0,1);
  lcd.print("#=Lock Door");

  while(true) {

    char key = keypad.getKey();

    /* Change Password */

    if(key == 'A') {

      changePassword();

      lcd.clear();

      lcd.setCursor(0,0);
      lcd.print("A=New Password");

      lcd.setCursor(0,1);
      lcd.print("#=Lock Door");
    }

    /* Lock Door */

    if(key == '#') {

      lcd.clear();

      lcd.setCursor(3,0);
      lcd.print("LOCKING...");

      digitalWrite(RED_LED,HIGH);
      digitalWrite(GREEN_LED,LOW);

      tone(BUZZER_PIN,700);

      lcd.setCursor(0,1);
      lcd.print("Closing Door");

      /* Smooth Servo Lock */

      for(int pos = UNLOCK_POS; pos >= LOCK_POS; pos--) {

        lockServo.write(pos);

        delay(15);
      }

      delay(500);

      noTone(BUZZER_PIN);

      lcd.clear();

      lcd.setCursor(4,0);
      lcd.print("LOCKED");

      delay(1000);

      break;
    }
  }
}

/* ================================================= */
/* ---------------- DENY ACCESS -------------------- */
/* ================================================= */

void denyAccess() {

  wrongAttempts++;

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("ACCESS DENIED");

  lcd.setCursor(0,1);
  lcd.print("Attempt: ");
  lcd.print(wrongAttempts);

  digitalWrite(RED_LED,HIGH);

  /* Alarm Sound */

  for(int i=0; i<3; i++) {

    tone(BUZZER_PIN,300);

    delay(150);

    noTone(BUZZER_PIN);

    delay(150);
  }

  digitalWrite(RED_LED,LOW);

  delay(1000);

  /* Security Lock */

  if(wrongAttempts >= 3) {

    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("SYSTEM LOCKED");

    lcd.setCursor(0,1);
    lcd.print("Wait 10 Sec");

    for(int i=0; i<10; i++) {

      digitalWrite(RED_LED,HIGH);

      tone(BUZZER_PIN,250);

      delay(300);

      digitalWrite(RED_LED,LOW);

      noTone(BUZZER_PIN);

      delay(300);
    }

    wrongAttempts = 0;
  }
}

/* ================================================= */
/* ---------------- SETUP -------------------------- */
/* ================================================= */

void setup() {

  lcd.begin(16,2);

  pinMode(BUZZER_PIN,OUTPUT);

  pinMode(GREEN_LED,OUTPUT);

  pinMode(RED_LED,OUTPUT);

  lockServo.attach(SERVO_PIN);

  /* Initial Lock Position */

  lockServo.write(LOCK_POS);

  digitalWrite(RED_LED,HIGH);

  startupScreen();
}

/* ================================================= */
/* ---------------- LOOP --------------------------- */
/* ================================================= */

void loop() {

  String entered = getPassword();

  if(entered == password) {

    wrongAttempts = 0;

    unlockDoor();

  } else {

    denyAccess();
  }
}