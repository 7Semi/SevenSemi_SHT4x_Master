#ifndef _SEVENSEMI_ERRORS_H_
#define _SEVENSEMI_ERRORS_H_

#include <stdint.h>
#include <stdlib.h>

enum HighLevelError : uint16_t {
    NoError = 0,
    WriteError = 0x0100,
    ReadError = 0x0200,
    TxFrameError = 0x0300,
    RxFrameError = 0x0400,
    ExecutionError = 0x0500,
    SensorSpecificError = 0x8000,
};

enum LowLevelError : uint8_t {
    Undefined = 0,
    NonemptyFrameError,
    NoDataError,
    BufferSizeError,
    WrongNumberBytesError,
    CRCError,
    I2cAddressNack,
    I2cDataNack,
    I2cOtherError,
    NotEnoughDataError,
    InternalBufferSizeError,
};

void err_discription(uint16_t error, char errorMessage[],
                   size_t errorMessageSize);

#endif /* _SEVENSEMI_ERRORS_H_ */
