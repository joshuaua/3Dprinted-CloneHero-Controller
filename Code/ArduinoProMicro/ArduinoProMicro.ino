#include "src/Joystick/Joystick.h"

// #define DEBUG

#define PLAYER_1 0x03
#define PLAYER_2 0x04
#define PLAYER_3 0x05
#define PLAYER_4 0x06

Joystick_ Guitar(
  PLAYER_1,               // Change this for each controller connected to one computer
  JOYSTICK_TYPE_GAMEPAD,
  9, 0,                   // 9 buttons, no hat switches
  false, false, false,    // No X, Y or Z axis
  false, false, false,    // No Rx, Ry, or Rz
  false, false,           // No rudder or throttle
  false, false, false     // No accelerator, brake, or steering
);

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif

  // Set all buttons to use internal pullup resistors
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

  Guitar.begin();
}

// Last press state of the buttons
int lastButtonState[9] = {0,0,0,0,0,0,0,0,0};
// Temporary variable for looped button's state
int currentButtonState = 0;

// TODO: Set up a consistent 1ms delay between loops?

void loop() {
  // For each button
  for (int index = 0; index < 9; index++)
  {
    // We use the opposite value because pins are pulled UP by default
    currentButtonState = !digitalRead(index + 1);
    // Send a button event to the computer only once per press/unpress
    if (currentButtonState != lastButtonState[index])
    {
      #ifdef DEBUG
      Serial.print("Button ");
      Serial.print(index + 1);
      Serial.print(" set to ");
      Serial.println(currentButtonState);
      #endif
      Guitar.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }
}
