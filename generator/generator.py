#!/usr/bin/python3

import os
import sys
import getopt

from generator_selector import select_generator
from config_loader import load_config


def main(argv):
    inputfile = ''
    outputdir = ''
    arch = ''
    lib = ''

    try:
        opts, args = getopt.getopt(
            argv, "i:o:a:l:", ["file=", "output_dir=", "arch=", "lib="])
    except:
        getopt.GetoptError
        print("generator.py -i <inputfile> -o <outputdir> -a <arch> -l <lib>")
        sys.exit(2)
    for opt, arg in opts:
        if opt == "-h":
            print("generator.py -i <inputfile>")
            sys.exit()
        elif opt in ("-i", "--file"):
            inputfile = arg
        elif opt in ("-o", "--output_dir"):
            outputdir = arg
        elif opt in ("-a", "--arch"):
            arch = arg
        elif opt in ("-l", "--lib"):
            lib = arg

    print("Generate code from: ", inputfile)
    print("Files will be written to: ", outputdir)
    generator = select_generator(arch, lib)
    config = load_config(inputfile)
    generator.set_config(config)

    generator.set_output_dir(os.path.abspath(outputdir))
    generator.generate()


if __name__ == "__main__":
    main(sys.argv[1:])
