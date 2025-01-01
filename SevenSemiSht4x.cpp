/******************************************************************************
 * File:        SevenSemiSht4x.cpp
 * Author:      7Semi
 * Version:     1.0.1
 * Date:        28/12/2024
 ******************************************************************************/
 
#include "SevenSemiSht4x.h"
#include <Arduino.h>


static uint8_t communication_buffer[6] = {0};

Sht4x_Sensor::Sht4x_Sensor() {
}

float Sht4x_Sensor::signalTemperature(uint16_t temperatureTicks) {
    float temperature = 0.0;
    temperature = (float)(temperatureTicks);
    temperature = ((temperature * 175.0) / 65535.0) - 45.0;
    return temperature;
}

float Sht4x_Sensor::signalHumidity(uint16_t humidityTicks) {
    float humidity = 0.0;
    humidity = (float)(humidityTicks);
    humidity = ((humidity * 125.0) / 65535.0) - 6.0;
    return humidity;
}

int16_t Sht4x_Sensor::measureHighPrecision(float& aTemperature,
                                                float& aHumidity) {
    uint16_t tempTicks = 0;
    uint16_t humiTicks = 0;
    int16_t localError = 0;
    localError = measureHighPrecisionTicks(tempTicks, humiTicks);
    if (localError != 0) {
        return localError;
    }
    aTemperature = Sht4x_Sensor::signalTemperature(tempTicks);
    aHumidity = Sht4x_Sensor::signalHumidity(humiTicks);
    return localError;
}

int16_t Sht4x_Sensor::measureMediumPrecision(float& aTemperature,
                                                  float& aHumidity) {
    uint16_t tempTicks = 0;
    uint16_t humiTicks = 0;
    int16_t localError = 0;
    localError = measureMediumPrecisionTicks(tempTicks, humiTicks);
    if (localError != 0) {
        return localError;
    }
    aTemperature = Sht4x_Sensor::signalTemperature(tempTicks);
    aHumidity = Sht4x_Sensor::signalHumidity(humiTicks);
    return localError;
}

int16_t Sht4x_Sensor::measureLowestPrecision(float& aTemperature,
                                                  float& aHumidity) {
    uint16_t tempTicks = 0;
    uint16_t humiTicks = 0;
    int16_t localError = 0;
    localError = measureLowestPrecisionTicks(tempTicks, humiTicks);
    if (localError != 0) {
        return localError;
    }
    aTemperature = Sht4x_Sensor::signalTemperature(tempTicks);
    aHumidity = Sht4x_Sensor::signalHumidity(humiTicks);
    return localError;
}

int16_t Sht4x_Sensor::activateHighestHeaterPowerLong(float& aTemperature,
                                                          float& aHumidity) {
    uint16_t tempTicks = 0;
    uint16_t humiTicks = 0;
    int16_t localError = 0;
    localError = activateHighestHeaterPowerLongTicks(tempTicks, humiTicks);
    if (localError != 0) {
        return localError;
    }
    aTemperature = Sht4x_Sensor::signalTemperature(tempTicks);
    aHumidity = Sht4x_Sensor::signalHumidity(humiTicks);
    return localError;
}

int16_t Sht4x_Sensor::activateHighestHeaterPowerShort(float& aTemperature,
                                                           float& aHumidity) {
    uint16_t tempTicks = 0;
    uint16_t humiTicks = 0;
    int16_t localError = 0;
    localError = activateHighestHeaterPowerShortTicks(tempTicks, humiTicks);
    if (localError != 0) {
        return localError;
    }
    aTemperature = Sht4x_Sensor::signalTemperature(tempTicks);
    aHumidity = Sht4x_Sensor::signalHumidity(humiTicks);
    return localError;
}

int16_t Sht4x_Sensor::activateMediumHeaterPowerLong(float& aTemperature,
                                                         float& aHumidity) {
    uint16_t tempTicks = 0;
    uint16_t humiTicks = 0;
    int16_t localError = 0;
    localError = activateMediumHeaterPowerLongTicks(tempTicks, humiTicks);
    if (localError != 0) {
        return localError;
    }
    aTemperature = Sht4x_Sensor::signalTemperature(tempTicks);
    aHumidity = Sht4x_Sensor::signalHumidity(humiTicks);
    return localError;
}

int16_t Sht4x_Sensor::activateMediumHeaterPowerShort(float& aTemperature,
                                                          float& aHumidity) {
    uint16_t tempTicks = 0;
    uint16_t humiTicks = 0;
    int16_t localError = 0;
    localError = activateMediumHeaterPowerShortTicks(tempTicks, humiTicks);
    if (localError != 0) {
        return localError;
    }
    aTemperature = Sht4x_Sensor::signalTemperature(tempTicks);
    aHumidity = Sht4x_Sensor::signalHumidity(humiTicks);
    return localError;
}

int16_t Sht4x_Sensor::activateLowestHeaterPowerLong(float& aTemperature,
                                                         float& aHumidity) {
    uint16_t tempTicks = 0;
    uint16_t humiTicks = 0;
    int16_t localError = 0;
    localError = activateLowestHeaterPowerLongTicks(tempTicks, humiTicks);
    if (localError != 0) {
        return localError;
    }
    aTemperature = Sht4x_Sensor::signalTemperature(tempTicks);
    aHumidity = Sht4x_Sensor::signalHumidity(humiTicks);
    return localError;
}

