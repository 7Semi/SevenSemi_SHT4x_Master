#include "SevenSemiI2CCom.h"

#include <stdint.h>
#include <stdlib.h>

#include "Arduino.h"
#include "SevenSemiCrc.h"
#include "SevenSemiErrors.h"
#include "SevenSemiI2CRxFrame.h"
#include "SevenSemiI2CTxFrame.h"

static void clearRxBuffer(TwoWire& i2cBus) {
    while (i2cBus.available()) {
        (void)i2cBus.read();
    }
}

uint16_t DeviceLibraryI2CCommunication::sendFrame(uint8_t address,
                                              DeviceLibraryI2CTxFrame& frame,
                                              TwoWire& i2cBus) {
    i2cBus.beginTransmission(address);
    size_t writtenBytes = i2cBus.write(frame._buffer, frame._index);
    uint8_t i2c_error = i2cBus.endTransmission();
    if (writtenBytes != frame._index) {
        return WriteError | I2cOtherError;
    }

    switch (i2c_error) {
        case 0:
            return NoError;
        case 1:
            return WriteError | InternalBufferSizeError;
        case 2:
            return WriteError | I2cAddressNack;
        case 3:
            return WriteError | I2cDataNack;
        default:
            return WriteError | I2cOtherError;
    }
}

uint16_t DeviceLibraryI2CCommunication::receiveFrame(uint8_t address,
                                                 size_t numBytes,
                                                 DeviceLibraryI2CRxFrame& frame,
                                                 TwoWire& i2cBus,
                                                 CrcPolynomial poly) {

#ifdef I2C_BUFFER_LENGTH
    const uint8_t sizeBuffer =
        (static_cast<uint8_t>(I2C_BUFFER_LENGTH) / static_cast<uint8_t>(3)) * 3;
#elif defined(BUFFER_LENGTH)
    const uint8_t sizeBuffer =
        (static_cast<uint8_t>(BUFFER_LENGTH) / static_cast<uint8_t>(3)) * 3;
#else
    const uint8_t sizeBuffer = 30;
#endif

    if (numBytes % 3) {
        return ReadError | WrongNumberBytesError;
    }
    if ((numBytes / 3) * 2 > frame._bufferSize) {
        return ReadError | BufferSizeError;
    }
    size_t i = 0;
    int16_t remaining = numBytes;
    uint8_t bytesToRead = sizeBuffer;
    bool stop = bytesToRead >= remaining;
    do {
        if (sizeBuffer >= remaining) {
            stop = true;
            bytesToRead = remaining;
        }
        uint8_t available = i2cBus.requestFrom(address, bytesToRead,
                                               static_cast<uint8_t>(stop));
        if (bytesToRead != available) {
            return ReadError | NotEnoughDataError;
        }
        while (available > 0) {
            frame._buffer[i++] = i2cBus.read();
            frame._buffer[i++] = i2cBus.read();
            uint8_t actualCRC = i2cBus.read();
            uint8_t expectedCRC = generateCRC(&frame._buffer[i - 2], 2, poly);
            if (actualCRC != expectedCRC) {
                clearRxBuffer(i2cBus);
                return ReadError | CRCError;
            }
            available -= 3;
        }
        remaining -= bytesToRead;

    } while (remaining > 0);
    frame._numBytes = i;
    return NoError;
}
