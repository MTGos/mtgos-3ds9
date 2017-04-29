#pragma once
#include "../i2c/i2c.hpp"
namespace MCU {
extern I2C access;
auto getVersionLo() -> unsigned char;
auto getVersionHi() -> unsigned char;
auto getLCDFlickerTop() -> unsigned char;
auto setLCDFlickerTop(unsigned char) -> void;
auto getLCDFlickerBottom() -> unsigned char;
auto setLCDFlickerTop(unsigned char) -> void;
auto get3DSlider() -> unsigned char;
auto getVolume() -> unsigned char;
auto getBatteryPercent() -> unsigned char;
auto getSystemVoltage() -> unsigned char;
auto isCharging() -> bool;
auto isOpen() -> bool;
extern uint8_t HIDStatus;
auto updateHIDStatus() -> void;
auto powerButtonPressed() -> bool;
auto powerButtonLongPressed() -> bool;
auto homeButtonPressed() -> bool;
auto homeButtonReleased() -> bool;
auto wifiEnabled() -> bool;
auto closed() -> bool;
auto opened() -> bool;
auto poweroff() -> void;
auto reboot() -> void;
auto enableTopLCD() -> void;
auto disableTopLCD() -> void;
auto enableBottomLCD() -> void;
auto disableBottomLCD() -> void;
auto setWifiLED(char val) -> void;
auto setCameraLED(char val) -> void;
auto set3DLED(char val) -> void;
struct RTC_date {
    unsigned char seconds;
    unsigned char minutes;
    unsigned char hours;
    unsigned char days;
    unsigned char months;
    unsigned char years;
};
auto getRTC(RTC_date *) -> void;
auto setRTC(RTC_date *) -> void;
}
