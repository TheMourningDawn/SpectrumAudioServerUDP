#ifndef SPECTRUMEQUALIZER_CPP
#define SPECTRUMEQUALIZER_CPP

#include "SpectrumEqualizer.h"
#include "application.h"
#include "LEDAnimations.h"

SpectrumEqualizer::SpectrumEqualizer() {

}

void SpectrumEqualizer::init() {
    pinMode(RESET_PIN, OUTPUT); // reset
    pinMode(STROBE_PIN, OUTPUT); // strobe
    digitalWrite(RESET_PIN, LOW); // reset low
    digitalWrite(STROBE_PIN, HIGH); //pin 5 is RESET on the shield
}

void SpectrumEqualizer::readAudioFrequencies() {
    // reset the data
    digitalWrite(RESET_PIN, HIGH);
    digitalWrite(RESET_PIN, LOW);

    for (int band = 0; band < 7; band++) {
        digitalWrite(STROBE_PIN, LOW); // go to the next band
        delayMicroseconds(50); // gather some data
        frequenciesLeft[band] = analogRead(LEFT_EQ_PIN); // store left band reading
        frequenciesRight[band] = analogRead(RIGHT_EQ_PIN); // store right band reading
        digitalWrite(STROBE_PIN, HIGH); // reset the strobe pin
    }
}

#endif
