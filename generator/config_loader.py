import json


def load_config(filename):
    with open(filename) as file:
        return json.load(file)
