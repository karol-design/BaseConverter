#include <format>
#include <iostream>
#include <string>

using namespace std;

/*===========================================================================
                        FUNCTIONS DECLARATION
===========================================================================*/

bool testBaseConverter();

/*===========================================================================
                        TYPEDEFS, MACROS AND CONSTS
===========================================================================*/

#define NUMBASE_SIZE uint8_t
#define NUMBASE_FILEDS 4

/// @brief Numeral base type
enum class NumBase : NUMBASE_SIZE {
  BASE_BIN = 0,
  BASE_OCT = 1,
  BASE_DEC = 2,
  BASE_HEX = 3
};

/// @brief Base (uint8_t) mapping of NumBase enum
static const uint8_t BASE_TO_UINT[] = {2, 8, 10, 16};

/// @brief String mapping of NumBase enum
static const char* BASE_TO_STRING[] = {"Binary", "Octal", "Decimal", "Hexadecimal"};

// Unsigned long int type to be used throughout this app (not required in C++20 or newer)
// typedef unsigned long int uint64_t;

/// @brief Struct with the initial data for number conversion
typedef struct {
  string numStr;
  NumBase originBase;
} BaseConverterData;

/// @brief Struct with the initial data for the CLI initialization
typedef struct {
  string appName;
  string appDescription;
  string appHelpContent;
  uint64_t appVersion;
} CliData;

/*===========================================================================
                            BaseConverter CLASS
===========================================================================*/

class BaseConverter {
 public:
  /// @brief [Constructor with data struct] Verify if the number is valid and convert it to decimal
  /// @param _data BaseConverterData struct with the number and origin base
  BaseConverter(const BaseConverterData data) : _data(data) {
    if (!isValidNumber()) {
      cout << "Error: invalid number (non-digit character detected)!" << endl;
    }
    _numDecimal = strToDec();
  }

  /// @brief [Constructor no parameters]
  BaseConverter() {
    _isValid = false; // No number and base provided
  }

  /// @brief Convert the number to a selected numeral system
  /// @param target_base Target base
  /// @param result Pointer to a string for storing the result of the conversion
  void toBase(NumBase target_base, string* result) {
    if (!_isValid) {
      cout << "Error: the current number is not valid!" << endl;
      return;
    }

    switch (target_base) {
      case (NumBase::BASE_BIN): {
        *result = toBin();
        break;
      }
      case (NumBase::BASE_OCT): {
        *result = toOct();
        break;
      }
      case (NumBase::BASE_DEC): {
        *result = toDec();
        break;
      }
      case (NumBase::BASE_HEX): {
        *result = toHex();
        break;
      }
      default: {
        *result = "Error: incorrect target base";
        break;
      }
    }
    return;
  };

  /// @brief Set the number to be converted and its base
  /// @param data BaseConverterData struct with the number and origin base
  void setNumber(const BaseConverterData data) {
    _data.numStr = data.numStr;
    _data.originBase = data.originBase;
    if (!isValidNumber()) {
      cout << "Error: invalid number";
    }
    _numDecimal = strToDec();
  }

  /// @brief Print the current number and its numeral system
  void printNumber(void) {
    if (!_isValid) {
      cout << "Error: the current number is not valid!" << endl;
      return;
    }

    cout << "Value: " << _data.numStr << ", ";
    cout << "Numeral system: " << BASE_TO_STRING[static_cast<NUMBASE_SIZE>(_data.originBase)] << endl;
  }

 protected:
 private:
  bool _isValid;  // Is the current number (to be converted) valid
  BaseConverterData _data;
  uint64_t _numDecimal;

  bool isValidNumber() {
    _isValid = true;
    // Itterate through the string and validate if contains only digits
    for (const char& c : _data.numStr) {
      if (!isdigit(c)) {
        _isValid = false;
        break;
      }
    }
    return _isValid;
  }

  uint64_t strToDec() {
    size_t processed_chars;
    long val = stol(_data.numStr.c_str(), &processed_chars, BASE_TO_UINT[static_cast<NUMBASE_SIZE>(_data.originBase)]);
    uint64_t dec = static_cast<uint64_t>(val);
    return dec;
  }

