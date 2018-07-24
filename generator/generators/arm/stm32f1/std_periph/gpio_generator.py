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
            f.write("namespace hal\n{\n")
            f.write("namespace gpio\n{\n")

            self.generate_port(f)

            f.write("} // namespace gpio\n")
            f.write("} // namespace hal\n")

    def generate_header(self, f):
        f.write(generated_header())
        f.write(user_include("hal/gpio/gpio.hpp"))
        f.write(user_include("arm/stm32/stm32f10x/gpio/stm32f10x_gpio.hpp"))
        f.write(newline())

    def generate_port(self, f):
        for port_name in self.config:
            for pin in self.config[port_name]:
                f.write("    using P" + port_name + str(pin) + " = Gpio<hal::stm32f10x::gpio::StmGpio<GPIO" +
                        port_name + "_BASE, GPIO_Pin_" + str(pin) + ">>;")
                f.write(newline())
