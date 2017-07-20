#!/usr/bin/env python3
import sys,os
sf = sys.argv[1]
tf = os.path.splitext(sf)[0] + ".mmap"
hf = os.path.splitext(sf)[0] + ".mh"
with open(sf) as f:
    code = [ x[:-1] for x in f.readlines()]
obj = []
endian='little'
bits=32
for line in code:
    data = b''
    a = line.split(' ')
    if a[0] == "DEVICETYPE":
        data+=b'\x00'
        data+=b'\x01'
        devicetypes={"PC":b'\x00', "CONSOLE":b'\x01', "EMBEDDED":b'\x02'}
        data+=devicetypes[a[1]]
    elif a[0] == "DEVICENAME":
        data+=b'\x01'
        data+=len(a[1]).to_bytes(1,'little')
        data+=a[1].encode("UTF-8")
    elif a[0] == "CPUARCH":
        data+=b'\x02'
        data+=b'\x01'
        archs = {"X86":b'\x00', "X86_64":b'\x01', "ARM":b'\x02'}
        data+=archs[a[1]]
    elif a[0] == "ENDIAN":
        data+=b'\x03'
        data+=b'\x01'
        if a[1] == "BIG":
            data+=b'\x00'
            endian='big'
        else:
            data+=b'\x01'
            endian="little"
    elif a[0] == "BITS":
        data+=b'\x04'
        data+=b'\x01'
        if a[1] == "32":
            data+=b'\x20'
            bits=32
        else:
            data+=b'\x40'
            bits=64
    elif a[0] == "REGION":
        data+=b'\x05'
        data+=(bits//4+1).to_bytes(1,endian)
        data+=int(a[1],16).to_bytes(bits//8,endian)
        data+=int(a[2],16).to_bytes(bits//8,endian)
        perms={
                "NONE": 0,
                "X": 1,
                "W": 2,
                "WX": 3,
                "R": 4,
                "RX": 5,
                "RW": 6,
                "RWX": 7
                }
        data+=perms[a[3]].to_bytes(1,endian)
    elif a[0] == "":
        continue
    else:
        raise ValueError("Unknown command '"+a[0]+"'")
    obj.append(data)
mmdata = b'MMAP' + bytes(4) + len(obj).to_bytes(4,'little')
for o in obj:
    mmdata += o
with open(tf,"wb") as f:
    f.write(mmdata)
with open(hf, "w") as f:
    f.write("#pragma once\n")
    f.write("#include <stdint.h>\n")
    f.write("uint8_t mmap[] = {\n")
    for b in mmdata:
        f.write(hex(b)+", ")
    f.write("\n};\n")
