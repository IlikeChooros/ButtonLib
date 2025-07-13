/*

This example demonstrates how to use the Button library to handle button presses
with callbacks for press, release, and hold events.

Created by IlikeChooros
License: MIT License

*/

// Uncomment the following lines to change the default values
// #define DEBOUNCE_DELAY 50
// #define HOLD_TIME_DEFAULT 900 // Default hold time in milliseconds (after this delay, the callback
// will be rapidly triggered)
// #define HOLD_RAPID_DELAY 20 // delay between rapid callbacks


#include <ButtonLib.h>

// This is only a suggestion, you can change the pin number to any other digital pin
// Diagram:
// 
//  +-----------------+
//  |                 |
//  |    Arduino      |
//  | A3 A2    GND V5 |
//  +-----------------+
//    |   |     |   |
//    |   |     |   |
//    |   +-BTN-+   |
//    |             |
//    +-----BTN-----+
// You should connect one leg of the button to pin 2 and the other to GND
Button button(2); // Button on pin 2, by defeault uses INPUT_PULLUP mode
Button button2; // will be initialized in setup

// You may also use the following constructor to set the pin mode explicitly
// Button button(2, Button::MODE_INPUT); // Button on pin 2, uses
// INPUT mode, which means the button will be pressed when the pin is HIGH
// Button button2(3, Button::MODE_INPUT_PULLUP); // Button on pin 3, uses INPUT_PULLUP mode

// Define the callbacks for button events
bool heldForFirstSecond = false; // Flag to check if the first second has passed

void onPress() {
    Serial.println("Button Pressed!");
}

void onPress2() {
    Serial.println("Button2 Pressed!");
}

void onRelease() {
    Serial.print("Button released after ");
    Serial.print(button.holdTime());
    Serial.println(" milliseconds");
    heldForFirstSecond = false;
}

// Will be called frequently after the initial countdown (by default ~1second)
void onHold() {
    Serial.println("Button Held!");

    if (button.heldFor(1000) && !heldForFirstSecond) {
        Serial.println("More than 1 second");
        heldForFirstSecond = true; // Prevents printing this message again
    }
}

void setup() {
    // If you are using a board like ESP32, you might want to change the baud rate
    // to a higher value, like 115200
    Serial.begin(9600);
    Serial.println("ButtonLib Example: Multiple Buttons");
    
    button2 = Button(3, Button::MODE_INPUT_PULLUP); // Button on pin 3, uses INPUT_PULLUP mode
    button2.begin();
    button2.onPress(onPress2); // Set the callback for button2 press

    // Initialize the button's pin mode and internal state
    button.begin();
    button.onPress(onPress).onRelease(onRelease).onHold(onHold);
}

void loop() {
    button.read();
    button2.read();
}