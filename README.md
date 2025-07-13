# ButtonLib

A simple and memory-efficient library for handling buttons in Arduino projects.
Allows custom delays for debouncing, as well as short and long hold delays.
Suppors both INPUT_PULLUP and INPUT modes.

## Example Usage

On any device:
```cpp
#include <ButtonLib.h>

Button button(2); // Button on pin 2, by defeault uses INPUT_PULLUP mode
// So the user should connect one leg of the button to pin 2 and the other to GND

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

void setup() {
    Serial.begin(9600);

    // Initialize the button's pin mode and internal state
    button.begin();
    button.onPress(onPress).onRelease(onRelease).onHold(onHold);
}

void loop() {
    button.read();
}
```

## Features
- **Debouncing**: Automatically handles button debouncing with customizable delay.
- **Callbacks**: Supports custom callbacks for button press, release, and hold events.
- **Pin Modes**: Allows setting the pin mode to either `INPUT_PULLUP` or `INPUT`.
- **Memory Efficient**: Designed to be lightweight, minimizing memory usage.
- **Customizable**: Users can set custom hold times and debounce delays.

## Installation
1. Download the library from the release page.
2. Extract the contents to your `Arduino/libraries` directory.
3. Restart the Arduino IDE if it was open during installation.
4. Include the library in your sketch with `#include <ButtonLib.h>`. 


  

