#include <base_converter.h>

#include <iostream>
#include <string>

// Verify BaseConverter return value
#define ERROR_CHECK(ERR)                   \
  ({                                       \
    if ((ERR) != BaseConverterError::OK) { \
      return -1;                           \
    }                                      \
  })

const std::string num_in = "101";
const std::string EXPECTED_OUTPUT[NUMBASE_FILEDS][NUMBASE_FILEDS] = {
    {"0b101", "05", "5", "0x5"},
    {"0b1000001", "0101", "65", "0x41"},
    {"0b1100101", "0145", "101", "0x65"},
    {"0b100000001", "0401", "257", "0x101"}};

int main() {
  std::string num_out;
  NumBase base_out, base_in;
  BaseConverterError ret;

  // Itterate though all starting bases
  for (NUMBASE_SIZE base_out_uint = 0; base_out_uint < NUMBASE_FILEDS; base_out_uint++) {
    base_out = static_cast<NumBase>(base_out_uint);
    BaseConverterData conv_data = {num_in, base_out};
    BaseConverter conv;
    ERROR_CHECK(conv.setNumber(&conv_data));

    // Itterate though all target bases
    for (NUMBASE_SIZE base_in_uint = 0; base_in_uint < NUMBASE_FILEDS; base_in_uint++) {
      base_in = static_cast<NumBase>(base_in_uint);
      ERROR_CHECK(conv.toBase(base_in, &num_out));

      // Verify if the output is identical to the expected value
      std::string expected = EXPECTED_OUTPUT[static_cast<NUMBASE_SIZE>(base_out)][static_cast<NUMBASE_SIZE>(base_in)];
      if (num_out != expected) {
        return -1;
      }
    }
  }

  return 0;
}