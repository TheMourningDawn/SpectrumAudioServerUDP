#include "application.h"
#include "SpectrumEqualizer.h"

#define NUM_FREQUENCIES 7
#define BUFFER_SIZE NUM_FREQUENCIES*2

SpectrumEqualizer *spectrum;
char spectrumAsBytes[BUFFER_SIZE];

UDP udpMulticast;
int port = 32555;
IPAddress remoteIP(239,1,1,234);

void setup() {
    Serial.begin(9600);

    udpMulticast.begin(0);

    spectrum = new SpectrumEqualizer();
    spectrum->init();
}

void loop() {
   spectrum->readAudioFrequencies();
   for(int i=0;i<BUFFER_SIZE;i+=2) {
        spectrumAsBytes[i] = spectrum->frequenciesLeft[i/2] >> 8;
        spectrumAsBytes[i+1] = spectrum->frequenciesLeft[i/2] & 0xFF;
   }

   if(udpMulticast.sendPacket(spectrumAsBytes, BUFFER_SIZE, remoteIP, port) > 0) {
       Serial.print(".");
   } else {
       Serial.printlnf("send failed");
       delay(1000);
       udpMulticast.begin(0);
   }
}
