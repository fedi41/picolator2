from PIL import Image
import os

INPUT_FILE = "image.png"
OUTPUT_FILE = "image.h"

img = Image.open(INPUT_FILE).convert("RGB")

name = os.path.splitext(os.path.basename(INPUT_FILE))[0]

with open(OUTPUT_FILE, "w") as f:
    f.write("#pragma once\n\n")
    f.write("#include <stdint.h>\n\n")

    f.write(f"const uint16_t {name}[{img.width * img.height}] = {{\n")

    count = 0

    for y in range(img.height):
        for x in range(img.width):
            r, g, b = img.getpixel((x, y))

            rgb565 = (
                ((r >> 3) << 11) |
                ((g >> 2) << 5) |
                (b >> 3)
            )

            # Bytes swappen
            rgb565 = ((rgb565 << 8) | (rgb565 >> 8)) & 0xFFFF
            f.write(f"0x{rgb565:04X},")

            count += 1

            if count % 12 == 0:
                f.write("\n")
            else:
                f.write(" ")

    f.write("\n};\n\n")
    f.write(f"constexpr int {name}_width = {img.width};\n")
    f.write(f"constexpr int {name}_height = {img.height};\n")

print(f"Exportiert: {OUTPUT_FILE}")