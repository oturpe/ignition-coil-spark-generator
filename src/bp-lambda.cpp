#include "config.h"
#include "bp-lambda.h"

#include <stdlib.h>

#define STEPS_COUNT 10

// Relative frequency of tones
static float steps[STEPS_COUNT] = {
    1.0000,
    1.1841,
    1.2886,
    1.4022,
    1.6604,
    1.8068,
    2.1395,
    2.3282,
    2.7569,
    3.0000
};

static float stepsInverted[STEPS_COUNT] = {
    1.0000,
    0.9190,
    0.7761,
    0.7132,
    0.6023,
    0.5535,
    0.4674,
    0.4295,
    0.3947,
    0.3333
};

uint8_t Bp::nextNote(uint8_t currentNote) {
    int8_t jumpDirection = (rand() % 3) - 1;
    int8_t steps = rand() % BP_TONE_JUMP_MAX;

    uint8_t nextNote = currentNote + (jumpDirection * steps);
    if (nextNote < BP_TONE_MIN) {
        return BP_TONE_MIN;
    }
    else if (nextNote > BP_TONE_MAX) {
        return BP_TONE_MAX;
    }

    return nextNote;
}

uint16_t Bp::frequency(uint8_t note) {
    int8_t distance = note - BP_TONE_BASE_STEP;
    uint16_t frequency = BP_TONE_BASE_FREQUENCY;

    float * stepsDirected = steps;
    // If requested note is below base note, use lowering steps.
    if (distance < 0) {
        stepsDirected = stepsInverted;
        distance *= -1;
    }

    while (distance > STEPS_COUNT - 1) {
        frequency *= stepsDirected[STEPS_COUNT - 1];
        distance -= STEPS_COUNT - 1;
    }

    return frequency *=stepsDirected[distance];
}
