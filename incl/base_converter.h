#ifndef BASECONVERTER_HPP
#define BASECONVERTER_HPP

#include <format>
#include <string>

#define BASECONVERTERERROR_SIZE uint32_t
#define NUMBASE_SIZE uint32_t
#define NUMBASE_FILEDS 4

/// @brief Numeral base type
enum class NumBase : NUMBASE_SIZE {
  BASE_BIN = 0,
  BASE_OCT = 1,
  BASE_DEC = 2,
  BASE_HEX = 3
};

/// @brief BaseConverter Error type
enum class BaseConverterError : BASECONVERTERERROR_SIZE {
  ERROR_OK,
  ERROR_INVALID_NUMBER,
  ERROR_INVALID_BASE,
  ERROR_CONVERSION_FAULT,
  ERROR_GENERIC
};

/// @brief Struct with the initial data for number conversion
typedef struct {
  std::string numStr;
  NumBase originBase;
} BaseConverterData;

class BaseConverter {
 public:
  /// @brief [Constructor]
  BaseConverter();

  /// @brief [Constructor] Verify if the number is valid and convert it to decimal
  /// @param _data BaseConverterData struct with the number and origin base
  BaseConverter(BaseConverterData* data);

  /// @brief [Modifier] Set the number to be converted and its base
  /// @param data Pointer to the BaseConverterData struct with the number and origin base
  BaseConverterError setNumber(BaseConverterData* data);

  /// @brief [Selector] Get the current number to be converted and its base
  /// @param data Pointer to the struct where number and base should be saved
  void getNumber(BaseConverterData* data) const;

  /// @brief Convert the number to a selected numeral system
  /// @param target_base Target base
  /// @param result Pointer to a string for storing the result of the conversion
  BaseConverterError toBase(const NumBase target_base, std::string* result);

  /// @brief Print the current number and its numeral system
  BaseConverterError printNumber() const;

 protected:
 private:
  bool _isValid;  // Is the current number (to be converted) valid
  BaseConverterData _data;
  uint64_t _numDecimal;
  bool isValidNumber();
  uint64_t strToDec();
  std::string toDec();
  std::string toHex();
  std::string toOct();
  std::string toBin();
};

#endif /* BASECONVERTER_HPP */