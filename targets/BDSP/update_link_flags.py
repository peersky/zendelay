# Custom settings, as referred to as "extra_script" in platformio.ini
#
# See http://docs.platformio.org/en/latest/projectconf.html#extra-script

Import("env")


env.Append(LINKFLAGS=["-mthumb", "-mfloat-abi=hard", "-mfpu=fpv4-sp-d16"])
