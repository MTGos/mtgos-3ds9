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
