from .gpio_generator import GpioGenerator


class Generator:
    def __init__(self):
        self.config = {}
        self.output = ''

    def set_config(self, config):
        self.config = config

    def set_output_dir(self, output):
        self.output = output

    def generate(self):
        print("Generating: GPIO...")

        gpioGenerator = GpioGenerator(self.config["Port"], self.output)
        gpioGenerator.generate()
