import unittest

import os
import sys
import subprocess
import shutil
import inspect
import json

class Test(unittest.TestCase):
    output_directory = "tests/tmp/generate_soc"

    @staticmethod
    def execute_script(out, soc, suppress = False):
        if os.path.exists(Test.output_directory + "/" + out):
            shutil.rmtree(Test.output_directory + "/" + out, ignore_errors=True)

        command = "python generate_soc.py -s " + soc + " -i tests/data/generate_soc/hal_configs" + " -o " + Test.output_directory + "/" + out
        print (command)
        out = subprocess.run(command, shell=True, capture_output=True)

        if out.stderr and not suppress:
            print("Command failed: ")
            print(out.stderr.decode("utf-8"))

        return out

    @staticmethod
    def execute_script_with_user_configs(out, soc, suppress = False):
        if os.path.exists(Test.output_directory + "/" + out):
            shutil.rmtree(Test.output_directory + "/" + out, ignore_errors=True)

        command = "python generate_soc.py -s " + soc + " -i tests/data/generate_soc/hal_configs " + " -u tests/data/generate_soc/user_config " + " -o " + Test.output_directory + "/" + out
        print (command)
        out = subprocess.run(command, shell=True, capture_output=True)

        if out.stderr and not suppress:
            print("Command failed: ")
            print(out.stderr.decode("utf-8"))

        return out

    @staticmethod
    def execute_script_with_override(out, soc, override, suppress = False):
        if os.path.exists(Test.output_directory + "/" + out):
            shutil.rmtree(Test.output_directory + "/" + out, ignore_errors=True)

        command = "python generate_soc.py -s " + soc + " -i tests/data/generate_soc/hal_configs " \
        + " -u tests/data/generate_soc/user_config " \
        + " -c tests/data/generate_soc/" + override \
        + " -o " + Test.output_directory + "/" + out
        print (command)
        out = subprocess.run(command, shell=True, capture_output=True)

        if out.stderr and not suppress:
            print("Command failed: ")
            print(out.stderr.decode("utf-8"))

        return out

    def test_generate_soc_from_hal_description(self):
        output_name = inspect.currentframe().f_code.co_name
        self.assertEqual(Test.execute_script(output_name, "device_a").returncode, 0)

        with open(self.output_directory + "/" + output_name + "/soc_config.json") as config_file:
            config = json.loads(config_file.read())
            self.assertDictEqual(config, {
                "memory": {
                    "flash": {
                        "address": "0x123",
                        "size": "10K"
                    },
                    "array": [1, 2, 3]
                }
            })
            with open(self.output_directory + "/" + output_name + "/soc_config.cmake") as config_file:
                cmake = config_file.read()
                self.assertNotEqual(-1, cmake.find("set (memory_flash_address 0x123)"))
                self.assertNotEqual(-1, cmake.find("set (memory_flash_size 10K)"))
                self.assertNotEqual(-1, cmake.find("set (memory_array [1, 2, 3])"))
                self.assertNotEqual(-1, cmake.find("set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS tests/data/generate_soc/hal_configs/device_a.json)"))
                self.assertNotEqual(-1, cmake.find("set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS tests/data/generate_soc/hal_configs/parent_a.json)"))


    def test_generate_soc_from_user_and_hal_configs(self):
        output_name = inspect.currentframe().f_code.co_name
        self.assertEqual(Test.execute_script_with_user_configs(output_name, "device_a").returncode, 0)

        with open(self.output_directory + "/" + output_name + "/soc_config.json") as config_file:
            config = json.loads(config_file.read())
            self.assertDictEqual(config, {
                "memory": {
                    "flash": {
                        "address": "0x123",
                        "size": "10K",
                        "offset": "100",
                        "type": "nand"
                    },
                    "array": [3, 4]

                },
                "ram": "true",
                "test": "a"
            })
            with open(self.output_directory + "/" + output_name + "/soc_config.cmake") as config_file:
                cmake = config_file.read()
                self.assertNotEqual(-1, cmake.find("set (memory_flash_address 0x123)"))
                self.assertNotEqual(-1, cmake.find("set (memory_flash_size 10K)"))
                self.assertNotEqual(-1, cmake.find("set (memory_flash_offset 100)"))
                self.assertNotEqual(-1, cmake.find("set (memory_flash_type nand)"))
                self.assertNotEqual(-1, cmake.find("set (memory_array [3, 4])"))
                self.assertNotEqual(-1, cmake.find("set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS tests/data/generate_soc/hal_configs/device_a.json)"))
                self.assertNotEqual(-1, cmake.find("set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS tests/data/generate_soc/user_config/device_a.json)"))
                self.assertNotEqual(-1, cmake.find("set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS tests/data/generate_soc/hal_configs/parent_a.json)"))
                self.assertNotEqual(-1, cmake.find("set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS tests/data/generate_soc/user_config/parent_a.json)"))


    def test_generate_soc_from_user(self):
        output_name = inspect.currentframe().f_code.co_name
        self.assertEqual(Test.execute_script_with_user_configs(output_name, "device_c").returncode, 0)

        with open(self.output_directory + "/" + output_name + "/soc_config.json") as config_file:
            config = json.loads(config_file.read())
            self.assertDictEqual(config, {
                "a": [1, 2, 3],
                "b": "b"
            })
        with open(self.output_directory + "/" + output_name + "/soc_config.cmake") as config_file:
            cmake = config_file.read()
            self.assertNotEqual(-1, cmake.find("set (a [1, 2, 3])"))
            self.assertNotEqual(-1, cmake.find("set (b b)"))
            self.assertNotEqual(-1, cmake.find("set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS tests/data/generate_soc/user_config/device_c.json)"))



    def test_generate_soc_and_override(self):
        output_name = inspect.currentframe().f_code.co_name
        self.assertEqual(Test.execute_script_with_override(output_name, "device_a", "override.json").returncode, 0)

        with open(self.output_directory + "/" + output_name + "/soc_config.json") as config_file:
            config = json.loads(config_file.read())
            self.assertDictEqual(config, {
                "memory": {
                    "flash": {
                        "address": "0x123",
                        "size": "10K",
                        "offset": "100",
                        "type": "nand"
                    },
                    "array": [3, 4]
                },
                "ram": "false",
                "test": "a"
            })


            with open(self.output_directory + "/" + output_name + "/soc_config.cmake") as config_file:
                cmake = config_file.read()
                self.assertNotEqual(-1, cmake.find("set (memory_flash_address 0x123)"))
                self.assertNotEqual(-1, cmake.find("set (memory_flash_size 10K)"))
                self.assertNotEqual(-1, cmake.find("set (memory_flash_offset 100)"))
                self.assertNotEqual(-1, cmake.find("set (memory_flash_type nand)"))
                self.assertNotEqual(-1, cmake.find("set (memory_array [3, 4])"))
                self.assertNotEqual(-1, cmake.find("set (ram false)"))
                self.assertNotEqual(-1, cmake.find("set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS tests/data/generate_soc/hal_configs/device_a.json)"))
                self.assertNotEqual(-1, cmake.find("set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS tests/data/generate_soc/user_config/device_a.json)"))
                self.assertNotEqual(-1, cmake.find("set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS tests/data/generate_soc/hal_configs/parent_a.json)"))
                self.assertNotEqual(-1, cmake.find("set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS tests/data/generate_soc/user_config/parent_a.json)"))
                self.assertNotEqual(-1, cmake.find("set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS tests/data/generate_soc/override.json)"))



if __name__ == '__main__':
    unittest.main()
