#include <Arduino.h>
#include "SevenSemiSht4x.h"
#include <Wire.h>


Sht4x_Sensor Sht4x;

static char Err_MSG[64];
static int16_t Err;

void setup() {

    Serial.begin(115200);
    delay(500);
    Wire.begin();
    Sht4x.begin(Wire, SHT40_I2C_ADDR_44);

    Sht4x.softReset();
    delay(10);
    uint32_t serialNumber = 0;
    Err = Sht4x.serialNumber(serialNumber);
    if (Err != 0) 
    {
        Serial.print("Error : ");
        err_discription(Err, Err_MSG, sizeof Err_MSG);
        Serial.println(Err_MSG);
        return;
    }
    Serial.print("serial Number: ");
    Serial.print(serialNumber);
    Serial.println();
}

void loop() {

    float Temp = 0.0;
    float Hum = 0.0;
    delay(100);
    Err = Sht4x.measureLowestPrecision(Temp, Hum);
    if (Err != 0) 
    {
        Serial.print("Error : ");
        err_discription(Err, Err_MSG, sizeof Err_MSG);
        Serial.println(Err_MSG);
        return;
    }
    Serial.print("Temperature: ");
    Serial.print(Temp);
    Serial.print("\t");
    Serial.print("Humidity: ");
    Serial.print(Hum);
    Serial.println();
}
