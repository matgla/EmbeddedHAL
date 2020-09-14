#!/usr/bin/python3

# This file is part of Embedded HAL project.
# Copyright (C) 2020 Mateusz Stadnik
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import argparse
import os
import json
import sys
import re

from jinja2 import Template, Environment, FileSystemLoader


parser = argparse.ArgumentParser(description = "Linker script generator for HAL")
parser.add_argument("-i", "--input", dest="input", action="store", help="Path to configuration file file", required=True)
parser.add_argument("-o", "--output", dest="output", action="store", help="Path to output file", required=True)
parser.add_argument("-s", "--sections", dest="options", action="store", help="Additional sections in format: <name>:<access(r/w/x)>:address:length, separated by comma (',')")

args, rest = parser.parse_known_args()

size_units = {
    "B": 1,
    "KB": 10**3,
    "K": 10**3,
    "MB": 10**6,
    "M": 10**6,
    "GB": 10**9,
    "G": 10**9,
    "TB": 10**12,
    "T": 10**12
}

import re

# based on https://stackoverflow.com/a/60708339
units = {
    "B": 1,
    "K": 2**10,
    "KB": 2**10,
    "M": 2**20,
    "MB": 2**20,
    "G": 2**30,
    "GB": 2**30,
    "T": 2**40,
    "TB": 2**40
}

def parse_size(size):
    size = size.upper()
    print("size before: ", size)
    if not any(i in size for i in 'TGMKB'):
        if size.find("X"):
            return int(size, base=16)
        else:
            return int(size)
    print("Size: ", size)
    if not re.match(r' ', size):
        print("Inserting space")
        size = re.sub(r'([KMGT]B?)', r' \1', size)
    print (size.split())
    number, unit = [string.strip() for string in size.split()]

    return int(float(number)*units[unit])

def to_kilobytes(size):
    return str(int(size/1024)) + "K"

def main():

    config = None
    with open(args.input) as config_file:
        config = json.loads(config_file.read())

    if config is None:
        sys.exit(-1)

    current_path = os.path.dirname(os.path.abspath(__file__))
    template_loader = FileSystemLoader(current_path)
    env = Environment(loader = template_loader)
    t = env.get_template("linker_script.ld.template")

    sections = []
    for section_key in config["memory"]["sections"]:
        value = config["memory"]["sections"][section_key]
        # if parts exists then section is splitted
        subsections = []
        section_size = parse_size(value["size"])
        if "parts" in value:
            section_start_address = parse_size(value["address"])
            section_size = parse_size(value["size"])
            section_end_address = section_start_address + section_size
            print("start: ", hex(section_start_address))
            print("start: ", hex(section_end_address))
            additional_size = 0
            previous_address = section_end_address

            for part_value in value["parts"]:
                print ("part: ", part_value)
                subsection_size = parse_size(part_value["size"])
                subsection_address = previous_address - subsection_size
                additional_size = additional_size + subsection_size
                previous_address = subsection_address
                subsections.append({
                    "name": part_value["name"],
                    "access": value["access"],
                    "address": hex(subsection_address),
                    "length": to_kilobytes(subsection_size)
                })
                if additional_size > section_size:
                    raise RuntimeError("Subsections size higher that section (" + to_kilobytes(additional_size) + " > " + to_kilobytes(section_size) + ")")

            section_size = section_size - additional_size
        sections.append({
            "name": section_key,
            "access": value["access"],
            "address": value["address"],
            "length": to_kilobytes(section_size)
        })

        sections = sections + subsections

    rendered = t.render(
        sections = sections,
        heap = hex(parse_size(config["memory"]["heap"]["size"])),
        stack = hex(parse_size(config["memory"]["stack"]["size"]))
    )

    print(rendered)
    with open(args.output + "/linker_script.ld", "w") as output:
        output.write(rendered)
    with open(args.output + "/memory_config.cmake", "w") as output:
        for section in sections:
            print (section)
            output.write("set(" + section["name"] + "_" + "size" + " " + section["length"] + " CACHE INTERNAL \"\" FORCE)\n")

main()
