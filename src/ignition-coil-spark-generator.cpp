// Firmware for device triggering and generating tones with a car induction
// coil.
//
// Author: Otto Urpelainen / Koelse
// Email: oturpe@iki.fi
// Date: 2017-05-09

#include "config.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "AtmegaU4Utils.h"


#include "bp-lambda.h"

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

/// \brief
///    Initializes spark triggers to run as variable frequency pwm with fixed
///    ON period. Frequency is set using function setSparkFrequency() while
///    the ON period is fixed here to match properties of the ignition coil
///    used.
void initializeSparkTrigger() {
    // Set oscillator
    // Fast pwm, TOP = OCR1A
    TCCR0B |= BV(WGM02);
    TCCR0A |= BV(WGM01) | BV(WGM00);

    TCCR1B |= BV(WGM13) | BV(WGM12);
    TCCR1A |= BV(WGM11) | BV(WGM10);

    // Prescaler
    // TODO: Check that these new definitions work
    // TODO: Move the storage and query of prescaler value to AtmegaU4Utils
    AtmegaU4::setTimer0Prescaler(AtmegaU4::PSV_1024);

    AtmegaU4::setTimer1Prescaler(AtmegaU4::PSV_64);

    // Clear on compare match, set on TOP
    TCCR0A |= BV(COM0B1);

    TCCR1A |= BV(COM1B1);

    // Set ON period
    OCR0B = (F_CPU / AtmegaU4::timer0Prescaler()) / SPARK_LOAD_FREQUENCY;

    OCR1B = (F_CPU / AtmegaU4::timer1Prescaler()) / SPARK_LOAD_FREQUENCY;

    // Set oscillator pin to output
    DDRD |= BV(DDD0);

    DDRB |= BV(DDB6);
}

/// \brief
///    Sets both outputs to logic low.
void disableOutputs() {
    // Disable pwm outputs
    TCCR0A &= ~BV(COM0B1);

    TCCR1A &= ~BV(COM1B1);

    // Set outputs to low
    PORTD &= ~BV(PORTD0);

    PORTB &= ~BV(PORTB6);
}

/// \brief
///    Connects outputs to pwm timers.
void enableOutputs() {
    // Enable pwm outputs
    TCCR0A |= BV(COM0B1);

    TCCR1A |= BV(COM1B1);
}

/// \brief
///    Sets spark 0 frequency to given value.
///
/// \param frequency
///    Spark frequency in units of Hertz
void setSpark0Frequency(uint16_t frequency) {
    const uint32_t stepFrequency = F_CPU / AtmegaU4::timer0Prescaler();

    uint32_t steps = stepFrequency / frequency;

    OCR0A = steps;
}

/// \brief
///    Sets spark 1 frequency to given value.
///
/// \param frequency
///    Spark frequency in units of Hertz
void setSpark1Frequency(uint16_t frequency) {
    const uint32_t stepFrequency = F_CPU / AtmegaU4::timer1Prescaler();

    uint32_t steps = stepFrequency / frequency;

    OCR1A = steps;
}

int main() {
    INDICATOR_DATA_DIR |= BV(INDICATOR_DATA_DIR_PIN);

    initializeSparkTrigger();

    uint16_t cooldownCounter = 0;
    bool isCooling = false;

    uint16_t sparkCounter[2] = {0, 0};
    // The current note for the two oscillators
    uint8_t notes[2] = {
        BP_TONE_BASE_STEP,
        BP_TONE_BASE_STEP
    };

    while (true) {
        // Set spark 0 tone
        if (sparkCounter[0] == SPARK_PERIOD_0) {
            notes[0] = Bp::nextNote(notes[0]);
            setSpark0Frequency(Bp::frequency(notes[0]));

            sparkCounter[0] = 0;
        }
        else {
            sparkCounter[0]++;
        }

        // Set spark 1 tone
        if (sparkCounter[1] == SPARK_PERIOD_1) {
            notes[1] = Bp::nextNote(notes[1]);
            setSpark1Frequency(Bp::frequency(notes[1]));

            sparkCounter[1] = 0;
        }
        else {
            sparkCounter[1]++;
        }

        // Flash indicator
        if (indicatorCounter == INDICATOR_HALF_PERIOD) {
            toggleIndicator();
            indicatorCounter = 0;
        }
        else {
            indicatorCounter++;
        }

        if (isCooling && cooldownCounter == COOLDOWN_PERIOD_OFF) {
            enableOutputs();

            isCooling = false;
            cooldownCounter = 0;
        }
        else if (!isCooling && cooldownCounter == COOLDOWN_PERIOD_ON) {
            disableOutputs();

            isCooling = true;
            cooldownCounter = 0;
        }
        else {
            cooldownCounter++;
        }

        _delay_ms(LOOP_DELAY);
    }
}
