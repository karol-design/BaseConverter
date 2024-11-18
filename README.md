# BaseConv | Numeral Systems Converter
Simple CLI toolkit for converting numbers between any of the most popular numeral systems (**BIN, OCT, DEC, HEX**) 

## Building and using [on Windows]
```console
$ cmake -B .\build -G "MinGW Makefiles"
$ cmake --build .\build
$ cd .\build
$ ./baseconverter --help
```

## Testing
```console
$ cd .\build
$ ctest
```

## Requirements
General requirements:
* The main functionality that this code should deliver is to convert numbers between any of four selected systems (binary, octal, decimal, hexadecimal)
* The base/numeral system of the input sould be detected automatically
* The functionality should be encapsulated in a single class called BaseConverter
* Both input and output from the BaseConverter class should be in a form of a string
* An additional class called Interface should handle the interaction with the user through the Command Prompt
* Any data exchange between both classes should be carried out via a dedicated structure
* The number under conversion should be of uint64_t type
* The BaseConverter class should use in particular C++ built-in functions (e.g. strtol, bitwidth etc.)
* The action undertaken by the BaseConverter class should be triggered from the switch control statement

### Typical use case:
>A user interacts with the app via the Command Prompt. An execution with no input parameters results in printing the welcome note and a very brief description of the app. In addition -h or --help argument can be used to display help/manual of the app. For the main functionality the user have to execute the app with the first argument being the number to be converted, and the second one being the target numerical system (e.g. BaseConv.exe 0x4f00 BIN) - the app should return the converted number to the console and ask if further conversion is needed.

## Improvement list:
- Add a better definition of interface arguments and configuration
- Add a unit test for the Interface class
- Improve parameter validation and error handling
- Review the commenting and its completeness
- Review used coding style convention (if correct and consistent)
- Reduce number of data members in favour of passing data as parameters of class methods (?)

## Conventions:
Google C++ Style Guide
