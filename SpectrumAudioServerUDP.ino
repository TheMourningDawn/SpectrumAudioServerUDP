#include "application.h"
#include "SpectrumEqualizer.h"

#define NUM_FREQUENCIES 7
#define BUFFER_SIZE NUM_FREQUENCIES*2

SpectrumEqualizer *spectrum;
char spectrumAsBytes[BUFFER_SIZE];

UDP udpMulticast;
int port = 32555;
IPAddress remoteIP(239, 1, 1, 234);

SYSTEM_THREAD(ENABLED);

bool poweredOn = true;

void setup() {
    Particle.function("reset-device", resetDevice);
    Particle.function("enter-safe-mode", enterSafeMode);
    Particle.function("power", power);

    Particle.variable("powered-on", poweredOn);

    udpMulticast.begin(0);

    spectrum = new SpectrumEqualizer();
    spectrum->init();
}

void loop() {
    delay(20);
    spectrum->readAudioFrequencies();
    for (int i = 0; i < BUFFER_SIZE; i += 2) {
        spectrumAsBytes[i] = spectrum->frequenciesLeft[i / 2] >> 8;
        spectrumAsBytes[i + 1] = spectrum->frequenciesLeft[i / 2] & 0xFF;
    }
    if (udpMulticast.sendPacket(spectrumAsBytes, BUFFER_SIZE, remoteIP, port) < 0) {
        Particle.publish("Resetting UDP connection.");
        udpMulticast.begin(0);
    }
    /*Serial.printlnf("Sent: [%d, %d, %d, %d]", spectrum->frequenciesLeft[0],spectrum->frequenciesLeft[2],spectrum->frequenciesLeft[4],spectrum->frequenciesLeft[6]);*/
}

int resetDevice(String arg) {
    System.reset();

    return 1;
}

int enterSafeMode(String arg) {
    System.enterSafeMode();

    return 1;
}

int power(String arg) {
    if (arg == "ON") {
        poweredOn = true;
    } else if (arg == "OFF") {
        poweredOn = false;
    } else {
        return -1;
    }

    return 1;
}
