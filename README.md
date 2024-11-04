# BaseConv | Numeral Systems Converter
Simple CLI toolkit for converting numbers between any of the most popular numeral systems (**BIN, OCT, DEC, HEX**) 

## Requirements
General requirements:
* The main functionality that this code should deliver is to convert numbers between any of four selected systems (binary, octal, decimal, hexadecimal)
* The base/numeral system of the input sould be detected automatically
* The functionality should be encapsulated in a single class called BaseConv
* Both input and output from the BaseConv class should be in a form of a string
* An additional class called BaseConvCLI should handle the interaction with the user through the Command Prompt
* Any data exchange between both classes should be carried out via a dedicated structure
* The number under conversion should be of uint64_t type
* The BaseConv class should use as many built-in functions (e.g. strtol, bitwidth etc.) as possible
* The action undertaken by the BaseConv class should be triggered from the switch control statement (based on enum class targetBase)

### Typical use case:
>A user interacts with the app via the Command Prompt. An execution with no input parameters results in printing the welcome note and a very brief description of the app. In addition -h or --help argument can be used to display help/manual of the app. For the main functionality the user have to execute the app with the first argument being the number to be converted, and the second one being the target numerical system (e.g. BaseConv.exe 0x4f00 BIN) - the app should return the converted number to the console and ask if further conversion is needed.

## ToDo:
- Finish the BaseConv class
- Add BaseConvCLI class
- Split the project into separate files and configure CMake & build automation
- CMake Configuration and build automation
- Prepare GIT repo and send to Michał when classes are ready
- Review used formatting convention (and naming convention)
- Add proper error handling and param validation (as described in the response)
- Review the commenting and its completeness
- Add unit tests (using C++ built-in library)

## Done:
- Installed gcc, g++ (14.1) and gdb (from MSYS2)
- Installed CMake in VSCode
- Started writing the app

### Additional notes:
Idea jest taka, że gdy dane są przekazywane przez klasę interfejsu do klasy core (poprzez struct), to najpierw do głównej metody trafia enum (class enum) z jakiego na jaki systemu ma się odbyć konwersja, a później za pomoca switcha wybierana jest metoda (private), która rzeczywiście przekonwertuje dane.
