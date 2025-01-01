#include "SevenSemiRxFrame.h"

#include <stdint.h>
#include <stdlib.h>

#include "SevenSemiErrors.h"

DeviceLibraryRxFrame::DeviceLibraryRxFrame(uint8_t buffer[], size_t bufferSize)
    : _buffer(buffer), _bufferSize(bufferSize), _index(0), _numBytes(0) {
}

uint16_t DeviceLibraryRxFrame::getUInt32(uint32_t& data) {
    if (_numBytes < 4) {
        return RxFrameError | NoDataError;
    }
    data = static_cast<uint32_t>(_buffer[_index++]) << 24;
    data |= static_cast<uint32_t>(_buffer[_index++]) << 16;
    data |= static_cast<uint32_t>(_buffer[_index++]) << 8;
    data |= static_cast<uint32_t>(_buffer[_index++]);
    _numBytes -= 4;
    return NoError;
}

uint16_t DeviceLibraryRxFrame::getInt32(int32_t& data) {
    uint32_t ret = 0;
    uint16_t error = getUInt32(ret);
    data = static_cast<int32_t>(ret);
    return error;
}

uint16_t DeviceLibraryRxFrame::getUInt16(uint16_t& data) {
    if (_numBytes < 2) {
        return RxFrameError | NoDataError;
    }
    data = static_cast<uint16_t>(_buffer[_index++]) << 8;
    data |= static_cast<uint16_t>(_buffer[_index++]);
    _numBytes -= 2;
    return NoError;
}

uint16_t DeviceLibraryRxFrame::getInt16(int16_t& data) {
    uint16_t ret = 0;
    uint16_t error = getUInt16(ret);
    data = static_cast<int16_t>(ret);
    return error;
}

uint16_t DeviceLibraryRxFrame::getUInt8(uint8_t& data) {
    if (_numBytes < 1) {
        return RxFrameError | NoDataError;
    }
    data = _buffer[_index++];
    _numBytes -= 1;
    return NoError;
}

uint16_t DeviceLibraryRxFrame::getInt8(int8_t& data) {
    if (_numBytes < 1) {
        return RxFrameError | NoDataError;
    }
    data = static_cast<int8_t>(_buffer[_index++]);
    _numBytes -= 1;
    return NoError;
}

uint16_t DeviceLibraryRxFrame::getBool(bool& data) {
    if (_numBytes < 1) {
        return RxFrameError | NoDataError;
    }
    data = static_cast<bool>(_buffer[_index++]);
    _numBytes -= 1;
    return NoError;
}

uint16_t DeviceLibraryRxFrame::getFloat(float& data) {
    union {
        uint32_t uInt32Data;
        float floatData;
    } convert = {0};
    uint16_t error = getUInt32(convert.uInt32Data);
    data = convert.floatData;
    return error;
}

uint16_t DeviceLibraryRxFrame::getBytes(uint8_t data[], size_t maxBytes) {
    if (_numBytes < 1) {
        return RxFrameError | NoDataError;
    }
    size_t readAmount = maxBytes;
    if (_numBytes < maxBytes) {
        readAmount = _numBytes;
    }
    for (size_t i = 0; i < readAmount; i++) {
        data[i] = _buffer[_index++];
    }
    _numBytes -= readAmount;
    return NoError;
}

uint16_t DeviceLibraryRxFrame::getInteger(uint8_t* destination, IntegerType type,
                                      uint8_t nrOfBytes) {

    if (_numBytes < nrOfBytes) {
        return RxFrameError | NoDataError;
    }

    if (nrOfBytes > type) {
        return RxFrameError;
    }

    uint8_t offset = type - nrOfBytes;
    for (uint8_t i = 0; i < offset; i++) {
        destination[type - i - 1] = 0;
    }

    for (uint8_t i = 1; i <= nrOfBytes; i++) {
        destination[type - offset - i] = _buffer[_index++];
    }

    return 0;
}
