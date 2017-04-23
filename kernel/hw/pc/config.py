config["ENABLE_FRAMEBUFFER"] = get_yes_no("Use VESA Framebuffer?", True)
if config["ENABLE_FRAMEBUFFER"]:
    config["ENABLE_FRAMEBUFFER_UNICODE"] = get_yes_no("Enable full Unicode BMP font (Adds around 1MB to binary)", False)
