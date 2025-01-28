#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BleKeyboard.h>

// Pin Definitions
#define BUTTON_LEFT 16
#define BUTTON_RIGHT 17
#define BUTTON_SEL 25

// Driver config
const int table_dirPin = 23;
const int table_stepPin = 12; // for tilting (big "table")
const int stand_dirPin = 27;
const int stand_stepPin = 14; // for rotation (small "stand")

const int steps_per_revolution = 200 * 16; // using 1/16 microstepping
const float ratio = 5.33333; // gear ratio between the stepper spock and the big arm spock

// Timings
const int step_delay_us = 350;
const int pose_delay_ms = 750;

// OLED Display Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Menu States
enum MenuState { MENU, COUNTING, CONNECTING };
enum MenuItem { START, TILT_CHANGES, TILT_ANGLE, P360, SPIRAL, SHRINK, NUM_ITEMS };

// Configuration Structure
struct Config {
  uint8_t tilt_changes = 2;    // Number of layers (0,1,2,3)
  uint8_t tilt_angle = 30;     // Layer angle increment (20,30,40 degrees)
  uint8_t p360 = 60;           // Pictures per full rotation (40,50,60,80)
  bool spiral = false;         // Spiral mode
  uint8_t shrink = 10;         // Layer shrink percentage
} config;

// Global Variables
MenuState currentState = CONNECTING;
MenuItem currentItem = START;
unsigned long countStartTime = 0;
uint16_t total_pictures = 0;
uint16_t current_picture = 0;
bool displayNeedsUpdate = true;
uint8_t current_layer = 0;
uint16_t current_layer_p360 = 0;
uint16_t pictures_in_layer = 0;

// Button Debounce Settings
#define DEBOUNCE_DELAY 50
unsigned long lastDebounceTime = 0;
int lastLeftState = HIGH;
int lastRightState = HIGH;
int lastSelState = HIGH;

// Bluetooth HID
BleKeyboard bleKeyboard("ESP32 Keyboard", "Manufacturer", 100);

void setup() {
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_SEL, INPUT_PULLUP);

  pinMode(table_stepPin, OUTPUT);
  pinMode(table_dirPin, OUTPUT);
  pinMode(stand_stepPin, OUTPUT);
  pinMode(stand_dirPin, OUTPUT);

  Wire.begin(33, 32);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) while (1);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  updateDisplay();

  bleKeyboard.begin();
}

void rotateStepper(int stepPin, int dirPin, int steps, bool direction) {
  digitalWrite(dirPin, direction);
  for (int i = 0; i < abs(steps); i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(step_delay_us);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(step_delay_us);
  }
}

void tiltTable(int angle) {
  int steps = angle * (steps_per_revolution / 360.0) * ratio;
  rotateStepper(table_stepPin, table_dirPin, steps, HIGH);
}

void handleCountingState() {
  if (currentState == COUNTING && current_picture < total_pictures) {
    delay(pose_delay_ms);
    if (bleKeyboard.isConnected()) bleKeyboard.write(KEY_RETURN);
    current_picture++;
    pictures_in_layer++;
    displayNeedsUpdate = true;
    delay(pose_delay_ms);

    if (pictures_in_layer >= current_layer_p360) {
      pictures_in_layer = 0;
      if (current_layer < config.tilt_changes) {
        tiltTable(config.tilt_angle);
        current_layer++;
        if (config.spiral) {
          current_layer_p360 = round(current_layer_p360 * (100.0 - config.shrink) / 100.0);
          if (current_layer_p360 < 1) current_layer_p360 = 1;
        }
      } else {
        current_layer = 0;
        pictures_in_layer = 0;
        currentState = MENU;
        display.setTextSize(2);
        displayNeedsUpdate = true;
      }
    } else {
      int steps = steps_per_revolution / current_layer_p360;
      rotateStepper(stand_stepPin, stand_dirPin, steps, HIGH);
    }
  }
}

