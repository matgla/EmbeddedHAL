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

def get_template(arch, periph):
    current_path = os.path.dirname(os.path.abspath(__file__))
    template_loader = FileSystemLoader(current_path + "/templates/" + arch)
    env = Environment(loader = template_loader)
    return env.get_template(periph + ".template")

parser = argparse.ArgumentParser(description = "SOC hal library generator for HAL")
parser.add_argument("-i", "--input", dest="input", action="store", help="Path to configuration file", required=True)
parser.add_argument("-o", "--output", dest="output", action="store", help="Path to output directory", required=True)

args, rest = parser.parse_known_args()

def main():
    with open(args.input) as config_file:
        config = json.loads(config_file.read())
    print ("GENERATE: ", config)
    template = get_template(config["info"]["arch"].lower(), "gpio")

    ports = config["hal"]["gpio"]["ports"]

    pins = []
    for port in ports:
        print (ports[port])
        port_name = port.upper()
        port = ports[port]
        pin = {
            "port_name": port_name,
            "rcc_base": port["rcc"]
        }

        if isinstance(port["pins"], str):
            ranges = port["pins"].split('-')
            min = int(ranges[0])
            max = int(ranges[1]) + 1
            pin["numbers"] = range(min, max)
        else:
            print ("p: ", port)
            pin["numbers"] = port["pins"]
        pins.append(pin)

    print (pins)
    rendered = template.render(
        arch = config["info"]["arch"].lower(),
        vendor = config["info"]["vendor"].lower(),
        family = config["info"]["family"].lower(),
        pins = pins
    )
    print(rendered)

    if not os.path.exists(args.output):
        os.makedirs(args.output)

    gpio_file = args.output + "/" + config["info"]["mcu"] + "_gpio.hpp"
    with open(gpio_file, "w") as gpio_out:
        gpio_out.write(rendered)

if __name__ == '__main__':
    main()
