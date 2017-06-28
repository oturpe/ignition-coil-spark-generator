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

// The number of individual sparks making tones
#define SPARK_COUNT 2
// Length of one tone in sequence for spark 0. Given in units of LOOP_DELAY
#define SPARK_PERIOD_0 14
// Length of one tone in sequence for spark 1. Given in units of LOOP_DELAY
#define SPARK_PERIOD_1 13

// Time needed to charge spark plug. Given as the number of times the plug can
// be loaded in one seconds (i.e. 1/T) 
#define SPARK_LOAD_FREQUENCY 5000

// Frequency of base tone of Bohlen-Pierce scale, α3 (39)
#define BP_TONE_BASE_FREQUENCY 440
// Lowest possible tone
#define BP_TONE_MIN 13
// Highest possible tone, as lambda mode steps above the base tone
#define BP_TONE_MAX 65
// Largest possible jump between two consecutive tones
#define BP_TONE_JUMP_MAX 7
