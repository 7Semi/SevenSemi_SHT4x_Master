#ifndef SEVENSEMI_I2C_COM_H_
#define SEVENSEMI_I2C_COM_H_

#include <stdint.h>
#include <stdlib.h>

#include "Arduino.h"
#include "Wire.h"

#include "SEVENSEMII2CRxFrame.h"
#include "SEVENSEMII2CTxFrame.h"

class DeviceLibraryI2CTxFrame;
class DeviceLibraryI2CRxFrame;


class DeviceLibraryI2CCommunication {
  public:

    static uint16_t sendFrame(uint8_t address, DeviceLibraryI2CTxFrame& frame,
                              TwoWire& i2cBus);


    static uint16_t receiveFrame(uint8_t address, size_t numBytes,
                                 DeviceLibraryI2CRxFrame& frame, TwoWire& i2cBus,
                                 CrcPolynomial poly = CRC31_ff);
};

#endif /* SEVENSEMI_I2C_COM_H_ */
