#include "SevenSemiErrors.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

void err_discription(uint16_t error, char errorMessage[],
                   size_t errorMessageSize) {

    uint16_t highLevelError = error & 0xFF00;
    uint16_t lowLevelError = error & 0x00FF;

    if (error & HighLevelError::SensorSpecificError) {
        snprintf(errorMessage, errorMessageSize, "Sensor specific error: 0x%2x",
                 lowLevelError);
        return;
    }

    switch (highLevelError) {
        case HighLevelError::NoError:
            if (!error) {
                strncpy(errorMessage, "No error", errorMessageSize);
                return;
            }
            break;
        case HighLevelError::WriteError:
            switch (lowLevelError) {
                case LowLevelError::Undefined:
                    strncpy(errorMessage, "Write error",
                            errorMessageSize);
                    return;
                case LowLevelError::InternalBufferSizeError:
                    strncpy(errorMessage,
                            "Data too long to fit in transmit buffer",
                            errorMessageSize);
                    return;
                case LowLevelError::I2cAddressNack:
                    strncpy(errorMessage,
                            "Received NACK on transmit of address",
                            errorMessageSize);
                    return;
                case LowLevelError::I2cDataNack:
                    strncpy(errorMessage, "Received NACK on transmit of data",
                            errorMessageSize);
                    return;
                case LowLevelError::I2cOtherError:
                    strncpy(errorMessage, "Error writing to I2C bus",
                            errorMessageSize);
                    return;
            }
            break;
        case HighLevelError::ReadError:
            switch (lowLevelError) {
                case LowLevelError::Undefined:
                    strncpy(errorMessage, "Read error", errorMessageSize);
                    return;
                case LowLevelError::NonemptyFrameError:
                    strncpy(errorMessage, "Frame already contains data",
                            errorMessageSize);
                    return;
                case LowLevelError::CRCError:
                    strncpy(errorMessage, "Wrong CRC found", errorMessageSize);
                    return;
                case LowLevelError::WrongNumberBytesError:
                    strncpy(errorMessage, "Number of bytes not a multiple of 3",
                            errorMessageSize);
                    return;
                case LowLevelError::NotEnoughDataError:
                    strncpy(errorMessage, "Not enough data received",
                            errorMessageSize);
                    return;
                case LowLevelError::InternalBufferSizeError:
                    strncpy(errorMessage, "Internal I2C buffer too small",
                            errorMessageSize);
                    return;
            }
            break;
        case HighLevelError::ExecutionError: {
            char format[] = "Execution error, status register: 0x%x";
            snprintf(errorMessage, errorMessageSize, format, lowLevelError);
            return;
        }
        case HighLevelError::TxFrameError:
            switch (lowLevelError) {
                case LowLevelError::Undefined:
                    strncpy(errorMessage, "Tx frame error", errorMessageSize);
                    return;
                case LowLevelError::BufferSizeError:
                    strncpy(errorMessage, "Not enough space in buffer",
                            errorMessageSize);
                    return;
            }
            break;
        case HighLevelError::RxFrameError:
            switch (lowLevelError) {
                case LowLevelError::Undefined:
                    strncpy(errorMessage, "Rx frame error", errorMessageSize);
                    return;
                case LowLevelError::BufferSizeError:
                    strncpy(errorMessage, "Not enough space in buffer",
                            errorMessageSize);
                    return;
                case LowLevelError::NoDataError:
                    strncpy(errorMessage, "No more data in frame",
                            errorMessageSize);
                    return;
            }
    }
    strncpy(errorMessage, "Error processing error", errorMessageSize);
    return;
}