void handleNavigation(int left, int right, int sel) {
  switch (currentState) {
    case MENU:
      if (left == LOW && lastLeftState == HIGH) {
        currentItem = static_cast<MenuItem>((currentItem + NUM_ITEMS - 1) % NUM_ITEMS);
        displayNeedsUpdate = true;
      }
      if (right == LOW && lastRightState == HIGH) {
        currentItem = static_cast<MenuItem>((currentItem + 1) % NUM_ITEMS);
        displayNeedsUpdate = true;
      }
      if (sel == LOW && lastSelState == HIGH) {
        if (currentItem == START) {
          currentState = COUNTING;
          current_layer = 0;
          pictures_in_layer = 0;
          current_layer_p360 = config.p360;
          
          if (config.spiral) {
            total_pictures = 0;
            float layer_p360 = config.p360;
            for (int i = 0; i <= config.tilt_changes; i++) {
              total_pictures += round(layer_p360);
              layer_p360 *= (100.0 - config.shrink) / 100.0;
              if (layer_p360 < 1) layer_p360 = 1;
            }
          } else {
            total_pictures = (config.tilt_changes + 1) * config.p360;
          }
          current_picture = 0;
          countStartTime = millis();
        } else {
          cycleSettingValue();
        }
        displayNeedsUpdate = true;
      }
      break;

    case COUNTING:
      if ((left == LOW && lastLeftState == HIGH) ||
          (right == LOW && lastRightState == HIGH) ||
          (sel == LOW && lastSelState == HIGH)) {
        currentState = MENU;
        current_layer = 0;
        pictures_in_layer = 0;
        display.setTextSize(2);
        displayNeedsUpdate = true;
      }
      break;
  }

  lastLeftState = left;
  lastRightState = right;
  lastSelState = sel;
}

void cycleSettingValue() {
  switch (currentItem) {
    case TILT_CHANGES:
      config.tilt_changes = (config.tilt_changes + 1) % 4;
      break;
    case TILT_ANGLE:
      config.tilt_angle = (config.tilt_angle == 20) ? 30 : (config.tilt_angle == 30) ? 40 : 20;
      break;
    case P360:
      config.p360 = (config.p360 == 40) ? 50 : (config.p360 == 50) ? 60 : (config.p360 == 60) ? 80 : 40;
      break;
    case SPIRAL:
      config.spiral = !config.spiral;
      break;
    case SHRINK:
      config.shrink += 5;
      if (config.shrink > 20) config.shrink = 0;
      break;
    default: break;
  }
}

void updateDisplay() {
  display.clearDisplay();
  switch (currentState) {
    case CONNECTING:
      display.setCursor(0, 0);
      display.println("Connecting...");
      break;

    case MENU:
      display.setCursor(0, 0);
      switch (currentItem) {
        case START:
          display.println("START");
          break;
        case TILT_CHANGES:
          display.print("Layers:");
          display.println(config.tilt_changes);
          break;
        case TILT_ANGLE:
          display.print("Tilt angle:");
          display.print(config.tilt_angle);
          display.println("°");
          break;
        case P360:
          display.print("P360:");
          display.println(config.p360);
          break;
        case SPIRAL:
          display.print("Spiral:");
          display.println(config.spiral ? "Y" : "N");
          break;
        case SHRINK:
          display.print("Shrink:");
          display.print(config.shrink);
          display.println("%");
          break;
      }
      break;

    case COUNTING:
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.printf("%d/%d", current_picture, total_pictures);
      display.setTextSize(1);
      display.setCursor(0, 24);
      display.println("Press any to stop");
      break;
  }
  display.display();
  displayNeedsUpdate = false;
}

void loop() {
  int leftState = digitalRead(BUTTON_LEFT);
  int rightState = digitalRead(BUTTON_RIGHT);
  int selState = digitalRead(BUTTON_SEL);

  if (millis() - lastDebounceTime > DEBOUNCE_DELAY) {
    handleNavigation(leftState, rightState, selState);
    lastDebounceTime = millis();
  }

  if (displayNeedsUpdate) updateDisplay();

  if (currentState == CONNECTING) {
    if (bleKeyboard.isConnected()) {
      display.setTextSize(2);
      currentState = MENU;
      displayNeedsUpdate = true;
    }
  } else {
    handleCountingState();
  }
}
