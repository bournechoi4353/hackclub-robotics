#!/usr/bin/env python3
"""Convert a PNG into an LVGL v8 TRUE_COLOR C array for LV_COLOR_DEPTH=32.

Usage:
    python3 tools/png_to_lvgl.py assets/field.png field_match 216 src/field_match.c
    python3 tools/png_to_lvgl.py assets/logo.png logo WxH src/logo.c alpha

Args: <input.png> <c_symbol_name> <size> <output.c> [alpha]
  <size> is either "N" (square NxN) or "WxH" (keep aspect / exact box).
  add "alpha" to preserve transparency (CF_TRUE_COLOR_ALPHA); otherwise opaque.
Emits an `lv_img_dsc_t <name>` you can draw with lv_img_set_src(obj, &<name>).
Pixel byte order is B,G,R,A (LVGL 32-bit native).
"""
import sys
from PIL import Image

def main():
    if len(sys.argv) not in (5, 6):
        print(__doc__)
        sys.exit(1)
    src, name, size, out = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4]
    use_alpha = len(sys.argv) == 6 and sys.argv[5] == "alpha"
    if "x" in size:
        w, h = (int(v) for v in size.split("x"))
    else:
        w = h = int(size)

    img = Image.open(src).convert("RGBA").resize((w, h), Image.LANCZOS)
    px = img.load()

    body = []
    for y in range(h):
        for x in range(w):
            r, g, b, a = px[x, y]
            body.append(f"0x{b:02x},0x{g:02x},0x{r:02x},0x{(a if use_alpha else 255):02x},")

    cf = "LV_IMG_CF_TRUE_COLOR_ALPHA" if use_alpha else "LV_IMG_CF_TRUE_COLOR"
    with open(out, "w") as f:
        f.write('#include "liblvgl/lvgl.h"\n\n')
        f.write("#ifndef LV_ATTRIBUTE_MEM_ALIGN\n#define LV_ATTRIBUTE_MEM_ALIGN\n#endif\n\n")
        f.write(f"static const LV_ATTRIBUTE_MEM_ALIGN uint8_t {name}_map[] = {{\n")
        # 16 pixels (64 bytes) per line
        for i in range(0, len(body), 16):
            f.write("  " + "".join(body[i:i+16]) + "\n")
        f.write("};\n\n")
        f.write(f"const lv_img_dsc_t {name} = {{\n")
        f.write(f"  .header.cf = {cf},\n")
        f.write("  .header.always_zero = 0,\n")
        f.write("  .header.reserved = 0,\n")
        f.write(f"  .header.w = {w},\n")
        f.write(f"  .header.h = {h},\n")
        f.write(f"  .data_size = {w*h*4},\n")
        f.write(f"  .data = {name}_map,\n")
        f.write("};\n")

    print(f"wrote {out}  ({w}x{h}, {w*h*4} bytes of image data)")

if __name__ == "__main__":
    main()
