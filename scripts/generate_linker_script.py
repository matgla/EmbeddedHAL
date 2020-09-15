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
from utils.human_readable_size_parser import parse_size, to_kilobytes
from utils.printers import print_error

LINKER_SCRIPT_TEMPLATE_FILENAME = "linker_script.ld.template"

def get_template():
    current_path = os.path.dirname(os.path.abspath(__file__))
    template_loader = FileSystemLoader(current_path)
    env = Environment(loader = template_loader)
    return env.get_template(LINKER_SCRIPT_TEMPLATE_FILENAME)

def fetch_config(input_file):
    with open(input_file) as config_file:
        return json.loads(config_file.read())

class ConfigValidator:
    def __init__(self, path):
        self.path = path

    def check(self, node, key):
        if not key in node:
            error = "Failure while processing {path}\n {key} not found under: {obj}.".format(path=self.path, key=key, obj=node)
            raise RuntimeError(error)

parser = argparse.ArgumentParser(description = "Linker script generator for HAL")
parser.add_argument("-i", "--input", dest="input", action="store", help="Path to configuration file file", required=True)
parser.add_argument("-o", "--output", dest="output", action="store", help="Path to output file", required=True)
parser.add_argument("-s", "--sections", dest="options", action="store", help="Additional sections in format: <name>:<access(r/w/x)>:address:length, separated by comma (',')")

args, rest = parser.parse_known_args()

def get_subsections(value, validator):
    section_start_address = parse_size(value["address"])
    section_size = parse_size(value["size"])
    section_end_address = section_start_address + section_size
    additional_size = 0
    previous_address = section_end_address
    subsections = []
    for part_value in value["subsections"]:
        validator.check(part_value, "name")
        validator.check(part_value, "size")

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
    return subsections, additional_size

def get_sections(config, validator):
    sections = []
    for section_key in config["sections"]:
        value = config["sections"][section_key]
        validator.check(value, "size")
        validator.check(value, "address")
        validator.check(value, "access")
        # if parts exists then section is splitted
        subsections = []
        section_size = parse_size(value["size"])
        if "subsections" in value:
            subsections, subsection_size = get_subsections(value, validator)
            section_size = section_size - subsection_size

        sections.append({
            "name": section_key,
            "access": value["access"],
            "address": value["address"],
            "length": to_kilobytes(section_size)
        })

        sections = sections + subsections
    return sections

def main():
    config = fetch_config(args.input)
    validator = ConfigValidator(args.input)

    validator.check(config, "memory")
    validator.check(config["memory"], "sections")

    sections = get_sections(config["memory"], validator)

    memory = config["memory"]
    validator.check(memory, "heap")
    validator.check(memory["heap"], "size")
    validator.check(memory, "stack")
    validator.check(memory["stack"], "size")
    heap = hex(parse_size(config["memory"]["heap"]["size"]))
    stack = hex(parse_size(config["memory"]["stack"]["size"]))

    rendered = get_template().render(
        sections = sections,
        heap = heap,
        stack = stack
    )

    if not os.path.exists(args.output):
        os.makedirs(args.output)

    with open(args.output + "/linker_script.ld", "w") as output:
        output.write(rendered)
    with open(args.output + "/memory_config.cmake", "w") as output:
        for section in sections:
            output.write("set(" + section["name"] + "_" + "size" + " " + section["length"] + " CACHE INTERNAL \"\" FORCE)\n")

if __name__ == '__main__':
    main()
