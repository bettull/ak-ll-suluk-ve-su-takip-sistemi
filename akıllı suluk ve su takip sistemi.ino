#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// --- LCD ---
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C adresi 0x27 olan 16x2 ekran

// --- Keypad ---
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// --- HC-SR04 ---
const int trigPin = 11;
const int echoPin = 12;

// --- LED & BUZZER ---
const int ledPin = 13;
const int buzzerPin = 10;

// --- Reset Butonu ---
#define resetButon A0

// --- Değişkenler ---
String yasStr = "";
String kiloStr = "";
int adim = 0;
float suIhtiyaci = 0;
float suSeviyesi = 0;
float oncekiSuSeviyesi = -1;
unsigned long sonIcilmeZamani = 0;

// --- Menü Kontrolü ---
int menuIndex = 0;
const int toplamMenu = 1; // Menü 0 ve 1 var

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(resetButon, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Yas girin:");
}

void loop() {
  char key = keypad.getKey();

  // --- Reset Butonu Sadece Buzzer Susturur ve Sistemi Sıfırlar ---
  if (digitalRead(resetButon) == LOW) {
    lcd.clear();
    lcd.print("RESET...");
    delay(1000);

    yasStr = "";
    kiloStr = "";
    suIhtiyaci = 0;
    suSeviyesi = 0;
    oncekiSuSeviyesi = -1;
    sonIcilmeZamani = millis();
    adim = 0;
    menuIndex = 0;

    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Yas girin:");
    delay(500);
    return;
  }

  // --- Giriş Adımları ---
  if (adim == 0 && key != NO_KEY) {
    if (key == '#') {
      adim = 1;
      lcd.clear();
      lcd.print("Kilo girin:");
    } else if (isDigit(key)) {
      yasStr += key;
      lcd.setCursor(0, 1);
      lcd.print(yasStr);
    }
  } else if (adim == 1 && key != NO_KEY) {
    if (key == '#') {
      int kilo = kiloStr.toInt();
      suIhtiyaci = kilo * 35.0 / 1000.0; // litre
      adim = 3;
      lcd.clear();
    } else if (isDigit(key)) {
      kiloStr += key;
      lcd.setCursor(0, 1);
      lcd.print(kiloStr);
    }
  }

  // --- Ölçüm ve Menü Gösterimi ---
  if (adim == 3) {
    float distance = mesafeOku();
    suSeviyesi = 2.0 * (1.0 - (distance / 25.0)); // 25 cm'lik şişeye göre
    if (suSeviyesi < 0) suSeviyesi = 0;
    if (suSeviyesi > 2.0) suSeviyesi = 2.0;

    // Menü Geçiş Tuşları
    if (key == '*') {
      menuIndex--;
      if (menuIndex < 0) menuIndex = toplamMenu;
      lcd.clear();
    } else if (key == '#') {
      menuIndex++;
      if (menuIndex > toplamMenu) menuIndex = 0;
      lcd.clear();
    }

    // LCD Menü
    if (menuIndex == 0) {
      lcd.setCursor(0, 0);
      lcd.print("Gunluk Hedef:");
      lcd.setCursor(0, 1);
      lcd.print(suIhtiyaci, 2);
      lcd.print(" L");
    } else if (menuIndex == 1) {
      lcd.setCursor(0, 0);
      lcd.print("Sulukta:");
      lcd.setCursor(0, 1);
      lcd.print(suSeviyesi, 2);
      lcd.print(" L");
    }

    // --- Uyarı Sistemi ---
    if (abs(suSeviyesi - oncekiSuSeviyesi) > 0.05) {
      sonIcilmeZamani = millis(); // su içildi, süreyi sıfırla
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);
    }

    if (millis() - sonIcilmeZamani > 60000) { // 1 dakika geçerse
      digitalWrite(ledPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
    }

    oncekiSuSeviyesi = suSeviyesi;
    delay(1000);
  }
}

// --- HC-SR04 Fonksiyonu ---
float mesafeOku() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long sure = pulseIn(echoPin, HIGH);
  float mesafe = sure * 0.034 / 2.0;
  return mesafe;
}
