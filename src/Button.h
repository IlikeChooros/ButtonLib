#pragma once

#include <Arduino.h>

#define DEBOUNCE_DELAY 50 // 50ms debounce delay
#define HOLD_TIME_DEFAULT 900 // Default hold time in milliseconds (after this delay, the callback will be rapidly triggered)
#define HOLD_RAPID_DELAY 20 // delay between rapid callbacks

namespace internal {
    #if defined(ESP32) || defined(ESP8266)
        // If that's an ESP32 or ESP8266, we can use the built-in functions

        #include <functional>
        // for callbacks, otherwise we need to define our own
        typedef std::function<void()> callback_t;

    #else 
        // For other platforms, we define a simple callback type
        typedef void (*callback_t)();
    #endif
}

class Button {
public:
    static constexpr unsigned int debounceDelay = DEBOUNCE_DELAY;
    static constexpr unsigned int holdTimeDefault = HOLD_TIME_DEFAULT;
    static constexpr unsigned int holdRapidDelay = HOLD_RAPID_DELAY;
    
    // For the future, I might add more modes, but for now I'll use just two:
    enum ButtonPinMode {
        MODE_INPUT_PULLUP,
        MODE_INPUT
    };

    // Hold button constructor
    Button(int pin, ButtonPinMode mode = MODE_INPUT_PULLUP)
    {
        m_state.pin = pin;
        m_state.mode = int(mode);
    }

    // Initialize the button, setting the pin mode and initial state
    void begin();

    // Read the button state, and possibly trigger the callback
    void read();

    // Set the on press callback
    Button& onPress(internal::callback_t callback) {
        m_on_press = callback;
        return *this;
    }

    // Set the on release callback, also called at the end of a hold
    Button& onRelease(internal::callback_t callback) {
        m_on_release = callback;
        return *this;
    }

    // Set the on hold callback, called repeatedly while the button is held
    Button& onHold(internal::callback_t callback) {
        m_on_hold = callback;
        return *this;
    }

private:

    struct pin_state_t {
        unsigned int pin: 26;
        unsigned int mode: 2;
        unsigned int state: 1;
        unsigned int last_state: 1;
        unsigned int pressed_state: 1;
        unsigned int hold_state: 1;
        unsigned int last_debounce_time;
        unsigned int current_hold_time;
        unsigned int last_hold_timer;
    } m_state;

    internal::callback_t m_on_press{nullptr}, 
                          m_on_release{nullptr},
                          m_on_hold{nullptr};
};
