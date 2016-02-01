A multi-sensor thermometer with display (in degrees F) running on the Particle Photon.

Sensors are display are on the I2C bus.

* Microcontroller: Particle Photon
* Temp sensor: MCP9808 (Adafruit kit)
* Display: 4 character alphanumeric (15-segment) display w/ I2C interface (Adafruit kit)

Uses the following libraries:
* Adafruit LED Backpack library, with Spark (Particle) support by creationix: https://github.com/creationix/spark-adafruit-led-backpack
* MCP9808 library by romainmp: https://github.com/romainmp/MCP9808