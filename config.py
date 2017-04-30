#!/usr/bin/env python3
"This tool is for configuring mtgos"
def get_from_list(p,l):
    print("Select one of:")
    for i,j in enumerate(l):
        print(str(i)+":",j)
    if len(l) == 1:
        print(p+": 0 (autoselected)")
        return l[0]
    i=-1
    while (i<0) or (i >= len(l)):
        x = input(p+": ")
        try:
            i = int(x)
        except:
            i = -1
    print()
    return l[i]
def get_yes_no(p, default=None):
    x="a"
    defaultstr = "[yn]"
    if default:
        defaultstr = "[Yn]"
    elif default == False:
        defaultstr = "[yN]"
    while x not in "ynYN":
        x = input(p+" "+defaultstr+": ")
        if (x == "") and default is not None:
            return default
    return x in "yY"
def add_driver(common, name):
    if common:
        drivers.append("hw/"+name+"/")
    else:
        drivers.append("hw/"+config["SYSTEM"]+"/"+name+"/")
drivers=[]
config={}
config["ARCH"] = get_from_list("Architecture", ["x86","x86_64","arm"])
exec(open("kernel/arch/"+config["ARCH"]+"/config.py").read())
exec(open("kernel/arch/"+config["ARCH"]+"/"+config["SYSTEM"]+"/config.py").read())
exec(open("kernel/cpu/"+config["ARCH"]+"/"+config["LOWEST_CPU"]+"/config.py").read())
exec(open("kernel/hw/"+config["SYSTEM"]+"/config.py").read())
exec(open("kernel/hw/config.py").read())
with open("config.cmake", "w") as f:
    for key, val in config.items():
        if val == True:
            f.write('SET('+key+' 1)\n')
        elif val != False:
            f.write('SET('+key+' '+str(val)+')\n')
    for driver in drivers:
        f.write("SET(DRIVER_SRCS ${DRIVER_SRCS} "+driver+"*.c "+driver+"*.cpp "+driver+"*.s)\n")

with open("config.h", "w") as f:
    for key, val in config.items():
        if val == True:
            f.write("#define "+key+" 1\n")
        elif val == False:
            f.write("#undef "+key+"\n")
        elif isinstance(val, int):
            f.write("#define "+key+" ("+str(val)+")\n")
        else:
            f.write("#define "+key+' "'+val+'"\n')
if "ENABLE_FRAMEBUFFER_UNICODE" in config:
    #Write the font
    chars=range(65536)
    if not config["ENABLE_FRAMEBUFFER_UNICODE"]:
        chars = [0x0000, 0x263A, 0x263B, 0x2665, 0x2666, 0x2663, 0x2660, 0x2022, 0x25D8, 0x25CB, 0x25D9, 0x2642, 0x2640, 0x266A, 0x266B, 0x263C,
                 0x25BA, 0x25C4, 0x2195, 0x203C, 0x00B6, 0x00A7, 0x25AC, 0x21A8, 0x2191, 0x2193, 0x2192, 0x2190, 0x221F, 0x2194, 0x25B4, 0x25BC]
        chars += list(range(0x20, 0x7F))
        chars += [0x2302]
        chars += [0xC7, 0xFC, 0xE9, 0xE2, 0xE4, 0xE0, 0xE5, 0xE7, 0xEA, 0xEB, 0xE8, 0xEF, 0xEE, 0xEC, 0xC4, 0xC5,
                  0xC9, 0xE6, 0xC6, 0xF4, 0xF6, 0xF2, 0xFB, 0xF9, 0xFF, 0xD6, 0xDC, 0xA2, 0xA3, 0xA5, 0x20A7, 0x0192,
                  0xE1, 0xED, 0xF3, 0xFA, 0xF1, 0xD1, 0xAA, 0xBA, 0xBF, 0x2310, 0xAC, 0xBD, 0xBC, 0xA1, 0xAB, 0xBB,
                  0x2591, 0x2592, 0x2593, 0x2502, 0x2524, 0x2561, 0x2562, 0x2556, 0x2555, 0x2563, 0x2551, 0x2557, 0x255D, 0x255C, 0x255B, 0x2510,
                  0x2514, 0x2534, 0x252C, 0x251C, 0x2500, 0x253C, 0x255E, 0x255F, 0x255A, 0x2554, 0x2569, 0x2566, 0x2560, 0x2550, 0x256C, 0x2567,
                  0x2568, 0x2564, 0x2565, 0x2559, 0x2558, 0x2552, 0x2553, 0x256B, 0x256A, 0x2518, 0x250C, 0x2588, 0x2584, 0x258C, 0x2590, 0x2580,
                  0x03B1, 0x00DF, 0x0393, 0x03C0, 0x03A3, 0x03C3, 0x00B5, 0x03C4, 0x03A6, 0x0398, 0x03A9, 0x03B4, 0x221E, 0x03C6, 0x03B5, 0x2229,
                  0x2261, 0x00B1, 0x2265, 0x2264, 0x2320, 0x2321, 0x00F7, 0x2248, 0x00B0, 0x2219, 0x00B7, 0x221A, 0x207F, 0x00B2, 0x25A0, 0x00A0]
        chars.sort()
    ch=chars
    chars=[]
    for c in ch:
        chars.append("{0:0{1}X}".format(c,4))
    x=open("unifont.hex").readlines()
    from subprocess import *
    p = Popen(["./fontgen.py"], stdin=PIPE)
    for l in x:
        if l[:4] in chars:
            p.stdin.write(l.encode("UTF-8"))
    p.stdin.close()
    p.wait()

print("Generating sourcecode…")
int_handler = open("kernel/arch/"+config["ARCH"]+"/int.s","w")
import os
try:
    os.makedirs("kernel/arch/"+config["ARCH"]+"/include")
except:
    pass
reg_struct = open("kernel/arch/"+config["ARCH"]+"/include/regs.h","w")
exec(open("kernel/arch/"+config["ARCH"]+"/sourcegen.py").read())
int_handler.close()
reg_struct.close()
