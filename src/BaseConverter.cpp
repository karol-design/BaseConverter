#include <BaseConverter.hpp>
#include <iostream>

/// @brief Base (uint8_t) mapping of NumBase enum
static const uint8_t BASE_TO_UINT[] = {2, 8, 10, 16};

/// @brief String mapping of NumBase enum
static const char* BASE_TO_STRING[] = {"BIN", "OCT", "DEC", "HEX"};

/// @brief [Constructor]
BaseConverter::BaseConverter() {
  _isValid = false;  // No number and base provided
}

/// @brief [Constructor] Verify if the number is valid and convert it to decimal
/// @param _data BaseConverterData struct with the number and origin base
BaseConverter::BaseConverter(BaseConverterData* data) : _data(*data) {
  if (isValidNumber()) {
    _numDecimal = strToDec();
  } else {
    std::cout << "Error: invalid number (non-digit character detected)!" << std::endl;
  }
}

/// @brief [Modifier] Set the number to be converted and its base
/// @param data Pointer to the BaseConverterData struct with the number and origin base
BaseConverterError BaseConverter::setNumber(BaseConverterData* data) {
  _data.numStr = data->numStr;
  _data.originBase = data->originBase;
  if (!isValidNumber()) {
    std::cout << "Error: invalid number";
    return BaseConverterError::ERROR_INVALID_NUMBER;
  }
  _numDecimal = strToDec();
  return BaseConverterError::ERROR_OK;
}

/// @brief [Selector] Get the current number to be converted and its base
/// @param data Pointer to the struct where number and base should be saved
void BaseConverter::getNumber(BaseConverterData* data) const {
  data->numStr = _data.numStr;
  data->originBase = _data.originBase;
}

/// @brief Convert the number to a selected numeral system
/// @param target_base Target base
/// @param result Pointer to a string for storing the result of the conversion
BaseConverterError BaseConverter::toBase(const NumBase target_base, std::string* result) {
  BaseConverterError ret = BaseConverterError::ERROR_OK;
  if (!_isValid) {
    std::cout << "Error: the current number is not valid!" << std::endl;
    ret = BaseConverterError::ERROR_INVALID_NUMBER;
    return ret;
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
      *result = "";
      ret = BaseConverterError::ERROR_INVALID_BASE;
      break;
    }
  }
  return ret;
}

/// @brief Print the current number and its numeral system
BaseConverterError BaseConverter::printNumber() const {
  if (!_isValid) {
    std::cout << "Error: the current number is not valid!" << std::endl;
    return BaseConverterError::ERROR_INVALID_NUMBER;
  }
  std::cout << "Value: " << _data.numStr << ", ";
  std::cout << "Numeral system: " << BASE_TO_STRING[static_cast<NUMBASE_SIZE>(_data.originBase)] << std::endl;
  return BaseConverterError::ERROR_OK;
  ;
}

bool BaseConverter::isValidNumber() {
  _isValid = true;
  // Itterate through the string and validate if contains only DEC/HEX numeric characters
  for (const char& c : _data.numStr) {
    if (!isxdigit(c)) {
      _isValid = false;
      break;
    }
  }
  return _isValid;
}

uint64_t BaseConverter::strToDec() {
  size_t processed_chars;
  long val = std::stol(_data.numStr.c_str(), &processed_chars, BASE_TO_UINT[static_cast<NUMBASE_SIZE>(_data.originBase)]);
  uint64_t dec = static_cast<uint64_t>(val);
  return dec;
}

std::string BaseConverter::toDec() {
  std::string ret = std::vformat("{:d}", std::make_format_args(_numDecimal));
  return ret;
}

std::string BaseConverter::toHex() {
  std::string ret = std::vformat("{:#x}", std::make_format_args(_numDecimal));
  return ret;
}

std::string BaseConverter::toOct() {
  std::string ret = std::vformat("{:#o}", std::make_format_args(_numDecimal));
  return ret;
}

std::string BaseConverter::toBin() {
  std::string ret = std::vformat("{:#b}", std::make_format_args(_numDecimal));
  return ret;
}