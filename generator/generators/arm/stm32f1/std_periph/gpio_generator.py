import os
import errno

from generators.common.cpp_snippets import *
from generators.arm.stm32f1.std_periph.gpio_mapper import *


class GpioGenerator:
    def __init__(self, config, output):
        self.config = config
        self.output = output + "/pinout.hpp"

    def create_file(self):
        if not os.path.exists(os.path.dirname(self.output)):
            try:
                os.makedirs(os.path.dirname(self.output))
            except OSError as error:
                if error.errno != errno.EEXIST:
                    raise

    def generate(self):
        self.create_file()

        with open(self.output, "w") as f:
            self.generate_header(f)
            self.generate_port(f)

    def generate_header(self, f):
        f.write(generated_header())
        f.write(system_include("stm32f10x.h"))
        f.write(newline())

    def generate_port(self, f):
        f.write(struct("Port"))
        f.write("{\n")
        f.write(indent() + enum(""))
        f.write(indent() + "{\n")
        port_names = list(self.config.keys())
        for port in port_names[:-1]:
            f.write(indent() * 2 + port + " = " +
                    port_to_gpio(port) + ",\n")
        f.write(indent() * 2 + port_names[-1] + " = " +
                port_to_gpio(port_names[-1]) + "\n")
        f.write(indent() + "};\n")
        f.write(newline())
        for port_name in self.config:
            f.write(indent() + struct(port_name))
            f.write(indent() + "{\n")
            f.write(indent() * 2 + "enum\n")
            f.write(indent() * 2 + "{\n")
            for pin in self.config[port_name][:-1]:
                f.write(indent() * 3 + "P" + str(pin) + " = " +
                        pin_to_gpio_pin(pin) + ",\n")
            f.write(indent() * 3 + "P" + str(self.config[port_name][-1]) + " = " +
                    pin_to_gpio_pin(self.config[port_name][-1]) + "\n")
            f.write(indent() * 2 + "} \n")
            f.write(indent() + "};\n")
            f.write("\n")

        f.write("};\n")
        f.write("\n")
