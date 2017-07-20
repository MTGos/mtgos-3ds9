config["LOWEST_CPU"] = "arm946e-s"
config["ENABLE_THUMB"] = get_yes_no("Enable Thumb", True)
import sys
sys.argv=["","kernel/mmaps/3ds9.mc"]
from buildtools import mmapcomp
