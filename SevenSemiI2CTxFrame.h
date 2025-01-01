#ifndef SEVENSEMI_I2C_TX_FRAME_H_
#define SEVENSEMI_I2C_TX_FRAME_H_

#include <stdint.h>
#include <stdlib.h>

#include "SevenSemiCrc.h"
#include "SevenSemiI2CCom.h"


class DeviceLibraryI2CTxFrame {

    friend class DeviceLibraryI2CCommunication;

  public:

    static DeviceLibraryI2CTxFrame
    createWithUInt8Command(uint8_t command, uint8_t buffer[], size_t bufferSize,
                           CrcPolynomial poly = CRC31_ff);


    static DeviceLibraryI2CTxFrame
    createWithUInt16Command(uint16_t command, uint8_t buffer[],
                            size_t bufferSize, CrcPolynomial poly = CRC31_ff);


    DeviceLibraryI2CTxFrame(uint8_t buffer[], size_t bufferSize,
                        CrcPolynomial poly = CRC31_ff);


    uint16_t addCommand(uint16_t command);


    uint16_t addUInt32(uint32_t data);


    uint16_t addInt32(int32_t data);


    uint16_t addUInt16(uint16_t data);


    uint16_t addInt16(int16_t data);

    
    uint16_t addUInt8(uint8_t data);

  
    uint16_t addInt8(int8_t data);


    uint16_t addBool(bool data);


    uint16_t addFloat(float data);


    uint16_t addBytes(const uint8_t data[], size_t dataLength);

  private:
    DeviceLibraryI2CTxFrame(uint8_t buffer[], size_t bufferSize,
                        size_t numCommandBytes, CrcPolynomial poly = CRC31_ff);

    uint16_t _addByte(uint8_t data);

    uint8_t* _buffer;
    size_t _bufferSize;
    size_t _index;
    size_t _numCommandBytes;
    CrcPolynomial _polynomial_type;
};

#endif /* SEVENSEMI_I2C_TX_FRAME_H_ */
