#ifndef SPECTRUMEQUALIZER_H
#define SPECTRUMEQUALIZER_H

#include "application.h"

#define STROBE_PIN D6
#define RESET_PIN D0
#define LEFT_EQ_PIN A0
#define RIGHT_EQ_PIN A1

class SpectrumEqualizer {
    public:
        int frequenciesLeft[7];
        int frequenciesRight[7];

        SpectrumEqualizer();
        void init();
        void readAudioFrequencies();
};

#endif
