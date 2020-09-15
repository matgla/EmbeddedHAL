import unittest

import os
import sys
import subprocess
import shutil
import inspect
from jinja2 import Template, Environment, FileSystemLoader
import difflib

class Test(unittest.TestCase):
    output_directory = "tests/tmp/linker_script_tests"

    @staticmethod
    def execute_script(input, out, suppress = False):
        if os.path.exists(Test.output_directory + "/" + out):
            shutil.rmtree(Test.output_directory + "/" + out, ignore_errors=True)

        out = subprocess.run(" python generate_linker_script.py -i " + input + " -o " + Test.output_directory + "/" + out, shell=True, capture_output=True)

        if out.stderr and not suppress:
            print("Command failed: ")
            print(out.stderr.decode("utf-8"))

        return out

    @staticmethod
    def compare_scripts(rendered, output_name):
        passed = False
        with open(Test.output_directory + "/" + output_name + "/linker_script.ld") as file:
            passed = True
            for line in difflib.unified_diff(rendered.strip().splitlines(), file.read().splitlines(), fromfile="linker_script.ld", tofile='test_file', lineterm=''):
                print(line)
                passed = False
        return passed


    def get_template(self):
        current_path = os.path.dirname(os.path.abspath(__file__))
        template_loader = FileSystemLoader(current_path + "/..")
        env = Environment(loader = template_loader)
        return env.get_template("linker_script.ld.template")


    def test_return_fail_exit_code_when_lack_of_data(self):
        self.assertNotEqual(Test.execute_script("tests/data/linker_script/empty.json", inspect.currentframe().f_code.co_name, True).returncode, 0)
        pass

    def test_generate_linker_script(self):
        output_name = inspect.currentframe().f_code.co_name
        self.assertEqual(Test.execute_script("tests/data/linker_script/memory_config.json", output_name).returncode, 0)

        template = self.get_template()
        sections = []
        sections.append({
            "name": "flash",
            "access": "rx",
            "address": "0x08000000",
            "length": "10K"
        })

        sections.append({
            "name": "ram",
            "access": "rwx",
            "address": "0x20000000",
            "length": "20K"
        })

        heap = "0x1400"
        stack = "0x1c00"
        rendered = template.render(
            sections = sections,
            heap = heap,
            stack = stack
        )

        self.assertTrue(Test.compare_scripts(rendered, output_name))

    def test_generate_linker_script_with_subsections(self):
        output_name = inspect.currentframe().f_code.co_name
        self.assertEqual(Test.execute_script("tests/data/linker_script/memory_config_with_subsection.json", output_name).returncode, 0)

        template = self.get_template()
        sections = []
        sections.append({
            "name": "flash",
            "access": "rx",
            "address": "0x08000000",
            "length": "3K" # subsections decreases section size
        })

        sections.append({
            "name": "fs_flash",
            "access": "rx",
            "address": "0x8001400",
            "length": "5K"
        })

        sections.append({
            "name": "kernel_fs",
            "access": "rx",
            "address": "0x8000c00",
            "length": "2K"
        })

        sections.append({
            "name": "ram",
            "access": "rwx",
            "address": "0x20000000",
            "length": "17K"
        })

        sections.append({
            "name": "ram_sub_1",
            "access": "rwx",
            "address": "0x20004c00",
            "length": "1K"
        })

        sections.append({
            "name": "ram_sub_2",
            "access": "rwx",
            "address": "0x20004400",
            "length": "2K"
    })


        heap = "0x1400"
        stack = "0x1c00"
        rendered = template.render(
            sections = sections,
            heap = heap,
            stack = stack
        )

        self.assertTrue(Test.compare_scripts(rendered, output_name))

    def get_regex(self, path, key):
        return r'Failure while processing ' + path + '.*\n ' + key + ' not found'

    def check_lack_of(self, filepath, output_name, key):
        out = Test.execute_script(filepath, output_name, True)
        self.assertNotEqual(out.returncode, 0)
        self.assertRegex(out.stderr.decode('utf-8'), self.get_regex(filepath, key))


    def test_fail_when_lack_of_sections(self):
        output_name = inspect.currentframe().f_code.co_name
        filepath = "tests/data/linker_script/memory_config_without_sections.json"
        self.check_lack_of(filepath, output_name, "sections")

    def test_fail_when_lack_of_address(self):
        output_name = inspect.currentframe().f_code.co_name
        filepath = "tests/data/linker_script/memory_config_without_address.json"
        self.check_lack_of(filepath, output_name, "address")

    def test_fail_when_lack_of_access(self):
        output_name = inspect.currentframe().f_code.co_name
        filepath = "tests/data/linker_script/memory_config_without_access.json"
        self.check_lack_of(filepath, output_name, "access")

    def test_fail_when_lack_of_size(self):
        output_name = inspect.currentframe().f_code.co_name
        filepath = "tests/data/linker_script/memory_config_without_size.json"
        self.check_lack_of(filepath, output_name, "size")

    def test_fail_when_lack_of_subsection_name(self):
        output_name = inspect.currentframe().f_code.co_name
        filepath = "tests/data/linker_script/memory_config_without_subsection_name.json"
        self.check_lack_of(filepath, output_name, "name")

    def test_fail_when_lack_of_subsection_size(self):
        output_name = inspect.currentframe().f_code.co_name
        filepath = "tests/data/linker_script/memory_config_without_subsection_size.json"
        self.check_lack_of(filepath, output_name, "size")

    def test_fail_when_lack_of_heap_size(self):
        output_name = inspect.currentframe().f_code.co_name
        filepath = "tests/data/linker_script/memory_config_without_heap.json"
        self.check_lack_of(filepath, output_name, "heap")

    def test_fail_when_lack_of_stack_size(self):
        output_name = inspect.currentframe().f_code.co_name
        filepath = "tests/data/linker_script/memory_config_without_stack.json"
        self.check_lack_of(filepath, output_name, "stack")

    def test_fail_when_subsection_larger_than_section(self):
        output_name = inspect.currentframe().f_code.co_name
        filepath = "tests/data/linker_script/memory_config_with_to_huge_subsection.json"
        out = Test.execute_script(filepath, output_name, True)
        self.assertNotEqual(out.returncode, 0)
        self.assertRegex(out.stderr.decode('utf-8'), r'Subsections size higher that section')





if __name__ == '__main__':
    unittest.main()
