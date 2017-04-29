config["ENABLE_EXTRA_MEMORY"] = get_yes_no("Enable 512KB of memory on n3DS", True)
add_driver(True, "framebuffer")
add_driver(False, "picafb")
print("Enable complete Unicode font: NO (because of the size)")
config["ENABLE_FRAMEBUFFER_UNICODE"] = False