  string toDec() {
    string ret = vformat("{:d}", make_format_args(_numDecimal));
    return ret;
  }

  string toHex() {
    string ret = vformat("{:#x}", make_format_args(_numDecimal));
    return ret;
  }

  string toOct() {
    string ret = vformat("{:#o}", make_format_args(_numDecimal));
    return ret;
  }

  string toBin() {
    string ret = vformat("{:#b}", make_format_args(_numDecimal));
    return ret;
  }
};

/*===========================================================================
                      COmmandLineInterface CLASS
===========================================================================*/

// /// @brief
// class CommandLineInterface {
//  public:
//   // Constructor
//   CommandLineInterface() {
//     ;
//   }

//   // Usage: BaseConv 0x4f00 BIN / BaseConv -h / BaseConv
//   void run() {
//     processInput();  // Process the input, i.e. arguments (incl. flags) and populate adequately the CLI config struct
//     switch (/*MODE*/) {
//       case (/* no arguments */): {
//         showMenu();
//         break;
//       }
//       case (/* conversion */): {
//         handleConvert();
//         break;
//       }
//       case (/* help */): {
//         handleHelp();
//         break;
//       }
//       default: {
//         handleError();
//         break;
//       }
//     }
//   }

//  protected:
//  private:
//   void showMenu() {}
//   void processInput(const std::string& input) {}
//   void handleHelp() {}
//   void handleConvert() {}
//   void handleError() {}
// };

/*===========================================================================
                            MAIN FUNCTION
===========================================================================*/

int main() {
  // // Instantiate the core converter and pass it to the CLI instance
  // BaseConverterData convData = {numIn, fromBase};
  // BaseConverter conv(convData);
  // CommandLineInterface cli(&conv);

  // // Run the CLI loop
  // cli.run();

  bool result = testBaseConverter();
  return 0;
}

/*===========================================================================
                            TEST FUNCTION
===========================================================================*/

/// @brief Test BaseConverter class for all starting / target numeral system on one selected value
/// @note It is assumed that the NumBase enum starts from 0 and that the difference between two consequitive members is 1
bool testBaseConverter() {
  const string EXPECTED_OUTPUT[NUMBASE_FILEDS][NUMBASE_FILEDS] = {{"0b101", "05", "5", "0x5"}, {"0b1000001", "0101", "65", "0x41"}, {"0b1100101", "0145", "101", "0x65"}, {"0b100000001", "0401", "257", "0x101"}};
  string numOut, numIn = "101";
  NumBase fromBase, toBase;
  uint32_t testNo = 0;

  // Itterate though all starting bases
  for (NUMBASE_SIZE fromBaseUint = 0; fromBaseUint < NUMBASE_FILEDS; fromBaseUint++) {
    fromBase = static_cast<NumBase>(fromBaseUint);
    BaseConverterData convData = {numIn, fromBase};
    BaseConverter conv;
    conv.setNumber(convData);

    // Itterate though all target bases
    for (NUMBASE_SIZE toBaseUint = 0; toBaseUint < NUMBASE_FILEDS; toBaseUint++) {
      toBase = static_cast<NumBase>(toBaseUint);
      conv.toBase(toBase, &numOut);

      // Verify if the output is identical to the expected value
      string expected = EXPECTED_OUTPUT[static_cast<NUMBASE_SIZE>(fromBase)][static_cast<NUMBASE_SIZE>(toBase)];
      if (numOut != expected) {
        cout << "Test result: failed at " << testNo << " out of " << (NUMBASE_FILEDS * NUMBASE_FILEDS) << "! (";
        cout << "Output: " << numOut << ", expected: " << expected << ")" << endl;
        return false;
      }
      testNo++;
    }
  }
  cout << "Test result: success (" << testNo << " out of " << (NUMBASE_FILEDS * NUMBASE_FILEDS) << " passed)!" << endl;
  return true;
}
