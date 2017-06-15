// Firmware for device triggering and generating tones with a car induction
// coil.
//
// Author: Otto Urpelainen / Koelse
// Email: oturpe@iki.fi
// Date: 2017-05-09

#include "AvrUtils.h"

#include "config.h"

#include "bp-lambda.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

uint32_t indicatorCounter = 0;

/// \brief
///    Toggles the indicator led state.
void toggleIndicator() {
    static bool lit;

    if (lit) {
        INDICATOR_DATA &= ~BV(INDICATOR_DATA_PIN);
    }
    else {
        INDICATOR_DATA |= BV(INDICATOR_DATA_PIN);
    }

    lit = !lit;
}

// Value of timer 1 prescaler. Set this value when prescaler value is changed.
uint16_t prescaler;

/// \brief
///    Initializes spark trigger to run as 50 % duty cycle pwm. Frequency is
///    set using function setSparkFrequency().
void initializeSparkTrigger() {
    // Set oscillator
    // Fast pwm, TOP = OCR1A
    TCCR1B |= BV(WGM13) | BV(WGM12);
    TCCR1A |= BV(WGM11) | BV(WGM10);

    // Prescaler
    TCCR1B |= BV(CS11) | BV(CS10);
    prescaler = 64;

    // Clear on compare match
    TCCR1A |= BV(COM1A0);

    // Set oscillator pin to output
    DDRB |= BV(DDB5);
}

/// \brief
///    Sets spark frequency to given value.
///
/// \param frequency
///    Spark frequency in units of Hertz
void setSparkFrequency(uint16_t frequency) {
    const uint32_t stepFrequency = F_CPU / prescaler;

    uint32_t steps = (stepFrequency / frequency) / 2;

    OCR1A = steps;
}

int main() {
    INDICATOR_DATA_DIR |= BV(INDICATOR_DATA_DIR_PIN);

    initializeSparkTrigger();

    uint16_t frequencyCounter = 0;
    uint8_t note = BP_TONE_BASE_STEP;

    while (true) {
        // Set spark tone
        if (frequencyCounter == TONE_PERIOD) {
            note = Bp::nextNote(note);
            setSparkFrequency(Bp::frequency(note));

            frequencyCounter = 0;
        }
        else {
            frequencyCounter++;
        }

        // Flash indicator
        if (indicatorCounter == INDICATOR_HALF_PERIOD) {
            toggleIndicator();
            indicatorCounter = 0;
        }
        else {
            indicatorCounter++;
        }

        _delay_ms(LOOP_DELAY);
    }
}
