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

from pathlib import Path
from utils.path import make_dir

parser = argparse.ArgumentParser(description = "CMake configuration generator based on KConfig")
parser.add_argument("-b", "--board", dest="board", action="store", help="Path to board config", required=True)
parser.add_argument("-i", "--input", dest="input_directory", action="store", help="Path to input directory", required=True)
parser.add_argument("-o", "--output", dest="output_directory", action="store", help="Path to output directory", required=True)
parser.add_argument("-u", "--user_directory", dest="user_directory", action="store", help="Path to user provided configs")
parser.add_argument("-c", "--user_configs", dest="user_configs", action="store", help="Path to additional user provided config.json")

args, rest = parser.parse_known_args()

processed_files = []

def find_soc_in(soc, path):
    if path is None:
        return None
    for p in Path(path).rglob(soc + ".json"):
        processed_files.append(p)
        return p
    return None

def load_config_from(path):
    if not path is None:
        with open(path) as config_file:
            return json.loads(config_file.read())
    return None

def get_all_configs(soc, input_directory, user_directory):
    next_config = soc
    configs = []

    soc_path = find_soc_in(soc, args.input_directory)
    base_config = load_config_from(soc_path)

    user_soc_path = find_soc_in(soc, args.user_directory)
    user_config = load_config_from(user_soc_path)
    if not user_config is None:
        base_config = merge(base_config, user_config)
    if base_config is None:
        print ("Base config is empty")
        print (soc + " not found under: ")
        print ("    " + args.input_directory)
        print ("    " + args.user_directory)
        sys.exit(-1)

    configs.append(base_config)
    while not next_config is None:
        if "parent" in configs[-1]:
            next_config = find_soc_in(configs[-1]["parent"], input_directory)
            new_config = load_config_from(next_config)

            next_user_config_path = find_soc_in(configs[-1]["parent"], user_directory)
            next_user_config = load_config_from(next_user_config_path)
            new_config = merge(new_config, next_user_config)
            if new_config == None:
                print("Cannot find file: " + input_directory + "/../" + configs[-1]["parent"] + ".json")
                sys.exit(-1)
            if "parent" in new_config:
                del new_config["parent"]
            configs.append(new_config)
        else:
            next_config = None

    return configs

def merge(old, new):
    if old == None:
        return new
    if new == None:
        return old

    for k in new:
        if k in old:
            print (old[k])
            if isinstance(old[k], dict):
                print (old[k], "instance")
                merge(old[k], new[k])
            else:
                print ("update: ", old[k], new[k])

                old[k] = new[k]
        else:
            print ("update: ", new[k])

            old[k] = new[k]

    return old

def write_node(node, prefix, file):
    for key in node:
        if prefix == "":
            pref = key
        else:
            pref = prefix + "_" + key
        if not isinstance(node[key], dict):
            file.write("set (" + pref + " " + str(node[key]) + ")\n")
        else:
            write_node(node[key], pref, file)

def patch_with_config(config, user_configs):
    for config_path in user_configs.split(';'):
        with open(config_path) as cfg:
            processed_files.append(config_path)
            user_config = json.loads(cfg.read())
            merge(config, user_config)
    return config

def merge_configs(configs):
    config = {}
    for c in range(0, len(configs)):
        config = merge(config, configs[-c - 1])
    return config

def patch_with_other_config(config, other_config_path):
    if not other_config_path is None:
        config = patch_with_config(config, other_config_path)
    return config

def main():
    make_dir(args.output_directory)
    with open(args.board) as board_file:
        board = json.loads(board_file.read())
    configs = get_all_configs(board["info"]["mcu"], args.input_directory, args.user_directory)
    config = merge_configs(configs)
    config = merge(board, config)
    config = patch_with_other_config(config, args.user_configs)
    if "parent" in config:
        del config["parent"]

    with open(args.output_directory + "/soc_config.json", "w") as file:
        json.dump(config, file)

    cmake_soc_file = args.output_directory + "/soc_config.cmake"
    with open(cmake_soc_file, "w") as soc_config:
        write_node(config, "", soc_config)
        for file in processed_files:
            soc_config.write("set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS " + str(file) + ")\n")

if __name__ == '__main__':
    main()
