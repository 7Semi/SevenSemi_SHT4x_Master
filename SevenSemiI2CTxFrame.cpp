#include "SevenSemiI2CTxFrame.h"

#include <stdint.h>
#include <stdlib.h>

#include "SevenSemiCrc.h"
#include "SevenSemiErrors.h"

DeviceLibraryI2CTxFrame::DeviceLibraryI2CTxFrame(uint8_t buffer[], size_t bufferSize,
                                         size_t numCommandBytes,
                                         CrcPolynomial poly)
    : _buffer(buffer), _bufferSize(bufferSize), _index(numCommandBytes),
      _numCommandBytes(numCommandBytes), _polynomial_type(poly) {
}

DeviceLibraryI2CTxFrame::DeviceLibraryI2CTxFrame(uint8_t buffer[], size_t bufferSize,
                                         CrcPolynomial poly)
    : DeviceLibraryI2CTxFrame(buffer, bufferSize, 2, poly) {
}

DeviceLibraryI2CTxFrame DeviceLibraryI2CTxFrame::createWithUInt8Command(
    uint8_t command, uint8_t buffer[], size_t bufferSize, CrcPolynomial poly) {
    DeviceLibraryI2CTxFrame instance =
        DeviceLibraryI2CTxFrame(buffer, bufferSize, 1, poly);
    instance._buffer[0] = command;
    return instance;
}

DeviceLibraryI2CTxFrame DeviceLibraryI2CTxFrame::createWithUInt16Command(
    uint16_t command, uint8_t buffer[], size_t bufferSize, CrcPolynomial poly) {
    DeviceLibraryI2CTxFrame instance =
        DeviceLibraryI2CTxFrame(buffer, bufferSize, 2, poly);
    instance._buffer[0] = static_cast<uint8_t>((command & 0xFF00) >> 8);
    instance._buffer[1] = static_cast<uint8_t>((command & 0x00FF) >> 0);
    return instance;
}

uint16_t DeviceLibraryI2CTxFrame::addCommand(uint16_t command) {
    if (_bufferSize < 2) {
        return TxFrameError | BufferSizeError;
    }
    _buffer[0] = static_cast<uint8_t>((command & 0xFF00) >> 8);
    _buffer[1] = static_cast<uint8_t>((command & 0x00FF) >> 0);
    return NoError;
}

uint16_t DeviceLibraryI2CTxFrame::addUInt32(uint32_t data) {
    uint16_t error = _addByte(static_cast<uint8_t>((data & 0xFF000000) >> 24));
    error |= _addByte(static_cast<uint8_t>((data & 0x00FF0000) >> 16));
    error |= _addByte(static_cast<uint8_t>((data & 0x0000FF00) >> 8));
    error |= _addByte(static_cast<uint8_t>((data & 0x000000FF) >> 0));
    return error;
}

uint16_t DeviceLibraryI2CTxFrame::addInt32(int32_t data) {
    return addUInt32(static_cast<uint32_t>(data));
}

uint16_t DeviceLibraryI2CTxFrame::addUInt16(uint16_t data) {
    uint16_t error = _addByte(static_cast<uint8_t>((data & 0xFF00) >> 8));
    error |= _addByte(static_cast<uint8_t>((data & 0x00FF) >> 0));
    return error;
}

uint16_t DeviceLibraryI2CTxFrame::addInt16(int16_t data) {
    return addUInt16(static_cast<uint16_t>(data));
}

uint16_t DeviceLibraryI2CTxFrame::addUInt8(uint8_t data) {
    return _addByte(data);
}

uint16_t DeviceLibraryI2CTxFrame::addInt8(int8_t data) {
    return _addByte(static_cast<uint8_t>(data));
}

uint16_t DeviceLibraryI2CTxFrame::addBool(bool data) {
    return _addByte(static_cast<uint8_t>(data));
}

uint16_t DeviceLibraryI2CTxFrame::addFloat(float data) {
    union {
        uint32_t uInt32Data;
        float floatData;
    } convert;

    convert.floatData = data;
    return addUInt32(convert.uInt32Data);
}

uint16_t DeviceLibraryI2CTxFrame::addBytes(const uint8_t data[],
                                       size_t dataLength) {
    uint16_t error = 0;
    for (size_t i = 0; i < dataLength; i++) {
        error |= _addByte(data[i]);
    }
    return error;
}

uint16_t DeviceLibraryI2CTxFrame::_addByte(uint8_t data) {
    if (_bufferSize <= _index) {
        return TxFrameError | BufferSizeError;
    }
    _buffer[_index++] = data;
    if ((_index - _numCommandBytes) % 3 == 2) {
        if (_bufferSize <= _index) {
            return TxFrameError | BufferSizeError;
        }
        uint8_t crc = generateCRC(&_buffer[_index - 2], 2, _polynomial_type);
        _buffer[_index++] = crc;
    }
    return NoError;
}