int16_t Sht4x_Sensor::activateLowestHeaterPowerShort(float& aTemperature,
                                                          float& aHumidity) {
    uint16_t tempTicks = 0;
    uint16_t humiTicks = 0;
    int16_t localError = 0;
    localError = activateLowestHeaterPowerShortTicks(tempTicks, humiTicks);
    if (localError != 0) {
        return localError;
    }
    aTemperature = Sht4x_Sensor::signalTemperature(tempTicks);
    aHumidity = Sht4x_Sensor::signalHumidity(humiTicks);
    return localError;
}

int16_t Sht4x_Sensor::measureHighPrecisionTicks(uint16_t& temperatureTicks,
                                                     uint16_t& humidityTicks) {
    int16_t localError = 0;
    uint8_t* buffer_ptr = communication_buffer;
    DeviceLibraryI2CTxFrame txFrame =
        DeviceLibraryI2CTxFrame::createWithUInt8Command(0xfd, buffer_ptr, 6);
    localError =
        DeviceLibraryI2CCommunication::sendFrame(_i2cAddress, txFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    delay(10);
    DeviceLibraryI2CRxFrame rxFrame(buffer_ptr, 6);
    localError = DeviceLibraryI2CCommunication::receiveFrame(_i2cAddress, 6,
                                                         rxFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    localError |= rxFrame.getUInt16(temperatureTicks);
    localError |= rxFrame.getUInt16(humidityTicks);
    return localError;
}

int16_t
Sht4x_Sensor::measureMediumPrecisionTicks(uint16_t& temperatureTicks,
                                               uint16_t& humidityTicks) {
    int16_t localError = 0;
    uint8_t* buffer_ptr = communication_buffer;
    DeviceLibraryI2CTxFrame txFrame =
        DeviceLibraryI2CTxFrame::createWithUInt8Command(0xf6, buffer_ptr, 6);
    localError =
        DeviceLibraryI2CCommunication::sendFrame(_i2cAddress, txFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    delay(5);
    DeviceLibraryI2CRxFrame rxFrame(buffer_ptr, 6);
    localError = DeviceLibraryI2CCommunication::receiveFrame(_i2cAddress, 6,
                                                         rxFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    localError |= rxFrame.getUInt16(temperatureTicks);
    localError |= rxFrame.getUInt16(humidityTicks);
    return localError;
}

int16_t
Sht4x_Sensor::measureLowestPrecisionTicks(uint16_t& temperatureTicks,
                                               uint16_t& humidityTicks) {
    int16_t localError = 0;
    uint8_t* buffer_ptr = communication_buffer;
    DeviceLibraryI2CTxFrame txFrame =
        DeviceLibraryI2CTxFrame::createWithUInt8Command(0xe0, buffer_ptr, 6);
    localError =
        DeviceLibraryI2CCommunication::sendFrame(_i2cAddress, txFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    delay(2);
    DeviceLibraryI2CRxFrame rxFrame(buffer_ptr, 6);
    localError = DeviceLibraryI2CCommunication::receiveFrame(_i2cAddress, 6,
                                                         rxFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    localError |= rxFrame.getUInt16(temperatureTicks);
    localError |= rxFrame.getUInt16(humidityTicks);
    return localError;
}

int16_t Sht4x_Sensor::activateHighestHeaterPowerLongTicks(
    uint16_t& temperatureTicks, uint16_t& humidityTicks) {
    int16_t localError = 0;
    uint8_t* buffer_ptr = communication_buffer;
    DeviceLibraryI2CTxFrame txFrame =
        DeviceLibraryI2CTxFrame::createWithUInt8Command(0x39, buffer_ptr, 6);
    localError =
        DeviceLibraryI2CCommunication::sendFrame(_i2cAddress, txFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    delay(1100);
    DeviceLibraryI2CRxFrame rxFrame(buffer_ptr, 6);
    localError = DeviceLibraryI2CCommunication::receiveFrame(_i2cAddress, 6,
                                                         rxFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    localError |= rxFrame.getUInt16(temperatureTicks);
    localError |= rxFrame.getUInt16(humidityTicks);
    return localError;
}

int16_t Sht4x_Sensor::activateHighestHeaterPowerShortTicks(
    uint16_t& temperatureTicks, uint16_t& humidityTicks) {
    int16_t localError = 0;
    uint8_t* buffer_ptr = communication_buffer;
    DeviceLibraryI2CTxFrame txFrame =
        DeviceLibraryI2CTxFrame::createWithUInt8Command(0x32, buffer_ptr, 6);
    localError =
        DeviceLibraryI2CCommunication::sendFrame(_i2cAddress, txFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    delay(110);
    DeviceLibraryI2CRxFrame rxFrame(buffer_ptr, 6);
    localError = DeviceLibraryI2CCommunication::receiveFrame(_i2cAddress, 6,
                                                         rxFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    localError |= rxFrame.getUInt16(temperatureTicks);
    localError |= rxFrame.getUInt16(humidityTicks);
    return localError;
}

int16_t Sht4x_Sensor::activateMediumHeaterPowerLongTicks(
    uint16_t& temperatureTicks, uint16_t& humidityTicks) {
    int16_t localError = 0;
    uint8_t* buffer_ptr = communication_buffer;
    DeviceLibraryI2CTxFrame txFrame =
        DeviceLibraryI2CTxFrame::createWithUInt8Command(0x2f, buffer_ptr, 6);
    localError =
        DeviceLibraryI2CCommunication::sendFrame(_i2cAddress, txFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    delay(1100);
    DeviceLibraryI2CRxFrame rxFrame(buffer_ptr, 6);
    localError = DeviceLibraryI2CCommunication::receiveFrame(_i2cAddress, 6,
                                                         rxFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    localError |= rxFrame.getUInt16(temperatureTicks);
    localError |= rxFrame.getUInt16(humidityTicks);
    return localError;
}

int16_t Sht4x_Sensor::activateMediumHeaterPowerShortTicks(
    uint16_t& temperatureTicks, uint16_t& humidityTicks) {
    int16_t localError = 0;
    uint8_t* buffer_ptr = communication_buffer;
    DeviceLibraryI2CTxFrame txFrame =
        DeviceLibraryI2CTxFrame::createWithUInt8Command(0x24, buffer_ptr, 6);
    localError =
        DeviceLibraryI2CCommunication::sendFrame(_i2cAddress, txFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    delay(110);
    DeviceLibraryI2CRxFrame rxFrame(buffer_ptr, 6);
    localError = DeviceLibraryI2CCommunication::receiveFrame(_i2cAddress, 6,
                                                         rxFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    localError |= rxFrame.getUInt16(temperatureTicks);
    localError |= rxFrame.getUInt16(humidityTicks);
    return localError;
}

int16_t Sht4x_Sensor::activateLowestHeaterPowerLongTicks(
    uint16_t& temperatureTicks, uint16_t& humidityTicks) {
    int16_t localError = 0;
    uint8_t* buffer_ptr = communication_buffer;
    DeviceLibraryI2CTxFrame txFrame =
        DeviceLibraryI2CTxFrame::createWithUInt8Command(0x1e, buffer_ptr, 6);
    localError =
        DeviceLibraryI2CCommunication::sendFrame(_i2cAddress, txFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    delay(1100);
    DeviceLibraryI2CRxFrame rxFrame(buffer_ptr, 6);
    localError = DeviceLibraryI2CCommunication::receiveFrame(_i2cAddress, 6,
                                                         rxFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    localError |= rxFrame.getUInt16(temperatureTicks);
    localError |= rxFrame.getUInt16(humidityTicks);
    return localError;
}

int16_t Sht4x_Sensor::activateLowestHeaterPowerShortTicks(
    uint16_t& temperatureTicks, uint16_t& humidityTicks) {
    int16_t localError = 0;
    uint8_t* buffer_ptr = communication_buffer;
    DeviceLibraryI2CTxFrame txFrame =
        DeviceLibraryI2CTxFrame::createWithUInt8Command(0x15, buffer_ptr, 6);
    localError =
        DeviceLibraryI2CCommunication::sendFrame(_i2cAddress, txFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    delay(110);
    DeviceLibraryI2CRxFrame rxFrame(buffer_ptr, 6);
    localError = DeviceLibraryI2CCommunication::receiveFrame(_i2cAddress, 6,
                                                         rxFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    localError |= rxFrame.getUInt16(temperatureTicks);
    localError |= rxFrame.getUInt16(humidityTicks);
    return localError;
}

int16_t Sht4x_Sensor::serialNumber(uint32_t& serialNumber) {
    int16_t localError = 0;
    uint8_t* buffer_ptr = communication_buffer;
    DeviceLibraryI2CTxFrame txFrame =
        DeviceLibraryI2CTxFrame::createWithUInt8Command(0x89, buffer_ptr, 6);
    localError =
        DeviceLibraryI2CCommunication::sendFrame(_i2cAddress, txFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    delay(10);
    DeviceLibraryI2CRxFrame rxFrame(buffer_ptr, 6);
    localError = DeviceLibraryI2CCommunication::receiveFrame(_i2cAddress, 6,
                                                         rxFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    localError |= rxFrame.getUInt32(serialNumber);
    return localError;
}

int16_t Sht4x_Sensor::softReset() {
    int16_t localError = 0;
    uint8_t* buffer_ptr = communication_buffer;
    DeviceLibraryI2CTxFrame txFrame =
        DeviceLibraryI2CTxFrame::createWithUInt8Command(0x94, buffer_ptr, 2);
    localError =
        DeviceLibraryI2CCommunication::sendFrame(_i2cAddress, txFrame, *_i2cBus);
    if (localError != 0) {
        return localError;
    }
    delay(10);
    return localError;
}

void Sht4x_Sensor::begin(TwoWire& i2cBus, uint8_t i2cAddress) {
    _i2cBus = &i2cBus;
    _i2cAddress = i2cAddress;
}
