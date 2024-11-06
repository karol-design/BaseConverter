#include <format>
#include <iostream>
#include <string>

using namespace std;

/*===========================================================================
                        FUNCTIONS DECLARATION
===========================================================================*/

bool testNumConverter();

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
} NumConverterData;

/*===========================================================================
                            NumConverter CLASS
===========================================================================*/

class NumConverter {
 public:
  /// @brief [Constructor] Verify if the number is valid and convert it to decimal
  /// @param _data NumConverterData struct with the number and origin base
  NumConverter(const NumConverterData data) : _data(data) {
    if (!isValidNumber()) {
      cout << "Error: invalid number (non-digit character detected)!" << endl;
    }
    _numDecimal = strToDec();
  };

  /// @brief Convert the number to a selected numeral system
  /// @param target_base Target base
  /// @param result Pointer to a string for storing the result of the conversion
  void toBase(NumBase target_base, string* result) {
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
  /// @param data NumConverterData struct with the number and origin base
  void setNumber(const NumConverterData data) {
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
    cout << "Numeral system: " << BASE_TO_STRING[static_cast<NUMBASE_SIZE>(_data.originBase)] << endl;
  }

 protected:
 private:
  NumConverterData _data;
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
                            MAIN FUNCTION
===========================================================================*/

int main() {
  bool result = testNumConverter();
  return 0;
}

/*===========================================================================
                            TEST FUNCTION
===========================================================================*/

/// @brief Test NumConverter class for all starting / target numeral system on one selected value
/// @note It is assumed that the NumBase enum starts from 0 and that the difference between two consequitive members is 1
bool testNumConverter() {
  const string EXPECTED_OUTPUT[NUMBASE_FILEDS][NUMBASE_FILEDS] = {{"0b101", "05", "5", "0x5"}, {"0b1000001", "0101", "65", "0x41"}, {"0b1100101", "0145", "101", "0x65"}, {"0b100000001", "0401", "257", "0x101"}};
  string numOut, numIn = "101";
  NumBase fromBase, toBase;
  uint32_t testNo = 0;

  // Itterate though all starting bases
  for (NUMBASE_SIZE fromBaseUint = 0; fromBaseUint < NUMBASE_FILEDS; fromBaseUint++) {
    fromBase = static_cast<NumBase>(fromBaseUint);
    NumConverterData convData = {numIn, fromBase};
    NumConverter conv(convData);

    // Itterate though all target bases
    for (NUMBASE_SIZE toBaseUint = 0; toBaseUint < NUMBASE_FILEDS; toBaseUint++) {
      toBase = static_cast<NumBase>(toBaseUint);
      conv.toBase(toBase, &numOut);

      // Verify if the output is identical to the expected value
      string expected = EXPECTED_OUTPUT[static_cast<NUMBASE_SIZE>(fromBase)][static_cast<NUMBASE_SIZE>(toBase)];
      if (numOut != expected) {
        cout << "Test result: failed at " << testNo << " out of " << (NUMBASE_FILEDS*NUMBASE_FILEDS) << "! (";
        cout << "Output: " << numOut << ", expected: " << expected << ")" << endl;
        return false;
      }
      testNo++;
    }
  }
  cout << "Test result: success (" << testNo << " out of " << (NUMBASE_FILEDS*NUMBASE_FILEDS) << " passed)!" << endl;
  return true;
}
