/*
 Copyright (C) 2023, Simon D. Levy
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * Neither the name of STMicroelectronics nor the
 names of its contributors may be used to endorse or promote products
 derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND
 NON-INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS ARE DISCLAIMED.
 IN NO EVENT SHALL STMICROELECTRONICS INTERNATIONAL N.V. BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.#include <Linux.h>
 */

#pragma once

#include "vl53l1x.hpp"

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

extern "C" {
#include <i2c/smbus.h>
}

class VL53L1X_Linux : public VL53L1X {

    public:

        VL53L1X_Linux(const uint8_t bus=1, const uint8_t devAddr=0x29) 
            : VL53L1X(NULL)
        {
            // Attempt to open /dev/i2c-<NUMBER>
            char fname[32];
            sprintf(fname,"/dev/i2c-%d", bus);
            int fd = open(fname, O_RDWR);
            if (fd < 0) {
                fprintf(stderr, "Unable to open %s\n", fname);
                exit(1);
            }

            // Attempt to make this device an I2C slave
            if (ioctl(fd, I2C_SLAVE, devAddr) < 0) {
                fprintf(stderr, "ioctl failed on %s\n", fname);
                exit(1);
            }

        }
};
