def generated_header():
    return "/* THIS FILE WAS GENERATED! */\n"


def newline():
    return "\n"


def system_include(name):
    return "#include <" + name + ">\n"


def user_include(name):
    return "#include \"" + name + "\"\n"


def indent():
    return "  "


def struct(name):
    return "struct " + name + "\n"


def enum(name):
    return "enum " + name + "\n"
