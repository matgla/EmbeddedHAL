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

import re

# based on https://stackoverflow.com/a/60708339
units = {
    "B": 1,
    "K": 2**10,
    "KB": 2**10,
    "M": 2**20,
    "MB": 2**20,
    "G": 2**30,
    "GB": 2**30,
    "T": 2**40,
    "TB": 2**40
}

def parse_size(size):
    size = size.upper()
    if not any(i in size for i in 'TGMKB'):
        if size.find("X") != -1:
            return int(size, base=16)
        else:
            return int(size)
    if not re.match(r' ', size):
        size = re.sub(r'([KMGTB]B?)', r' \1', size)
    number, unit = [string.strip() for string in size.split()]

    return int(float(number)*units[unit])

def to_kilobytes(size):
    return str(int(size/1024)) + "K"
