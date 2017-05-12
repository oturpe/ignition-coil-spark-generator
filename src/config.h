// This is the configuration file. Ideally, any configuration and calibration
// of the device should be done by changing this file only.

// Needed by util/delay.h
#define F_CPU 16000000UL

// Delay between two executions of main loop, given in millisecond.
#define LOOP_DELAY 10

// Definition of indicator pin data direction and data ports and pins
#define INDICATOR_DATA_DIR DDRD
#define INDICATOR_DATA_DIR_PIN DDD6
#define INDICATOR_DATA PORTD
#define INDICATOR_DATA_PIN PORTD6

// Half length of one complete indicator period. In other words, the time the
// indicator spends on and off. Given in units of LOOP_DELAY.
#define INDICATOR_HALF_PERIOD 20

// Length of one tone in sequence. Given in units of LOOP_DELAY
#define TONE_PERIOD 14
// Frequency of the lowest possible frequency
#define TONE_MINIMUM_FREQUENCY 50
// Ration between two consecutive intervals. Value of 1.0595 gives 12 steps per
// octave.
#define TONE_INTERVAL_RATIO 1.0595;
// Amount of tones in the range
#define TONE_RANGE 60
