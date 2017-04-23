config["ENABLE_N3DS_OVERCLOCK"] = get_yes_no("Enable overclocking on n3ds", True)
config["ENABLE_I2C"] = get_yes_no("Enable i2c driver", True)
if config["ENABLE_I2C"]:
    config["PROTECT_MCU"] = get_yes_no("Prevent writes to MCU firmware (Device 3, Register 5)", True)
    config["ENABLE_SCREENINIT"] = get_yes_no("Enable screeninit.", True)

