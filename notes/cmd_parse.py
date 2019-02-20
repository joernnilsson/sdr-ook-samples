
rcs = {}

for l in open("cmd.txt"):
    try:
        key, val = l.split(":")
        print("uint8_t " + key + "[] \t= {" + val.strip() + "};")

        rc, rc_num, ch_num, cmd = key.split("_")

        if rc_num not in rcs:
            rcs[rc_num] = []
        
        rcs[rc_num].append(key)
    except:
        pass


for k,v in rcs.items():
    out = "uint8_t * cmdRemote__error"+k+"[] \t= {" + ", ".join(v) + "};"
    print(out)
    
print("uint8_t ** cmdRemotes[] = {" + ", ".join("cmdRemote"+k for k in rcs.keys()) + "};")