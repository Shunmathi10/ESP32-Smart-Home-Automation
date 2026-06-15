#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// ===== OLED =====
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

// ===== LEDs =====
#define LED1 18      // Room Light
#define LED2 19      // Bedroom Light
#define LED3 23      // Fan (moved from GPIO21)

// ===== Buttons =====
#define BTN1 25
#define BTN2 26
#define BTN3 33      // Optional manual fan button

// ===== Sensors =====
#define LDR_PIN 34

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// ===== States =====
bool roomLight = false;
bool bedroomLight = false;

void setup() {

  Serial.begin(115200);

  // LEDs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // Buttons
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);

  // DHT
  dht.begin();

  // OLED
  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Failed");
    while (true);
  }

  display.clearDisplay();
  display.display();
}

void loop() {

  // ==========================
  // BUTTON 1 - ROOM LIGHT
  // ==========================
  if (digitalRead(BTN1) == LOW) {

    roomLight = !roomLight;
    digitalWrite(LED1, roomLight);

    while (digitalRead(BTN1) == LOW);
    delay(50);
  }

  // ==========================
  // BUTTON 2 - BEDROOM LIGHT
  // ==========================
  if (digitalRead(BTN2) == LOW) {

    bedroomLight = !bedroomLight;
    digitalWrite(LED2, bedroomLight);

    while (digitalRead(BTN2) == LOW);
    delay(50);
  }

  // ==========================
  // LDR READING
  // ==========================
  int lightValue = analogRead(LDR_PIN);

  bool isDark = (lightValue > 700);
  if (isDark) {
  digitalWrite(LED1, HIGH);
}
else {
  digitalWrite(LED1, LOW);
}

  // ==========================
  // DHT22 READING
  // ==========================
  float temp = dht.readTemperature();

  // ==========================
  // FAN AUTOMATION
  // ==========================
  bool fanOn = false;

  if (temp > 30) {
    digitalWrite(LED3, HIGH);
    fanOn = true;
  }
  else {
    digitalWrite(LED3, LOW);
    fanOn = false;
  }

  // ==========================
  // SERIAL MONITOR
  // ==========================
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C  ");

  Serial.print("Light: ");
  Serial.print(lightValue);

  Serial.print("  Fan: ");
  Serial.println(fanOn ? "ON" : "OFF");

  // ==========================
  // OLED DISPLAY
  // ==========================
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temp);
  display.println(" C");

  display.setCursor(0, 12);
  display.print("Fan : ");
  display.println(fanOn ? "ON" : "OFF");

  display.setCursor(0, 24);
  display.print("Room: ");
  display.println(roomLight ? "ON" : "OFF");

  display.setCursor(0, 36);
  display.print("Bed : ");
  display.println(bedroomLight ? "ON" : "OFF");

  display.setCursor(0, 48);
  display.print("Light: ");
  display.println(isDark ? "DARK" : "BRIGHT");

  display.display();

  delay(500);
}