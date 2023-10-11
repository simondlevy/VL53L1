#include <Arduino.h>
#include <Wire.h>

#include "vl53l1x.hpp"

static VL53L1X sensor;

void setup(void)
{
    Wire.begin();

    Serial.begin(115200);

    sensor.begin();
}

void loop(void)
{
    Serial.print(sensor.readDistance());
    Serial.println(" mm");
}
