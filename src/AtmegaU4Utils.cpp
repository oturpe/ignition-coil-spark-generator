#include <stdint.h>
#include <avr/io.h>

#include "AtmegaU4Utils.h"

namespace AtmegaU4 {
// TODO: Check that these are correct. They were copied from Atmega328p code

uint16_t timerPrescalers[4] = { 1, 1, 1, 1};

void setTimer0Prescaler(TimerPrescalerValue value) {
  switch (value) {
  case PSV_1:
    TCCR0B |= BV(CS00);
    timerPrescalers[0] = 1;
    break;
  case PSV_8:
    TCCR0B |= BV(CS01);
    timerPrescalers[0] = 8;
    break;
  case PSV_64:
    TCCR0B |= BV(CS01) | BV(CS00);
    timerPrescalers[0] = 64;
    break;
  case PSV_256:
    TCCR0B |= BV(CS02);
    timerPrescalers[0] = 256;
    break;
  case PSV_1024:
    TCCR0B |= BV(CS02) | BV(CS00);
    timerPrescalers[0] = 1024;
    break;
  }
}

uint16_t timer0Prescaler() {
  return timerPrescalers[0];
}

void setTimer1Prescaler(TimerPrescalerValue value) {
  switch (value) {
  case PSV_1:
    TCCR1B |= BV(CS10);
    timerPrescalers[1] = 1;
    break;
  case PSV_8:
    TCCR1B |= BV(CS11);
    timerPrescalers[1] = 8;
    break;
  case PSV_64:
    TCCR1B |= BV(CS11) | BV(CS10);
    timerPrescalers[1] = 64;
    break;
  case PSV_256:
    TCCR1B |= BV(CS12);
    timerPrescalers[1] = 256;
    break;
  case PSV_1024:
    TCCR1B |= BV(CS12) | BV(CS10);
    timerPrescalers[1] = 1024;
    break;
  }
}

uint16_t timer1Prescaler() {
  return timerPrescalers[1];
}

void setTimer3Prescaler(TimerPrescalerValue value) {
  switch (value) {
  case PSV_1:
    TCCR3B |= BV(CS30);
    timerPrescalers[3] = 1;
    break;
  case PSV_8:
    TCCR3B |= BV(CS31);
    timerPrescalers[3] = 8;
    break;
  case PSV_64:
    TCCR3B |= BV(CS31) | BV(CS30);
    timerPrescalers[3] = 64;
    break;
  case PSV_256:
    TCCR3B |= BV(CS32);
    timerPrescalers[3] = 256;
    break;
  case PSV_1024:
    TCCR3B |= BV(CS32) | BV(CS30);
    timerPrescalers[3] = 1024;
    break;
  }
}

uint16_t timer3Prescaler() {
  return timerPrescalers[3];
}

} // namespace
