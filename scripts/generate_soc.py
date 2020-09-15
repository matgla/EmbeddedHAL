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

parser = argparse.ArgumentParser(description = "CMake configuration generator based on KConfig")
parser.add_argument("-s", "--soc", dest="soc", action="store", help="SOC name", required=True)
parser.add_argument("-i", "--input", dest="input_directory", action="store", help="Path to input directory", required=True)
parser.add_argument("-o", "--output", dest="output_directory", action="store", help="Path to output directory", required=True)
parser.add_argument("-u", "--user_directory", dest="user_directory", action="store", help="Path to user provided configs")
parser.add_argument("-c", "--user_configs", dest="user_configs", action="store", help="Path to additional user provided config.json")

args, rest = parser.parse_known_args()

processed_files = []

def get_all_configs(soc, input_directory, user_directory):
    next_config = soc
    configs = []

    soc_path = None
    base_config = None

    for path in Path(args.input_directory).rglob(soc + ".json"):
        soc_path = path
        processed_files.append(soc_path)
        break

    if not soc_path is None:
        with open(soc_path) as config_file:
            base_config = json.loads(config_file.read())

    soc_path = None
    if not user_directory is None:
        print ("Searching in " + args.user_directory + " :" + soc + ".json")
        for path in Path(args.user_directory).rglob(soc + ".json"):
            soc_path = path
            processed_files.append(soc_path)
            break

    print ("User path: ", soc_path)
    if not soc_path is None:
        with open(soc_path) as config_file:
            if base_config is None:
                base_config = json.loads(config_file.read())
            else:
                print("Merge: ")
                merge(base_config, json.loads(config_file.read()))

    if base_config is None:
        sys.exit(-1)

    print ("append base: ", base_config)
    configs.append(base_config)
    while not next_config is None:
        if "parent" in configs[-1]:
            next_config = None
            new_config = None
            for path in Path(input_directory).rglob(configs[-1]["parent"] + ".json"):
                next_config = path
                processed_files.append(next_config)
                break

            if not next_config is None:
                with open(next_config) as config_file:
                    new_config = json.loads(config_file.read())

            if not user_directory is None:
                for path in Path(user_directory).rglob(configs[-1]["parent"] + ".json"):
                    next_config = path
                    processed_files.append(next_config)
                    break

                if not next_config is None:
                    with open(next_config) as config_file:
                        part = json.loads(config_file.read())
                        if new_config is None:
                            new_config = part
                        else:
                            print ("Merge 2")
                            print ("1: ", new_config)
                            print ("2: ", part)
                            new_config = merge(new_config, part)

            if new_config == None:
                print("Cannot find file: " + input_directory + "/../" + configs[-1]["parent"] + ".json")
                sys.exit(-1)
            print("Append: ", new_config)
            if "parent" in new_config:
                del new_config["parent"]
            print("Appenfing: ", new_config)
            configs.append(new_config)
        else:
            next_config = None

    return configs

def merge(old, new):
    for k in new:
        if k in old:
            print (old[k])
            if isinstance(old[k], dict):
                print (old[k], "instance")
                merge(old[k], new[k])
            else:
                print (old[k], new[k])

                old[k] = new[k]
        else:
            old[k] = new[k]

    return old

def write_node(node, prefix, file):
    print("node: ", node)
    for key in node:
        if prefix == "":
            pref = key
        else:
            pref = prefix + "_" + key
        print ("key: ", key)
        if not isinstance(node[key], dict):
            file.write("set (" + pref + " " + str(node[key]) + ")\n")
        else:
            write_node(node[key], pref, file)

def main():
    if not os.path.exists(args.output_directory):
        os.makedirs(args.output_directory)

    configs = get_all_configs(args.soc, args.input_directory, args.user_directory)
    config = {}
    for c in range(0, len(configs)):
        print ("merge: ", config)
        print ("with: ", c)
        merge(config, configs[-c - 1])

    if not args.user_configs is None:
        for config_path in args.user_configs.split(';'):
            with open(config_path) as cfg:
                processed_files.append(config_path)
                user_config = json.loads(cfg.read())
                print("User cfg: ", user_config)
                merge(config, user_config)

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
