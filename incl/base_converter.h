#ifndef BASE_CONVERTER_H_
#define BASE_CONVERTER_H_

#include <format>
#include <string>

#define BASECONVERTERERROR_SIZE uint32_t
#define NUMBASE_SIZE uint32_t
#define NUMBASE_FILEDS 4

/// @brief Numeral base type
enum class NumBase : NUMBASE_SIZE {
  BIN,
  OCT,
  DEC,
  HEX
};

/// @brief BaseConverter Error type
enum class BaseConverterError : BASECONVERTERERROR_SIZE {
  OK,
  INVALID_NUMBER,
  INVALID_BASE,
  INVALID_POINTER,
  CONVERSION_FAULT,
  GENERIC
};

/// @brief Struct with the data for number conversion
struct BaseConverterData {
  std::string num_str;
  NumBase origin_base;
};

/// @brief Converter between numeral systems
class BaseConverter {
 public:
  /// @brief [Constructor]
  BaseConverter();

  /// @brief [Constructor] Verify if the number is valid and convert it to decimal
  /// @param conversion_data BaseConverterData struct with the number and origin base
  BaseConverter(BaseConverterData* conversion_data);

  /// @brief [Modifier] Set the number to be converted and its base
  /// @param conversion_data Pointer to the BaseConverterData struct with the number and origin base
  BaseConverterError setNumber(BaseConverterData* conversion_data);

  /// @brief [Selector] Get the current number to be converted and its base
  /// @param conversion_data Pointer to the struct where number and base should be saved
  BaseConverterError getNumber(BaseConverterData* conversion_data) const;

  /// @brief Convert the number to a selected numeral system
  /// @param target_base Target base
  /// @param result Pointer to a string for storing the result of the conversion
  BaseConverterError toBase(const NumBase target_base, std::string* result);

  /// @brief Print the current number and its numeral system
  BaseConverterError printNumber() const;

 protected:
 private:
  bool is_num_valid_;  // Is the current number (to be converted) valid
  BaseConverterData conversion_data_;
  uint64_t num_decimal_;
  bool isNumValid();
  uint64_t strToDec();
  std::string toDec();
  std::string toHex();
  std::string toOct();
  std::string toBin();
};

#endif /* BASE_CONVERTER_H_ */