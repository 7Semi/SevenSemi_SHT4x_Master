#ifndef SEVENSEMI_I2C_RX_FRAME_H_
#define SEVENSEMI_I2C_RX_FRAME_H_

#include <stdint.h>
#include <stdlib.h>

#include "SevenSemiI2CCom.h"
#include "SevenSemiRxFrame.h"


class DeviceLibraryI2CRxFrame : public DeviceLibraryRxFrame {

    friend class DeviceLibraryI2CCommunication;

  public:

    DeviceLibraryI2CRxFrame(uint8_t buffer[], size_t bufferSize)
        : DeviceLibraryRxFrame(buffer, bufferSize){};
};

#endif /* SEVENSEMI_I2C_RX_FRAME_H_ */
