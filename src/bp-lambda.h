// Definitions and tools for generating notes of Bohlen-Pierce scale lambda
// mode notes.
//
//
// To use this library, the following macro definitions are needed:
//
// // Frequency of base tone of Bohlen-Pierce scale, α3 (39)
// #define BP_TONE_BASE_FREQUENCY 440
//
// // Lowest possible tone, as lambda mode steps under the base tone
// #define BP_TONE_MIN 26
//
// // Highest possible tone, as lambda mode steps above the base tone
// #define BP_TONE_MAX 26
//
// // Largest possible jump between two consecutive tones
// #define BP_TONE_JUMP_MAX 7

#include "stdint.h"

// Step number of the base tone, α3
#define BP_TONE_BASE_STEP 39

namespace Bp {
    /// \brief
    ///    Returns the step number of the next note in sequence.
    ///
    /// \param currentNote
    ///    Current note step number
    ///
    /// \return
    ///    Next note step number
    uint8_t nextNote(uint8_t currentNote);

    /// \brief
    ///    Returns the frequency of given note.
    ///
    /// \param note
    ///    Note step number
    ///
    /// \return
    ///    Frequency
    uint16_t frequency(uint8_t note);
}