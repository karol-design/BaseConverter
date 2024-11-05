#include <format>
#include <iostream>
#include <string>

using namespace std;

/*===========================================================================
                        FUNCTIONS DECLARATION
===========================================================================*/

void testNumConverter();

/*===========================================================================
                        TYPEDEFS, MACROS AND CONSTS
===========================================================================*/

/// @brief Numeral base type
typedef enum {
  BASE_BIN,
  BASE_OCT,
  BASE_DEC,
  BASE_HEX
} num_base_t;

/// @brief Base (uint8_t) mapping of num_base_t enum
static const uint8_t BASE_TO_UINT[] = {2, 8, 10, 16};

/// @brief String mapping of num_base_t enum
static const char* BASE_TO_STRING[] = {"Binary", "Octal", "Decimal", "Hexadecimal"};

// Unsigned long int type to be used throughout this app (not required in C++20 or newer)
// typedef unsigned long int uint64_t;

/// @brief Struct with the initial data for number conversion
typedef struct {
  string numStr;
  num_base_t originBase;
} NumConverter_data_t;

/*===========================================================================
                            NumConverter CLASS
===========================================================================*/

class NumConverter {
 public:
  /// @brief [Constructor] Verify if the number is valid and convert it to decimal
  /// @param _data NumConverter_data_t struct with the number and origin base
  NumConverter(const NumConverter_data_t data) : _data(data) {
    if (!isValidNumber()) {
      cout << "Error: invalid number (non-digit character detected)!" << endl;
    }
    _numDecimal = strToDec();
  };

  /// @brief Convert the number to a selected numeral system
  /// @param target_base Target base
  /// @param result Pointer to a string for storing the result of the conversion
  void toBase(num_base_t target_base, string* result) {
    switch (target_base) {
      case BASE_BIN: {
        *result = toBin();
        break;
      }
      case BASE_OCT: {
        *result = toOct();
        break;
      }
      case BASE_DEC: {
        *result = toDec();
        break;
      }
      case BASE_HEX: {
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
  /// @param data NumConverter_data_t struct with the number and origin base
  void setNumber(const NumConverter_data_t data) {
    _data.numStr = data.numStr;
    _data.originBase = data.originBase;
    if (!isValidNumber()) {
      cout << "Error: invalid number";
    }
    _numDecimal = strToDec();
  }

  /// @brief Print the current number and its numeral system
  void printNumber(void) {
    cout << "Value: " << _data.numStr << ", ";
    cout << "Numeral system: " << BASE_TO_STRING[_data.originBase] << endl;
  }

 protected:
 private:
  NumConverter_data_t _data;
  uint64_t _numDecimal;

  bool isValidNumber() {
    // Itterate through the string and validate if contains only digits
    for (const char& c : _data.numStr) {
      if (!isdigit(c)) {
        return false;
      }
    }
    return true;
  }

  uint64_t strToDec() {
    size_t processed_chars;
    uint64_t dec = static_cast<uint64_t>(abs(stol(_data.numStr.c_str(), &processed_chars, BASE_TO_UINT[_data.originBase])));
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
                            MAIN FUNCTION
===========================================================================*/

int main() {
  testNumConverter();
  return 0;
}

/*===========================================================================
                            TEST FUNCTION
===========================================================================*/

/// @brief Test NumConverter class for all starting / target numeral system on one selected value
void testNumConverter() {
  const string EXPECTED_OUTPUT[4][4] = {{"0b101", "05", "5", "0x5"}, {"0b1000001", "0101", "65", "0x41"}, {"0b1100101", "0145", "101", "0x65"}, {"0b100000001", "0401", "257", "0x101"}};
  string convertedNum, startingNum = "101";
  num_base_t targetBase, startingBase;

  // Itterate though all starting bases
  for (uint8_t startingBaseUint = BASE_BIN; startingBaseUint <= BASE_HEX; startingBaseUint++) {
    startingBase = static_cast<num_base_t>(startingBaseUint);
    NumConverter_data_t convData = {startingNum, startingBase};
    NumConverter conv(convData);

    // Itterate though all target bases
    for (uint8_t targetBaseUint = BASE_BIN; targetBaseUint <= BASE_HEX; targetBaseUint++) {
      targetBase = static_cast<num_base_t>(targetBaseUint);
      conv.toBase(targetBase, &convertedNum);

      // Verify if the output is identical to the expected value
      if (convertedNum != EXPECTED_OUTPUT[startingBase][targetBase]) {
        cout << "Test result: failed! Output: " << convertedNum << ", expected: " << EXPECTED_OUTPUT[startingBase][targetBase] << endl;
        return;
      }
    }
  }
  cout << "Test result: success!" << endl;
}
