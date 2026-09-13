#!/usr/bin/env python3
"""Write the gmobile display-panel definition for zeus.

gmobile takes the cutout as an SVG-ish path. Its own entries are built from
cubic beziers, and arc commands did not render correctly here, so the punch-hole
is four beziers - the standard 0.5523 circle approximation.

  mk-cutout.py <cx> <cy> <r>
"""
import json, pathlib, sys

cx, cy, r = (int(a) for a in sys.argv[1:4])
k = round(r * 0.5523, 2)
rk = round(r - k, 2)

path = (f"M {cx-r},{cy} "
        f"c 0,-{k} {rk},-{r} {r},-{r} "
        f"c {k},0 {r},{rk} {r},{r} "
        f"c 0,{k} -{rk},{r} -{r},{r} "
        f"c -{k},0 -{r},-{rk} -{r},-{r} "
        f"Z")

doc = {
    "name": "Xiaomi 12 Pro",
    "x-res": 1440,
    "y-res": 3200,
    "width": 70,
    "height": 156,
    "border-radius": 120,
    "cutouts": [{"name": "punch-hole", "path": path}],
}
out = json.dumps(doc, indent=2) + "\n"
for p in ("src/gmobile/xiaomi,zeus.json",
          "src/pmaports/device-xiaomi-zeus/xiaomi,zeus.json"):
    pathlib.Path(p).write_text(out)
print("centre (%d,%d) r=%d" % (cx, cy, r))
