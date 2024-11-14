#include <base_converter.h>
#include <interface.h>

#include <iostream>
#include <string>

const std::string APP_NAME = "BaseConverter";
const std::string APP_DESCRIPTION = "CLI app for converting numbers between various numeral systems.";
const std::string APP_VERSION = "1.0";
const std::string APP_HELP =
    "Usage: ./baseconverter [NUMBER] [TARGET_BASE] [OPTIONS] ...\n"
    "Convert the NUMBER to TARGET_BASE and return the result.\n\n"
    "Note: TAGET_BASE has to be one of the following: BIN, OCT, DEC, HEX.\n"
    "Note: Base of the NUMBER is detected automatically depending on how the NUMBER starts: \n"
    "b or B (BIN), 0 (OCT), 0x or 0X (HEX), otherwise (DEC).\n\n"
    "All arguments for long options have the same meaning as for short arguments.\n"
    "  -h, --help            Display this help and exit.\n"
    "  -v, --verbose         Enable additional trace output.\n\n"
    "Usage example:\n"
    "   ./baseconverter 0xFF0A10 BIN --verbose \n";

int main(int argc, char* argv[]) {
  // Instantiate the core converter and pass it to the CLI instance
  BaseConverter conv;
  CliData cli_data = {
      argc,
      argv,
      &APP_NAME,
      &APP_DESCRIPTION,
      &APP_VERSION,
      &APP_HELP,
      &conv};

  Interface cli(cli_data);
  cli.runInterface();
}