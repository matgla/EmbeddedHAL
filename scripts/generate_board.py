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
import sys
import os
import json
import collections
from jinja2 import Template, Environment, FileSystemLoader
from pathlib import Path
from utils.path import make_dir

parser = argparse.ArgumentParser(description = "Board generator from JSON")
parser.add_argument("-i", "--input", dest="input", action="store", help="Path to input file", required=True)
parser.add_argument("-c", "--user_config", dest="user_config", action="store", help="Path to input user configs", required=True)
parser.add_argument("-o", "--output", dest="output_directory", action="store", help="Path to output directory", required=True)

args, rest = parser.parse_known_args()

BOARD_CMAKE_TEMPLATE = "board_cmake.template"

def get_template_path():
    current_path = os.path.dirname(os.path.abspath(__file__))
    return current_path + "/" + BOARD_CMAKE_TEMPLATE

def get_template():
    current_path = os.path.dirname(os.path.abspath(__file__))
    template_loader = FileSystemLoader(current_path)
    env = Environment(loader = template_loader)
    return env.get_template(BOARD_CMAKE_TEMPLATE)

def main():
    with open(args.input) as config_file:
        config = json.loads(config_file.read())

    if not os.path.exists(args.output_directory):
        os.makedirs(args.output_directory)

    if not "libraries" in config: 
        config["libraries"] = {} 
    if not "public" in config["libraries"]:
        config["libraries"]["public"] = [] 
    if not "private" in config["libraries"]:
        config["libraries"]["private"] = [] 
    if not "interface" in config["libraries"]:
        config["libraries"]["interface"] = []

    board_path = Path(args.input)
    template = get_template()
    rendered = template.render(
        path = get_template_path(),
        board = board_path.name.split('.')[0],
        board_path = board_path.parent,
        arch = config["info"]["arch"].lower(),
        soc = config["info"]["mcu"].lower(),
        user_board_config_path = args.user_config,
        public_dependencies = config["libraries"]["public"],
        private_dependencies = config["libraries"]["private"],
        interface_libraries = config["libraries"]["interface"]
    )
    with open(args.output_directory + "/board.cmake", "w") as cmake:
        cmake.write (rendered)

if __name__ == '__main__':
    main()
