#include <iostream>
#include <string>

using namespace std;

/*===========================================================================
                        TYPEDEFS, MACROS AND CONSTS
===========================================================================*/

/// @brief Numeral base type
typedef enum {
  HEX,
  DEC,
  OCT,
  BIN
} num_base_t;

/// @brief String mappings of num_base_t enum
static const char* num_base_mapping[] = {
    "Hexadecimal",
    "Decimal",
    "Octal",
    "Binary"};

// Unsigned int type to be used throughout this app
typedef unsigned int uint64_t;

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
    if(isValid() != true) {
        cout << "Error: invalid number";
    }
    // Convert the string to decimal - common format for internal processing
    _num = toDec();
  };

  /// @brief Convert the number to a selected numeral system
  /// @param target_base Target base
  /// @param str String to store the result of the conversion
  void toBase(num_base_t target_base, string *str) {
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
        *str = to_string(_num);
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
  /// @param number Num to be converted
  /// @param base Current base
  void setNumber(const NumConverter_data_t data) {
    _data.num_str = data.num_str;
    _data.origin_base = data.origin_base;
  }

  /// @brief Print the current number and its original base (for debugging purposes)
  void printNumber(void) {
    cout << "Number: " << _data.num_str << ", ";
    cout << "Origin: " << num_base_mapping[_data.origin_base] << endl;
  }

 protected:
 
 private:
  NumConverter_data_t _data;
  uint64_t _num;

  bool isValid() {
    bool val = true;
    return val;
  }

  uint64_t toDec() {
    uint64_t dec = 0;
    return dec;
  }

  string toHex() {
    string ret = "0x00";
    return ret;
  }

  string toOct() {
    string ret = "00";
    return ret;
  }

  string toBin() {
    string ret = "b00";
    return ret;
  }
};

/*===========================================================================
                            MAIN FUNCTION
===========================================================================*/

int main() {
  string num_conv, num_origin = "100";
  num_base_t base_origin = DEC;
  num_base_t base_target = BIN;

  NumConverter_data_t conv_data = {num_origin, base_origin};
  NumConverter conv(conv_data);

  conv.printNumber();
  conv.toBase(base_target, &num_conv);
  cout << "Original number: " << num_origin << ", converted: " << num_conv << endl;

  return 0;
}
