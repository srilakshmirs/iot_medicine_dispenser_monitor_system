#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUZZER_PIN 26
#define BUTTON_PIN 4

unsigned long lastReminder = 0;
unsigned long alertStartTime = 0;
unsigned long lastBuzzToggleTime = 0;
unsigned long secondReminderStart = 0;
unsigned long doseConfirmationTime = 0;

const unsigned long reminderInterval = 5 * 60 * 1000; // 5 minutes
const unsigned long alertDuration = 10000; // 10 seconds
const unsigned long retryDelay = 60000; // 1 minute

bool buzzerState = false;
bool isAlerting = false;
bool stopAlert = false;
bool medicineTaken = false;
bool secondReminderScheduled = false;
bool showReminderText = false;

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print("Medicine Reminder");
  display.display();
  delay(2000);
}

void loop() {
  unsigned long currentTime = millis();

  // If it's time for the next scheduled dose
  if (currentTime - lastReminder >= reminderInterval) {
    // Reset all flags
    medicineTaken = false;
    stopAlert = false;
    secondReminderScheduled = false;
    isAlerting = false;

    triggerReminder();
    lastReminder = currentTime;
  }

  // Background buzzer handler
  handleAlert();

  // Retry second reminder after 1 minute if dose not confirmed
  if (!medicineTaken && !isAlerting && secondReminderScheduled && (currentTime - secondReminderStart >= retryDelay)) {
    triggerReminder();  // Second alert
    secondReminderScheduled = false;
  }

  // Button press check
  if (digitalRead(BUTTON_PIN) == LOW && !medicineTaken) {
    stopAlert = true;
    medicineTaken = true;
    isAlerting = false;
    secondReminderScheduled = false;
    confirmDose();
  }

  if (showReminderText && millis() - doseConfirmationTime >= 10000) {
    display.clearDisplay();
    display.setCursor(0, 10);
    display.print("Medicine Reminder");
    display.display();
    showReminderText = false;
  }
}

void triggerReminder() {
  stopAlert = false;
  isAlerting = true;
  alertStartTime = millis();
  lastBuzzToggleTime = 0;
  buzzerState = false;
  displayMessage();
}

void displayMessage() {
  display.clearDisplay();
  display.setCursor(0, 10);
  display.print("Time to take medicine!");
  display.display();
}

void confirmDose() {
  stopAlert = true;
  isAlerting = false;
  noTone(BUZZER_PIN); // FORCE buzzer off

  display.clearDisplay();
  display.setCursor(0, 10);
  display.print("Dose taken!");
  display.display();

  doseConfirmationTime = millis();  // Save the time
  showReminderText = true;
}

void handleAlert() {
  if (!isAlerting) return;

  unsigned long currentTime = millis();

  if (stopAlert || currentTime - alertStartTime >= alertDuration) {
    noTone(BUZZER_PIN);
    isAlerting = false;

    if (!medicineTaken && !secondReminderScheduled) {
      secondReminderStart = millis();
      secondReminderScheduled = true;
    }

    return;
  }

  if (currentTime - lastBuzzToggleTime >= 300) {
    if (buzzerState) {
      noTone(BUZZER_PIN);
    } else {
      tone(BUZZER_PIN, 1000);
    }
    buzzerState = !buzzerState;
    lastBuzzToggleTime = currentTime;
  }
}