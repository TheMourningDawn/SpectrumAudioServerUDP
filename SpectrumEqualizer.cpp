#ifndef SPECTRUMEQUALIZER_CPP
#define SPECTRUMEQUALIZER_CPP

#include "SpectrumEqualizer.h"
#include "application.h"

SpectrumEqualizer::SpectrumEqualizer() {

}

void SpectrumEqualizer::init() {
    pinMode(RESET_PIN, OUTPUT);
    pinMode(STROBE_PIN, OUTPUT);
    digitalWrite(RESET_PIN, LOW);
    digitalWrite(STROBE_PIN, HIGH);
}

void SpectrumEqualizer::readAudioFrequencies() {
    digitalWrite(RESET_PIN, HIGH);
    digitalWrite(RESET_PIN, LOW);

    for (int band = 0; band < 7; band++) {
        digitalWrite(STROBE_PIN, LOW); // go to the next band
        delayMicroseconds(50); // gather some data
        frequenciesLeft[band] = analogRead(LEFT_EQ_PIN);
        digitalWrite(STROBE_PIN, HIGH); // reset the strobe pin
    }
    // Serial.printlnf("Just read: [%d, %d, %d, %d]", frequenciesLeft[0],frequenciesLeft[2],frequenciesLeft[4],frequenciesLeft[6]);
}

#endif
