#include "application.h"
#include "SpectrumEqualizer.h"

SpectrumEqualizer *spectrum;

UDP udpMulticast;
const size_t bufferSize = 16;
IPAddress remoteIP(239,1,1,234);
unsigned char buffer[bufferSize];
int port = 32555;
int hueValue = 100;

void setup() {
    Serial.begin(9600);

    udpMulticast.begin(0);

    spectrum = new SpectrumEqualizer();
}

void loop() {
   spectrum->readAudioFrequencies();
   char bufferJunk[] = {1, 23, 345, 4095};
   if(udpMulticast.sendPacket(bufferJunk, bufferSize, remoteIP, port) > 0) {
       Serial.printlnf("%d", value);
   } else {
       Serial.printlnf("send failed");
       delay(1000);
       udpMulticast.begin(0);
   }
}

void setupModeFunctions() {
  /*Particle.function("nextMode", nextMode);
  Particle.function("previousMode", previousMode);

  Particle.subscribe("NEXT_MODE", handleNextMode);
  Particle.subscribe("PREVIOUS_MODE", handlePreviousMode);*/
}

int nextMode(String mode) {
    /*int currentPattern = animations->nextPattern();
    char currentPatternString[5];
    sprintf(currentPatternString, "%i", currentPattern);
    Particle.publish("Current Pattern", currentPatternString);*/
    return 1;
}

void handleNextMode(const char *eventName, const char *data) {
    nextMode("notSureWhyIHaveToDoItLikeThis");
}

int previousMode(String mode) {
    /*int currentPattern = animations->previousPattern();
    char currentPatternString[5];
    sprintf(currentPatternString, "%i", currentPattern);
    Particle.publish("Current Pattern", currentPatternString);*/
    return 1;
}

void handlePreviousMode(const char *eventName, const char *data) {
    previousMode("seriouslyWhy?");
}
