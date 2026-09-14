import sys, re, struct
MOD = {0x0700100E:"TDM_SINK",0x07001023:"CODEC_DMA_SINK",0x0700101A:"DATA_LOGGING",0x07001032:"PCM_CNV?",0x07001015:"MFC?",
       0x07001000:"WR_SHMEM_EP",0x07001002:"GAIN?",0x07001003:"PCM_DEC?",0x07001011:"?",0x07001010:"?"}
def words(path):
    txt=open(path).read()
    blocks=re.split(r"\n  (subgraph data|connections) rc=", txt)
    out={}
    for i in range(1,len(blocks),2):
        body=blocks[i+1]
        ws=[int(w,16) for w in re.findall(r"\b[0-9a-f]{8}\b", body.split(":",1)[1] if ":" in body else body)]
        out[blocks[i]]=ws
    return out
def b(ws): return b"".join(struct.pack("<I",w) for w in ws)
def params(data):
    o=0
    while o+16<=len(data):
        iid,pid,size,err=struct.unpack_from("<IIII",data,o); o+=16
        pl=data[o:o+size]; o+= (size+7)//8*8 if size%8 else size
        yield iid,pid,pl
for path in sys.argv[1:]:
    print("#####",path)
    w=words(path)
    blob=b(w.get("subgraph data",[]))
    for iid,pid,pl in params(blob):
        u=[struct.unpack_from("<I",pl,i)[0] for i in range(0,len(pl)//4*4,4)]
        if pid==0x08001005:
            n=u[0]; print(f"  SUB_GRAPH_CONFIG n={n}"); i=1
            for _ in range(n):
                sg,np_=u[i],u[i+1]; i+=2; props=[]
                for _ in range(np_):
                    p,s=u[i],u[i+1]; i+=2; vals=u[i:i+(s//4)]; i+=s//4; props.append((hex(p),[hex(x) for x in vals]))
                print(f"    sg {sg:08x} props={props}")
        elif pid==0x08001000:
            n=u[0]; print(f"  CONTAINER_CONFIG n={n}"); i=1
            for _ in range(n):
                c,np_=u[i],u[i+1]; i+=2; props=[]
                for _ in range(np_):
                    p,s=u[i],u[i+1]; i+=2; vals=u[i:i+(s//4)]; i+=s//4; props.append((hex(p),[hex(x) for x in vals]))
                print(f"    cont {c:08x} props={props}")
        elif pid==0x08001002:
            n=u[0]; print(f"  MODULE_LIST n={n}"); i=1
            for _ in range(n):
                sg,cont,nm=u[i],u[i+1],u[i+2]; i+=3
                mods=[]
                for _ in range(nm):
                    mid,miid=u[i],u[i+1]; i+=2; mods.append(f"{mid:08x}({MOD.get(mid,"")})@{miid:x}")
                print(f"    sg {sg:08x} cont {cont:08x}: {mods}")
        elif pid==0x08001003:
            n=u[0]; print(f"  MODULE_PROP n={n}"); i=1
            for _ in range(n):
                miid,np_=u[i],u[i+1]; i+=2; props=[]
                for _ in range(np_):
                    p,s=u[i],u[i+1]; i+=2; vals=u[i:i+(s//4)]; i+=s//4; props.append((hex(p),[hex(x) for x in vals]))
                print(f"    mod {miid:x} {props}")
        elif pid==0x08001004:
            n=u[0]; print(f"  MODULE_CONN n={n}")
            for k in range(n):
                s_,sp,d,dp=u[1+4*k:5+4*k]; print(f"    {s_:x}:{sp} -> {d:x}:{dp}")
        else:
            print(f"  param {pid:08x} iid={iid:x} size={len(pl)}: {[hex(x) for x in u[:24]]}")
    cw=w.get("connections",[])
    print("  connections words:", [hex(x) for x in cw])
