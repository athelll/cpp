#!/usr/bin env python3

import sys

def markdownify(og_file):
    header1 = "="
    header2 = "-"
    code_format ="```"
    new_file = "README.md"

    try:
        file = open(og_file, "r")
        lines = file.readlines()
    except FileNotFoundError:
        print(f"file not found {r_file}")
    except Exception as e:
        print(f"Error occured {e}")
    file.close()

    for i in range(len(lines)):
        line = lines[i]
        if line.startswith('=') and line.endswith('=\n') and i in [0, 1]:
            lines[i] = line.replace('=', '')
            print(f"line {i+1}: converted introductions")

        if line.startswith('==') or line.startswith('== '):
            lines[i] = line.replace("==", '')
            lines[i] += (len(lines[i]) * header1)
            print(f"line {i+1}: converted to header 1")

        if line.startswith('[[') and line.endswith(']]\n'):
            lines[i] = line.replace('[[', '').replace(']]\n', '')
            lines[i] += ('\n' + len(lines[i])*header2)
            print(f"line {i+1}: converted to header 2")

        symbol = line[:3]
        if symbol in ['{{{', '}}}']:
            lines[i] = line.replace(symbol, code_format)
            print(f"line {i+1}: converted code formats")

    with open(new_file, "w") as file:
        file.writelines(lines)
        print("written into new file")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage python3 script.py file")
    else:
        markdownify(sys.argv[1])
        
