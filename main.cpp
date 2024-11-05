#include <format>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/*===========================================================================
                        TYPEDEFS, MACROS AND CONSTS
===========================================================================*/

/// @brief Numeral base type
typedef enum {
  BIN,
  OCT,
  DEC,
  HEX
} num_base_t;

/// @brief String mappings of num_base_t enum
static const uint8_t num_base_uint_mapping[] = {2, 8, 10, 16};

/// @brief String mappings of num_base_t enum
static const char* num_base_str_mapping[] = {
    "Binary",
    "Octal",
    "Decimal",
    "Hexadecimal"};

// Unsigned long int type to be used throughout this app (not required in C++20 or newer)
// typedef unsigned long int uint64_t;

/// @brief Struct with the initial data for number conversion
typedef struct {
  string num_str;
  num_base_t origin_base;
} NumConverter_data_t;

/*===========================================================================
                            NUMCONVERTER CLASS
===========================================================================*/

class NumConverter {
 public:
  /// @brief [Constructor] Verify if the number is valid and convert it to decimal
  /// @param _data NumConverter_data_t struct with the number and origin base
  NumConverter(const NumConverter_data_t data) : _data(data) {
    // Verify if data.num is a number
    if (isValid() != true) {
      cout << "Error: invalid number";
    }
    // Convert the string to decimal - common format for internal processing
    _num = strToDec();
  };

  /// @brief Convert the number to a selected numeral system
  /// @param target_base Target base
  /// @param str Pointer to a string for storing the result of the conversion
  void toBase(num_base_t target_base, string* str) {
    switch (target_base) {
      case BIN: {
        *str = toBin();
        break;
      }
      case OCT: {
        *str = toOct();
        break;
      }
      case DEC: {
        *str = toDec();
        break;
      }
      case HEX: {
        *str = toHex();
        break;
      }
      default: {
        *str = "Error: incorrect target base";
        break;
      }
    }
    return;
  };

  /// @brief Set the number to be converted and its base
  /// @param data NumConverter_data_t struct with the number and origin base
  void setNumber(const NumConverter_data_t data) {
    _data.num_str = data.num_str;
    _data.origin_base = data.origin_base;
    // Verify if data.num is a number
    if (isValid() != true) {
      cout << "Error: invalid number";
    }
    // Convert the string to decimal - common format for internal processing
    _num = strToDec();
  }

  /// @brief Print the current number and its original base (for debugging purposes)
  void printNumber(void) {
    cout << "Number: " << _data.num_str << ", ";
    cout << "Origin: " << num_base_str_mapping[_data.origin_base] << endl;
  }

 protected:
 private:
  NumConverter_data_t _data;
  uint64_t _num;

  bool isValid() {
    bool val = true;
    return val;
  }

  uint64_t strToDec() {
    size_t processed_chars;
    uint64_t dec = static_cast<uint64_t>(abs(stol(_data.num_str.c_str(), &processed_chars, num_base_uint_mapping[_data.origin_base])));
    return dec;
  }

  string toDec() {
    string ret = vformat("{:d}", make_format_args(_num));
    return ret;
  }

  string toHex() {
    string ret = vformat("{:#x}", make_format_args(_num));
    return ret;
  }

  string toOct() {
    string ret = vformat("{:#o}", make_format_args(_num));
    return ret;
  }

  string toBin() {
    string ret = vformat("{:#b}", make_format_args(_num));
    return ret;
  }
};

/*===========================================================================
                            MAIN FUNCTION
===========================================================================*/

int main() {
  cout << "C++ standard used: " << __cplusplus << endl;

  string num_conv, num_origin = "1011";
  num_base_t base, base_start;

  for (uint8_t base_start_uint = BIN; base_start_uint <= HEX; base_start_uint++) {
    base_start = static_cast<num_base_t>(base_start_uint);
    cout << endl;
    NumConverter_data_t conv_data = {num_origin, base_start};
    NumConverter conv(conv_data);
    conv.printNumber();

    for (uint8_t base_uint = BIN; base_uint <= HEX; base_uint++) {
      base = static_cast<num_base_t>(base_uint);
      conv.toBase(base, &num_conv);
      cout << num_base_str_mapping[base_start] << " -> " << num_base_str_mapping[base] << " | " << num_origin << " -> " << num_conv << endl;
    }
  }

  return 0;
}
