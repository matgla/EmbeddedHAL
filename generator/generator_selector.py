def select_generator(arch, lib):
    if arch == "STM32F1":
        if lib == "STD_PERIPH":
            from generators.arm.stm32f1.std_periph.code_generator import Generator
            return Generator()
