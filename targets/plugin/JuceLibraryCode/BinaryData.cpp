/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== README.md ==================
static const unsigned char temp_binary_data_0[] =
"#  README\n"
"\n"
"Zen delay FX module \n"
"\n"
"This project intented to run as DAW plugin or  STM32429 embedded.\n"
"\n"
"/targets/plugin/Source containts JUCE related code \n"
"/targets/BDSP/Source contains Black DSP board related code \n"
"\n"
"\n"
"\n"
"## Naming conventions\n"
" \n"
"- Variable and method names are written with camel-case, and always begin with a lower-case letter, e.g. myVariableName\n"
"- Class names are also written in camel-case, but always begin with a capital letter, e.g. MyClassName\n"
"- Hungarian notation is not allowed. \n"
"- private class/variables have trailing underscore eg MyPrivateVariable_ \n"
"- Avoid using underscores in variable or method names. Use underscores for long_and_otherwise_hard_readable_names or to separate physical dimension of variable (delayTime_ms vs delayTime_us)\n"
"- Leading underscores have a special status for use in standard library code, so to use them in use code looks quite jarring.\n"
"- If you really have to write a macro, it must be ALL_CAPS_WITH_UNDERSCORES. As they\xe2\x80\x99re the only symbols written in all-caps, this makes them easy to spot.\n"
"Since macros have no namespaces, their names must be guaranteed not to clash with macros or symbols used in other libraries or 3rd party code, so you should start them with something unique to your project. All the ZEN macros begin with ZEN_. \n"
"For enums, use camel-case with the same capitalisation that you'd use for a class and its member variables, e.g.\n"
"enum class MyEnum\n"
"{\n"
"    enumValue1 = 0,\n"
"    enumValue2 = 1\n"
"};\n"
"```\n";

const char* README_md = (const char*) temp_binary_data_0;

//================== LICENSE ==================
static const unsigned char temp_binary_data_1[] =
"MIT License\n"
"\n"
"Copyright (c) 2021 Tim Pechersky\n"
"\n"
"Permission is hereby granted, free of charge, to any person obtaining a copy\n"
"of this software and associated documentation files (the \"Software\"), to deal\n"
"in the Software without restriction, including without limitation the rights\n"
"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
"copies of the Software, and to permit persons to whom the Software is\n"
"furnished to do so, subject to the following conditions:\n"
"\n"
"The above copyright notice and this permission notice shall be included in all\n"
"copies or substantial portions of the Software.\n"
"\n"
"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
"SOFTWARE.\n";

const char* LICENSE = (const char*) temp_binary_data_1;

//================== README.md ==================
static const unsigned char temp_binary_data_2[] =
"#  README\n"
"\n"
"Zen DSP lib\n"
"\n"
"This is a lightweight audio processing library intended to run on embedded device and made in a way so it is compatible for incorporating in to Plugin/Standalone desktop/mobile projects as well \n"
"\n"
"\n"
"\n"
"## Naming conventions\n"
"\n"
"- Variable and method names are written with camel-case, and always begin with a lower-case letter, e.g. myVariableName\n"
"- Class names are also written in camel-case, but always begin with a capital letter, e.g. MyClassName\n"
"- Hungarian notation is not allowed. \n"
"- private class/variables have trailing underscore eg MyPrivateVariable_ \n"
"- Avoid using underscores in variable or method names. Use underscores for long_and_otherwise_hard_readable_names or to separate physical dimension of variable (delayTime_ms vs delayTime_us)\n"
"- Leading underscores have a special status for use in standard library code, so to use them in use code looks quite jarring.\n"
"- If you really have to write a macro, it must be ALL_CAPS_WITH_UNDERSCORES. As they\xe2\x80\x99re the only symbols written in all-caps, this makes them easy to spot.\n"
"Since macros have no namespaces, their names must be guaranteed not to clash with macros or symbols used in other libraries or 3rd party code, so you should start them with something unique to your project. All the ZEN macros begin with ZEN_. \n"
"For enums, use camel-case with the same capitalisation that you'd use for a class and its member variables, e.g.\n"
"```\n"
"enum class MyEnum\n"
"{\n"
"enumValue1 = 0,\n"
"enumValue2 = 1\n"
"};\n"
"```\n";

const char* README_md2 = (const char*) temp_binary_data_2;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x64791dc8:  numBytes = 1472; return README_md;
        case 0x34bc1021:  numBytes = 1070; return LICENSE;
        case 0x2aaa9b6a:  numBytes = 1474; return README_md2;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "README_md",
    "LICENSE",
    "README_md2"
};

const char* originalFilenames[] =
{
    "README.md",
    "LICENSE",
    "README.md"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
    {
        if (namedResourceList[i] == resourceNameUTF8)
            return originalFilenames[i];
    }

    return nullptr;
}

}
