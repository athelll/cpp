import sys

def markdownify(r_file):
    if len(r_file) == 0:
        print("we need a file over here")
        return

    header1 = "========================================================================="
    header2 = "-----------------------------------------------"
    code_format ="```"
    new_file = "README.md"

    try:

        with open(r_file, "r") as file:
            lines = file.readlines()
            for i in range(len(lines)):
                line = lines[i]
                if line.startswith('==') or line.startswith('== '):
                   lines[i] = line.replace("==", '') + header1
                   print("converted all header 1s")

                if line.startswith('[[') and line.endswith(']]\n'):
                    lines[i] = line.replace('[[', '').replace(']]\n', '')
                    lines[i] += ('\n' + header2)
                    print("converted all header 2s")

                symbol = line[:3]
                if symbol in ['{{{', '}}}']:
                    lines[i] = line.replace(symbol, code_format)
                    print("converted code formats")
            with open(new_file, "w") as file:
                file.writelines(lines)
                print("written into new file")

    except FileNotFoundError:
        print(f"file not found {r_file}")
    except Exception as e:
        print(f"Error occured {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage python3 script.py file")
    else:
        markdownify(sys.argv[1])
