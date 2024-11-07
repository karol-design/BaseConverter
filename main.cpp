#include <iostream>
#include <string>
#include <BaseConverter.hpp>
#include <Interface.hpp>

bool testBaseConverter();

/// @brief Struct with the initial data for the CLI initialization
// typedef struct {
//   std::string appName;
//   std::string appDescription;
//   std::string appHelpContent;
//   uint64_t appVersion;
// } CliData;

/*===========================================================================
                            MAIN FUNCTION
===========================================================================*/

int main() {
  // Instantiate the core converter and pass it to the CLI instance
  BaseConverter conv;
  Interface cli(&conv);

  // Run the CLI loop
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