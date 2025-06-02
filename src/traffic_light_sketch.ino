// Pin Definitions for Traffic Light LEDs
const int redPin = 7;    // D7 - Red LED
const int yellowPin = 6; // D6 - Yellow LED
const int greenPin = 5;  // D5 - Green LED

// Timing (in milliseconds)
const unsigned long redTimer = 5000;    // 5 seconds
const unsigned long yellowTimer = 2000; // 2 seconds
const unsigned long greenTimer = 5000;  // 5 seconds

// State Machine for Traffic Light
typedef enum {RED = 0, YELLOW, GREEN} traffic_light_state_t;
traffic_light_state_t state = RED;

// Timing Variables
unsigned long previousMillis = 0; // Last state change time
unsigned long currentTimer = 0;   // Duration of current state

void setup() {
  // Initialize Traffic Light LED Pins
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void setTrafficLight(bool red, bool yellow, bool green) {
  // Set the traffic light LEDs
  digitalWrite(redPin, red ? HIGH : LOW);
  digitalWrite(yellowPin, yellow ? HIGH : LOW);
  digitalWrite(greenPin, green ? HIGH : LOW);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // State machine with non-blocking timing
  switch (state) {
    case RED:
      setTrafficLight(true, false, false); // Red ON
      currentTimer = redTimer;
      if (currentMillis - previousMillis >= redTimer) {
        state = GREEN;
        previousMillis = currentMillis;
      }
      break;

    case YELLOW:
      setTrafficLight(false, true, false); // Yellow ON
      currentTimer = yellowTimer;
      if (currentMillis - previousMillis >= yellowTimer) {
        state = RED;
        previousMillis = currentMillis;
      }
      break;

    case GREEN:
      setTrafficLight(false, false, true); // Green ON
      currentTimer = greenTimer;
      if (currentMillis - previousMillis >= greenTimer) {
        state = YELLOW;
        previousMillis = currentMillis;
      }
      break;

    default:
      setTrafficLight(false, false, false); // All OFF
      state = RED;
      previousMillis = currentMillis;
      break;
  }
}