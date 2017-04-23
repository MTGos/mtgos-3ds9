config["SYSTEM"] = get_from_list("System", ["pc"])
if not get_yes_no("Build for generic x86_64"):
    config["LOWEST_CPU"] = get_from_list("Lowest supported CPU", ["pentium4", "core2", "nehalem", "westmere", "sandybridge", "ivybridge", "haswell", "broadwell", "skylake", "kabylake"])


