#ifndef SEVENSEMISHT4X_H
#define SEVENSEMISHT4X_H

#include "SevenSemiI2CDriver.h"
#include <Wire.h>

#define SHT40_I2C_ADDR_44 0x44
#define SHT40_I2C_ADDR_45 0x45
#define SHT41_I2C_ADDR_44 0x44
#define SHT41_I2C_ADDR_45 0x45
#define SHT45_I2C_ADDR_44 0x44
#define SHT45_I2C_ADDR_45 0x45

typedef enum {
    SHT4X_MEASURE_HIGH_PRECISION_TICKS_CMD_ID = 0xfd,
    SHT4X_MEASURE_MEDIUM_PRECISION_TICKS_CMD_ID = 0xf6,
    SHT4X_MEASURE_LOWEST_PRECISION_TICKS_CMD_ID = 0xe0,
    SHT4X_ACTIVATE_HIGHEST_HEATER_POWER_LONG_TICKS_CMD_ID = 0x39,
    SHT4X_ACTIVATE_HIGHEST_HEATER_POWER_SHORT_TICKS_CMD_ID = 0x32,
    SHT4X_ACTIVATE_MEDIUM_HEATER_POWER_LONG_TICKS_CMD_ID = 0x2f,
    SHT4X_ACTIVATE_MEDIUM_HEATER_POWER_SHORT_TICKS_CMD_ID = 0x24,
    SHT4X_ACTIVATE_LOWEST_HEATER_POWER_LONG_TICKS_CMD_ID = 0x1e,
    SHT4X_ACTIVATE_LOWEST_HEATER_POWER_SHORT_TICKS_CMD_ID = 0x15,
    SHT4X_SERIAL_NUMBER_CMD_ID = 0x89,
    SHT4X_SOFT_RESET_CMD_ID = 0x94,
} SHT4xCmdId;

class Sht4x_Sensor {
  public:
    Sht4x_Sensor();
    void begin(TwoWire& i2cBus, uint8_t i2cAddress);
    int16_t measureHighPrecision(float& aTemperature, float& aHumidity);
    int16_t measureMediumPrecision(float& aTemperature, float& aHumidity);
    int16_t measureLowestPrecision(float& aTemperature, float& aHumidity);
    int16_t activateHighestHeaterPowerLong(float& aTemperature,
                                           float& aHumidity);
    int16_t activateHighestHeaterPowerShort(float& aTemperature,
                                            float& aHumidity);
    int16_t activateMediumHeaterPowerLong(float& aTemperature,
                                          float& aHumidity);
    int16_t activateMediumHeaterPowerShort(float& aTemperature,
                                           float& aHumidity);
    int16_t activateLowestHeaterPowerLong(float& aTemperature,
                                          float& aHumidity);
    int16_t activateLowestHeaterPowerShort(float& aTemperature,
                                           float& aHumidity);
    int16_t measureHighPrecisionTicks(uint16_t& temperatureTicks,
                                      uint16_t& humidityTicks);
    int16_t measureMediumPrecisionTicks(uint16_t& temperatureTicks,
                                        uint16_t& humidityTicks);
    int16_t measureLowestPrecisionTicks(uint16_t& temperatureTicks,
                                        uint16_t& humidityTicks);
    int16_t activateHighestHeaterPowerLongTicks(uint16_t& temperatureTicks,
                                                uint16_t& humidityTicks);
    int16_t activateHighestHeaterPowerShortTicks(uint16_t& temperatureTicks,
                                                 uint16_t& humidityTicks);
    int16_t activateMediumHeaterPowerLongTicks(uint16_t& temperatureTicks,
                                               uint16_t& humidityTicks);
    int16_t activateMediumHeaterPowerShortTicks(uint16_t& temperatureTicks,
                                                uint16_t& humidityTicks);
    int16_t activateLowestHeaterPowerLongTicks(uint16_t& temperatureTicks,
                                               uint16_t& humidityTicks);
    int16_t activateLowestHeaterPowerShortTicks(uint16_t& temperatureTicks,
                                                uint16_t& humidityTicks);
    int16_t serialNumber(uint32_t& serialNumber);
    int16_t softReset();
    static float signalTemperature(uint16_t temperatureTicks);
    static float signalHumidity(uint16_t humidityTicks);

  private:
    TwoWire* _i2cBus = nullptr;
    uint8_t _i2cAddress = 0;
};

#endif  // SEVENSEMISHT4X_H
