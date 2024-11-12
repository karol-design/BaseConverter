#include <BaseConverter.hpp>
#include <Interface.hpp>
#include <iostream>
#include <string>

const static std::string APP_NAME = "BaseConverter";
const static std::string APP_DESCRIPTION = "CLI app for converting numbers between various numeral systems.";
const static std::string APP_VERSION = "1.0";
const static std::string APP_HELP =
    "Usage: ./baseconv [NUMBER] [TARGET_BASE] \n"
    "Convert the NUMBER to TARGET_BASE and print the result.\n"
    "TAGET_BASE has to be one of the following: BIN, OCT, DEC, HEX.\n"
    "Base of the NUMBER is detected automatically:\n"
    "   - BIN if the number starts from b or B;\n"
    "   - OCT if the number starts from 0;\n"
    "   - HEX if the number starts from 0x or 0X;\n"
    "   - DEC otherwise (default);\n\n"
    "Possible agruments:\n"
    "   -h   Display this help and exit.\n"
    "Usage example:\n"
    "   ./baseconv 0xFF0A10 BIN \n";

bool testBaseConverter();

/*===========================================================================
                            MAIN FUNCTION
===========================================================================*/

int main(int argc, char* argv[]) {
  // Instantiate the core converter and pass it to the CLI instance
  BaseConverter conv;
  tCliData CliData = {
      argc,
      argv,
      &APP_NAME,
      &APP_DESCRIPTION,
      &APP_VERSION,
      &APP_HELP,
      &conv};

  Interface cli(CliData);
  cli.run();

  bool result = testBaseConverter();
  return 0;
}

/*===========================================================================
                            TEST FUNCTION
===========================================================================*/

/// @brief Test BaseConverter class for all starting / target numeral system on one selected value
/// @note It is assumed that the NumBase enum starts from 0 and that the difference between two consequitive members is 1
bool testBaseConverter() {
  const std::string EXPECTED_OUTPUT[NUMBASE_FILEDS][NUMBASE_FILEDS] = {{"0b101", "05", "5", "0x5"}, {"0b1000001", "0101", "65", "0x41"}, {"0b1100101", "0145", "101", "0x65"}, {"0b100000001", "0401", "257", "0x101"}};
  std::string numOut, numIn = "101";
  NumBase fromBase, toBase;
  uint32_t testNo = 0;
  BaseConverterError ret;

  // Itterate though all starting bases
  for (NUMBASE_SIZE fromBaseUint = 0; fromBaseUint < NUMBASE_FILEDS; fromBaseUint++) {
    fromBase = static_cast<NumBase>(fromBaseUint);
    BaseConverterData convData = {numIn, fromBase};
    BaseConverter conv;
    ret = conv.setNumber(&convData);
    if (ret != BaseConverterError::ERROR_OK) {
      std::cout << "Error: " << static_cast<BASECONVERTERERROR_SIZE>(ret) << " !" << std::endl;
    }

    // Itterate though all target bases
    for (NUMBASE_SIZE toBaseUint = 0; toBaseUint < NUMBASE_FILEDS; toBaseUint++) {
      toBase = static_cast<NumBase>(toBaseUint);
      conv.toBase(toBase, &numOut);

      // Verify if the output is identical to the expected value
      std::string expected = EXPECTED_OUTPUT[static_cast<NUMBASE_SIZE>(fromBase)][static_cast<NUMBASE_SIZE>(toBase)];
      if (numOut != expected) {
        std::cout << "Test result: failed at " << testNo << " out of " << (NUMBASE_FILEDS * NUMBASE_FILEDS) << "! (";
        std::cout << "Output: " << numOut << ", expected: " << expected << ")" << std::endl;
        return false;
      }
      testNo++;
    }
  }
  std::cout << "Test result: success (" << testNo << " out of " << (NUMBASE_FILEDS * NUMBASE_FILEDS) << " passed)!" << std::endl;
  return true;
}