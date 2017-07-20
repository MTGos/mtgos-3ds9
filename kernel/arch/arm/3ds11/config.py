config["LOWEST_CPU"] = "arm11mpcore"
config["ENABLE_HARD"] = get_yes_no("Enable VFP ABI", True)
if not config["ENABLE_HARD"]:
    config["ENABLE_THUMB"] = get_yes_no("Enable Thumb")
import sys
sys.argv=["","kernel/mmaps/3ds11.mc"]
from buildtools import mmapcomp
