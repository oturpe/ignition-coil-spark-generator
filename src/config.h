// This is the configuration file. Ideally, any configuration and calibration
// of the device should be done by changing this file only.

// Needed by util/delay.h
#define F_CPU 16000000UL

// Delay between two executions of main loop, given in millisecond.
#define LOOP_DELAY 100

// Definition of indicator pin data direction and data ports and pins
#define INDICATOR_DATA_DIR DDRC
#define INDICATOR_DATA_DIR_PIN DDC7
#define INDICATOR_DATA PORTC
#define INDICATOR_DATA_PIN PORTC7

// Half length of one complete indicator period. In other words, the time the
// indicator spends on and off. Given in units of LOOP_DELAY.
#define INDICATOR_HALF_PERIOD 5
