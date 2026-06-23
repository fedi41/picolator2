from PIL import Image
from pathlib import Path
import sys

def convert_sprite(input_file):
    img = Image.open(input_file).convert("1")

    width, height = img.size
    bytes_per_row = (width + 7) // 8

    data = []

    for y in range(height):
        for bx in range(bytes_per_row):
            byte = 0

            for bit in range(8):
                x = bx * 8 + bit

                if x >= width:
                    continue

                if img.getpixel((x, y)) == 0:
                    byte |= (0x80 >> bit)

            data.append(byte)

    sprite_name = Path(input_file).stem
    guard = f"{sprite_name.upper()}_H"

    output_file = f"imageBuilds/{sprite_name}.h"

    with open(output_file, "w") as f:
        f.write(f"#ifndef {guard}\n")
        f.write(f"#define {guard}\n\n")

        f.write("#include <stdint.h>\n\n")

        f.write("struct Sprite {\n")
        f.write("    uint16_t width;\n")
        f.write("    uint16_t height;\n")
        f.write("    const uint8_t* data;\n")
        f.write("};\n\n")

        f.write(
            f"static const uint8_t {sprite_name}_data[] = {{\n"
        )

        for i, byte in enumerate(data):
            if i % 12 == 0:
                f.write("    ")

            f.write(f"0x{byte:02X}, ")

            if i % 12 == 11:
                f.write("\n")

        f.write("\n};\n\n")

        f.write(
            f"static const Sprite {sprite_name} = {{\n"
        )
        f.write(f"    {width},\n")
        f.write(f"    {height},\n")
        f.write(f"    {sprite_name}_data\n")
        f.write("};\n\n")

        f.write("#endif\n")

    print(f"Generated {output_file}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python convert.py sprite.png")
        exit()

    convert_sprite(sys.argv[1])