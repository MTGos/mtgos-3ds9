#pragma once
#include "../i2c/i2c.hpp"
/**
 * Namespace containing all currently supported MCU functions
 */
namespace MCU {
extern I2C access;                            ///< Private variable which is used to access the MCU
auto getVersionLo() -> unsigned char;         ///< Installed MCU firmware version. Current is 56 on n3ds and 27 on o3ds
auto getVersionHi() -> unsigned char;         ///< Installed MCU firmware version. Current is 3 on n3ds and 2 on o3ds
auto getLCDFlickerTop() -> unsigned char;     ///< Returns the top LCDs bias voltage in some wax
auto setLCDFlickerTop(unsigned char) -> void; ///< Changes the top LCDs bias voltage
auto getLCDFlickerBottom() -> unsigned char;  ///< Returns the bottom LCDs bias voltage
auto setLCDFlickerTop(unsigned char) -> void; ///< Changes the bottom LCDs bias voltage
auto get3DSlider() -> unsigned char;          ///< Returns how far the 3D slider has moved up
auto getVolume() -> unsigned char;            ///< Returns the current volume
auto getBatteryPercent() -> unsigned char;    ///< Returns the battery percentage
auto getSystemVoltage() -> unsigned char;     ///< Returns the system voltage
auto isCharging() -> bool;                    ///< Returns true if the system is being charged
auto isOpen() -> bool;                        ///< Returns true if the system is not closed
extern uint8_t HIDStatus;                     ///< Storage variable for a few functions
auto updateHIDStatus() -> void;               ///< Updates HIDStatus
auto powerButtonPressed() -> bool;            ///< true if the power button got pressed
auto powerButtonLongPressed() -> bool;        ///< true if the power button got pressed for a long time
auto homeButtonPressed() -> bool;             ///< true if the home button got pressed
auto homeButtonReleased() -> bool;            ///< true if the home button got released
auto wifiEnabled() -> bool;                   ///< true if wifi is enabled
auto closed() -> bool;                        ///< true if the system got closed
auto opened() -> bool;                        ///< true if the system got reopened
auto poweroff() -> void;                      ///< powers the system off
auto reboot() -> void;                        ///< restarts the system
auto enableTopLCD() -> void;                  ///< enables the top LCD
auto disableTopLCD() -> void;                 ///< disables the top LCD
auto enableBottomLCD() -> void;               ///< enables the bottom LCD
auto disableBottomLCD() -> void;              ///< disables the bottom LCD
auto setWifiLED(char val) -> void;            ///< set to a value between 1 and 0xF to turn on the Wifi LED
auto setCameraLED(char val) -> void;          ///< set to a value between 1 and 0xF to turn on the Camera LED
auto set3DLED(char val)
    -> void; ///< set to a value between 1 and 0xF to turn on the 3D LED. Most devices don't have this LED
/**
 * Struct for a RTC. Range is between 2000 and 2050.
 * Will probably be off by a lot, as the raw value is adjusted.
 */
struct RTC_date {
    unsigned char seconds; ///< seconds. Range: 0…59
    unsigned char minutes; ///< minutes. Range: 0…59
    unsigned char hours;   ///< hours. Range: 0…23
    unsigned char days;    ///< days. Range: 1…31
    unsigned char months;  ///< months. Range: 1…12
    unsigned char years;   ///< years. Range: 0…50
};
auto getRTC(RTC_date *) -> void; ///< sets the passed struct to the current date
auto setRTC(RTC_date *) -> void; ///< sets the RTC to the data in the passed struct.
}
