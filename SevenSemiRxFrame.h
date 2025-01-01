#ifndef SEVENSEMI_RX_FRAME_H_
#define SEVENSEMI_RX_FRAME_H_

#include <stdint.h>
#include <stdlib.h>


typedef enum : uint16_t {
    Byte = 1,
    Short = 2,
    Integer = 4,
    LongInteger = 8
} IntegerType;


class DeviceLibraryRxFrame {

    friend class DeviceLibraryI2CCommunication;
    friend class DeviceLibraryShdlcCommunication;

  public:

    DeviceLibraryRxFrame(uint8_t buffer[], size_t bufferSize);


    uint16_t getInteger(uint8_t* destination, IntegerType type,
                        uint8_t nrOfBytes);


    uint16_t getUInt32(uint32_t& data);


    uint16_t getInt32(int32_t& data);


    uint16_t getUInt16(uint16_t& data);


    uint16_t getInt16(int16_t& data);


    uint16_t getUInt8(uint8_t& data);


    uint16_t getInt8(int8_t& data);


    uint16_t getBool(bool& data);


    uint16_t getFloat(float& data);

    uint16_t getBytes(uint8_t data[], size_t maxBytes);

  private:
    uint8_t* _buffer = 0;
    size_t _bufferSize = 0;
    size_t _index = 0;
    size_t _numBytes = 0;
};

#endif /* SEVENSEMI_RX_FRAME_H_ */
