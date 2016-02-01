#include "MCP9808/MCP9808.h"
#include "adafruit-led-backpack/adafruit-led-backpack.h"

// This is the Photon convention for I2C
int DATA_PIN = D0;
int CLOCK_PIN = D1;

byte ADDRESS_DISPLAY = 0x70; // default (no pins on)
byte ADDRESS_TEMP1 = 0x19; // A0 pin on (base = 0x18)
byte ADDRESS_TEMP2 = 0x1A; // A1 pin on

// The index at which the digits start
int ASCII_OFFSET = 48;

// The I2C devices - classes are imported from Adafruit's published libraries
Adafruit_AlphaNum4 display = Adafruit_AlphaNum4();
MCP9808 tempSensor1 = MCP9808(ADDRESS_TEMP1);
MCP9808 tempSensor2 = MCP9808(ADDRESS_TEMP2);

void setup() {
    // This also calls Wire.begin(), which tells the controller to join the I2C bus as a master
    display.begin(ADDRESS_DISPLAY);
    
    // Set the read mode on the sensors to the slowest/most accurate)
    // This mode is documented to take around 250ms per read
    tempSensor1.setResolution(MCP9808_SLOWEST);
    tempSensor2.setResolution(MCP9808_SLOWEST);
}

void loop() {
    // Using multiple sensors as an exercise - will be using a few for an upcoming project
    readAndDisplayTemp(tempSensor1);//, alpha4);
    delay(2000);
    // TODO: visual indicator would be nice
    readAndDisplayTemp(tempSensor2);//, alpha4);
    delay(2000);
}

void readAndDisplayTemp(MCP9808 sensor) {//, Adafruit_AlphaNum4 display) {
    // Clear the display
    display.clear();
    display.writeDisplay();
    
    // Read the temperature and break it into characters
    // We are displaying in tenths
    float tempC = sensor.getTemperature();
    float tempF = tempC * 1.8 + 32;
    int tempFTenths = int(tempF * 10);
    int characters[4] = {
        tempFTenths / 1000,
        tempFTenths % 1000 / 100,
        tempFTenths % 1000 % 100 / 10,
        tempFTenths % 1000 % 100 % 10
    };
    
    // Set the individual characters
    for (int i = 0; i < 4; i++) {
        // Write a leading negative sign if the temp is... well, negative.
        if (i == 0 && tempF < 0) {
            display.writeDigitAscii(i, '-');
            continue;
        }
        // Decimal is always written on the third character (it's just another segment, not a character on its own)
        boolean writeDecimal = i == 2;
        display.writeDigitAscii(i, byte(characters[i] + ASCII_OFFSET), writeDecimal);
    }
    
    // Done setting characters. Refresh the display.
    display.writeDisplay();
}