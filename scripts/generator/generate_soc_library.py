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

has_gpio = False 
has_usart = False 
has_i2c = False

def generate_gpio(config):
    ports = config["hal"]["gpio"]["ports"]

    pins = []
    for port in ports:
        port_name = port.upper()
        port = ports[port]
        pin = {
            "port_name": port_name,
        }


        if "rcc" in port:
            pin["rcc_base"] = port["rcc"]

        if isinstance(port["pins"], str):
            ranges = port["pins"].split('-')
            min = int(ranges[0])
            max = int(ranges[1]) + 1
            pin["numbers"] = range(min, max)
        else:
            pin["numbers"] = port["pins"]
        pins.append(pin)

    rendered = get_template(config["info"]["arch"].lower(), "gpio.hpp").render(
        arch = config["info"]["arch"].lower(),
        vendor = config["info"]["vendor"].lower(),
        family = config["info"]["family"].lower(),
        pins = pins,
        gpio_class = config["hal"]["gpio"]["class"]
    )

    gpio_file = args.output + "/" + config["info"]["mcu"] + "_gpio.hpp"
    with open(gpio_file, "w") as gpio_out:
        gpio_out.write(rendered)

    rendered = get_template(config["info"]["arch"].lower(), "gpio.cpp").render(
        arch = config["info"]["arch"].lower(),
        vendor = config["info"]["vendor"].lower(),
        family = config["info"]["family"].lower(),
        pins = pins,
        soc = config["info"]["mcu"].lower(),
        gpio_class = config["hal"]["gpio"]["class"]
    )

    gpio_file = args.output + "/" + config["info"]["mcu"] + "_gpio.cpp"
    with open(gpio_file, "w") as gpio_out:
        gpio_out.write(rendered)

def generate_usart(config):
    usarts_config = config["hal"]["usart"]["devices"]

    usarts = []

    for usart in usarts_config:
        if not "type" in usarts_config[usart]:
            usarts_config[usart]["type"] = None
        usart_config = {
            "number": usart,
            "tx_pin": usarts_config[usart]["tx"],
            "rx_pin": usarts_config[usart]["rx"],
            "type": usarts_config[usart]["type"]
        }

        usarts.append(usart_config)

    rendered = get_template(config["info"]["arch"].lower(), "usart.hpp").render(
        arch = config["info"]["arch"].lower(),
        vendor = config["info"]["vendor"].lower(),
        family = config["info"]["family"].lower(),
        usart_class = config["hal"]["usart"]["class"],
        soc = config["info"]["mcu"].lower(),
        usarts = usarts
    )

    usart_file = args.output + "/" + config["info"]["mcu"] + "_usart.hpp"
    with open(usart_file, "w") as usart_file:
        usart_file.write(rendered)

    rendered = get_template(config["info"]["arch"].lower(), "usart.cpp").render(
        arch = config["info"]["arch"].lower(),
        vendor = config["info"]["vendor"].lower(),
        family = config["info"]["family"].lower(),
        usart_class = config["hal"]["usart"]["class"],
        soc = config["info"]["mcu"].lower(),
        usarts = usarts
    )

    usart_file = args.output + "/" + config["info"]["mcu"] + "_usart.cpp"
    with open(usart_file, "w") as usart_file:
        usart_file.write(rendered)

def generate_i2c(config):
    template = get_template(config["info"]["arch"].lower(), "i2c")

    i2cs_config = config["hal"]["i2c"]["devices"]

    i2cs = []

    for i2c in i2cs_config:

        i2c_config = {
            "number": i2c,
            "scl": i2cs_config[i2c]["scl"],
            "sda": i2cs_config[i2c]["sda"]
        }

        i2cs.append(i2c_config)

    rendered = template.render(
        arch = config["info"]["arch"].lower(),
        vendor = config["info"]["vendor"].lower(),
        family = config["info"]["family"].lower(),
        soc = config["info"]["mcu"].lower(),
        i2cs = i2cs
    )

    i2c_file = args.output + "/" + config["info"]["mcu"] + "_i2c.hpp"
    with open(i2c_file, "w") as i2c_file:
        i2c_file.write(rendered)

    i2c_file = args.output + "/" + config["info"]["mcu"] + "_i2c.cpp"
    with open(i2c_file, "w") as i2c_file:
        i2c_file.write("")

def generate_cmake(config):
    template = get_template(config["info"]["arch"].lower(), "cmake")

    print ("HAS GPIO: ", has_gpio)
    peripherals = [] 
    if has_gpio:
        peripherals.append("gpio") 
    if has_usart: 
        peripherals.append("usart") 
    if has_i2c:
        peripherals.append("i2c")
   
    print ("Peripherals to generate: ", peripherals)
    rendered = template.render(
        arch = config["info"]["arch"].lower(),
        vendor = config["info"]["vendor"].lower(),
        family = config["info"]["family"].lower(),
        soc = config["info"]["mcu"].lower(),
        peripherals = peripherals,
        source_path = args.output,
        definitions = config["definitions"]
    )

    cmake_file = args.output + "/soc_library.cmake"
    with open(cmake_file, "w") as cmake_file:
        cmake_file.write(rendered)

def set_as_none(obj, name):
    obj[name] = None

def main():
    with open(args.input) as config_file:
        config = json.loads(config_file.read())

    if not os.path.exists(args.output):
        os.makedirs(args.output)


    if "gpio" in config["hal"]:
        if not "class" in config["hal"]["gpio"]:
            set_as_none(config["hal"]["gpio"], "class")
        generate_gpio(config)
        global has_gpio
        has_gpio = True

    if "usart" in config["hal"]:
        if not "class" in config["hal"]["usart"]:
            set_as_none(config["hal"]["usart"], "class")
        generate_usart(config)
        global has_usart
        has_usart = True 
    
    if "i2c" in config["hal"]:
        if not "class" in config["hal"]["i2c"]:
            set_as_none(config["hal"]["i2c"], "class")

        generate_i2c(config)
        global has_i2c
        has_i2c = True 

    generate_cmake(config)

if __name__ == '__main__':
    main()
