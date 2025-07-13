/*

ButtonLib Example: ESP32
Demonstrates the usage of esp32 platform-specific properties,
like lambda functions for button callbacks

See the main_example for more details on how to use the library.

Created by IlikeChooros
License: MIT License
*/

#include <ButtonLib.h>

Button button(25); // Button on GPIO 25, by defeault uses INPUT_PULLUP mode

void setup() {
    Serial.begin(9600);

    // Initialize the button's pin mode and internal state, 
    // The order here is not important, but it's good practice to call begin() before setting callbacks
    button.begin();

    // Use of lambda functions for callbacks
    button.onPress([]() {
        Serial.println("Button Pressed!");
    }).onRelease([]() {
        Serial.println("Button Released!");
    }).onHold([]() {
        Serial.println("Button Held!");
    });

    // Alternatively, you can use named functions for callbacks
    // button.onPress(onPress).onRelease(onRelease).onHold(onHold);
}

void loop() {
    button.read();
}

// Define the callbacks for button events
void onPress() {
    Serial.println("Button Pressed!");
}

void onRelease() {
    Serial.println("Button Released!");
}

// Will be called frequently after the initial countdown (by default ~1second)
void onHold() {
    Serial.println("Button Held!");
}