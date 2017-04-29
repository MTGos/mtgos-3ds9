#pragma once
#include <config.h>
#include <stdint.h>
class I2C {
    private:
    int currDev;
    int currReg;
    int busID;

    public:
    I2C();
    ~I2C();
    auto waitBusy() -> void;
    auto getResult() -> bool;
    auto stop() -> bool;
    auto selectDev(int dev) -> bool;
    auto selectReg(int reg) -> bool;
    auto write(uint8_t data) -> bool;
    auto read() -> uint8_t;
};
