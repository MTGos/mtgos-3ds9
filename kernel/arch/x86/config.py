config["SYSTEM"] = get_from_list("System", ["pc"])
if not get_yes_no("Build for generic x86"):
    config["LOWEST_CPU"] = get_from_list("Lowest supported CPU", ["486", "pentium", "pentium2", "pentium3", "pentium4"])
else:
    config["LOWEST_CPU"] = "486"

