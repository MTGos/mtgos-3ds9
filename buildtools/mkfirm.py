#!/usr/bin/env python3
import sys
if len(sys.argv) < 4:
    print("USAGE: mkfirm.py <kernel9.elf> <kernel11.elf> <output.firm>")
print("WARNING: Currently you cannot install this FIRM, because YOU'LL BRICK YOUR 3DS!")
sighax_sig = b'\x00'*256 #TODO insert sighax signature here.
import struct
import hashlib
def get_elf_seg(f): #Return entry,section_beg,section_size,section
    f.seek(0)
    if f.read(4) != b"\x7FELF":
        raise Exception("Not an ELF file!")
    if f.read(1) != b"\x01":
        raise Exception("ELF64s are not supported!")
    if f.read(1) != b"\x01":
        raise Exception("Little Endian ELF required!")
    if f.read(1) != b"\x01":
        raise Exception("Unknown ELF version!")
    f.read(9)
    if struct.unpack("<H",f.read(2))[0] != 2:
        raise Exception("Invalid ELF format")
    if struct.unpack("<H",f.read(2))[0] != 0x28:
        raise Exception("This is not an ELF for ARM!")
    if struct.unpack("<I",f.read(4))[0] != 1:
        raise Exception("Unknown ELF version!")
    loadAddr = struct.unpack("<I",f.read(4))[0]
    phoff = struct.unpack("<I",f.read(4))[0]
    f.seek(0x2C)
    no_ent = struct.unpack("<H",f.read(2))[0]
    f.seek(phoff)
    section_begin = 0
    section_size = 0
    section = b''
    for ent in range(no_ent):
        f.seek(phoff+ent*0x20)
        if struct.unpack("<I",f.read(4))[0] != 1:
            continue
        off,vaddr,filesz,memsz=struct.unpack("<IIxxxxII",f.read(20))
        section_begin = vaddr
        section_size = memsz
        f.seek(off)
        section = f.read(filesz)
        section = section + b'\x00'*(memsz-filesz)
        break
    print("Loading section of size {} to {} with entrypoint {}".format(section_size,hex(section_begin),hex(loadAddr)))
    return (loadAddr,section_begin,section_size,section)
f1 = open(sys.argv[1],"rb")
f2 = open(sys.argv[2],"rb")
f = open(sys.argv[3],"wb")
arm9_entry,arm9_section_beg,arm9_section_size,arm9_section = get_elf_seg(f1)
arm11_entry,arm11_section_beg,arm11_section_size,arm11_section = get_elf_seg(f2)
arm9_hash=hashlib.sha256(arm9_section).digest()
arm11_hash=hashlib.sha256(arm11_section).digest()
arm9_off = 0x200
arm11_off = 0x200+arm9_section_size
f.write(b'FIRM')
f.write(struct.pack("<III",0,arm11_entry,arm9_entry))
f.write(b'\x00'*0x30)
def write_seg(section_beg, section_size, hash, off):
    f.write(struct.pack("<IIII",off,section_beg,section_size,2))
    f.write(hash)
write_seg(arm9_section_beg,arm9_section_size,arm9_hash,arm9_off)
write_seg(arm11_section_beg,arm11_section_size,arm11_hash,arm11_off)
f.write(b'\x00'*0x60)
f.write(sighax_sig)
f.write(arm9_section)
f.write(arm11_section)
