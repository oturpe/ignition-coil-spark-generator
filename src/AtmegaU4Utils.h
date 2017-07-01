// Helpers for working with AtmegaU4 series.
//
// Works with the following models:
//    Atmega16U4
//    Atmega32U4

// Cleaner setting of bits
#define BV(x) (1<<x)

namespace AtmegaU4 {

// TODO: Check that these are correct. They were copied from Atmega328p code

/// Possible prescaler values for timer 0.
enum TimerPrescalerValue {
  PSV_1,
  PSV_8,
  PSV_64,
  PSV_256,
  PSV_1024,
};

/// Sets timer 0 prescaler to requested value.
///
/// This function assumes that Clock Select bits have not been touched yet. Note
/// that timer 0 does not support all Timer0PrescalerValue values. If illegal
/// value is entered, prescaler is not set to any value.
///
/// \param value
///   Requested prescaler value
void setTimer0Prescaler(TimerPrescalerValue value);

/// \brief 
///    Returns the current value of timer 0 prescaler.
///
/// \return
///    Timer 0 prescaler value
uint16_t timer0Prescaler();

/// Sets timer 1 prescaler to requested value.
///
/// This function assumes that Clock Select bits have not been touched yet. Note
/// that timer 1 does not support all Timer0PrescalerValue values. If illegal
/// value is entered, prescaler is not set to any value.
///
/// \param value
///   Requested prescaler value
void setTimer1Prescaler(TimerPrescalerValue value);

/// \brief 
///    Returns the current value of timer 1 prescaler.
///
/// \return
///    Timer 1 prescaler value
uint16_t timer1Prescaler();

/// Sets timer 3 prescaler to requested value.
///
/// This function assumes that Clock Select bits have not been touched yet.
///
/// \param value
///   Requested prescaler value
void setTimer3Prescaler(TimerPrescalerValue value);

/// \brief 
///    Returns the current value of timer 3 prescaler.
///
/// \return
///    Timer 3 prescaler value
uint16_t timer3Prescaler();

} // namespace
