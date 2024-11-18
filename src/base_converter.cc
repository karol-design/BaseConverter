#include <base_converter.h>

#include <iostream>

/// @brief Base (uint8_t) mapping of NumBase enum
static const uint8_t BASE_TO_UINT[] = {2, 8, 10, 16};

/// @brief String mapping of NumBase enum
static const char* BASE_TO_STRING[] = {"BIN", "OCT", "DEC", "HEX"};

BaseConverter::BaseConverter() {
  is_num_valid_ = false;  // No number and base provided
}

BaseConverter::BaseConverter(BaseConverterData* conversion_data) : conversion_data_(*conversion_data) {
  if (!conversion_data) {
    std::cout << "Error: invalid pointer!" << std::endl;
  } else if (isNumValid()) {
    num_decimal_ = strToDec();
  } else {
    std::cout << "Error: invalid number (non-digit character detected)!" << std::endl;
  }
}

BaseConverterError BaseConverter::setNumber(BaseConverterData* conversion_data) {
  if (!conversion_data) {
    return BaseConverterError::INVALID_POINTER;
  }
  conversion_data_.num_str = conversion_data->num_str;
  conversion_data_.origin_base = conversion_data->origin_base;
  if (!isNumValid()) {
    return BaseConverterError::INVALID_NUMBER;
  }
  num_decimal_ = strToDec();
  return BaseConverterError::OK;
}

BaseConverterError BaseConverter::getNumber(BaseConverterData* conversion_data) const {
  if (!conversion_data) {
    return BaseConverterError::INVALID_POINTER;
  }
  conversion_data->num_str = conversion_data_.num_str;
  conversion_data->origin_base = conversion_data_.origin_base;
  return BaseConverterError::OK;
}

BaseConverterError BaseConverter::toBase(const NumBase target_base, std::string* result) {
  if (!result) {
    return BaseConverterError::INVALID_POINTER;
  }

  if (!is_num_valid_) {
    return BaseConverterError::INVALID_NUMBER;
  }

  switch (target_base) {
    case (NumBase::BIN): {
      *result = toBin();
      break;
    }
    case (NumBase::OCT): {
      *result = toOct();
      break;
    }
    case (NumBase::DEC): {
      *result = toDec();
      break;
    }
    case (NumBase::HEX): {
      *result = toHex();
      break;
    }
    default: {
      *result = "";
      return BaseConverterError::INVALID_BASE;
      break;
    }
  }
  return BaseConverterError::OK;
}

BaseConverterError BaseConverter::printNumber() const {
  if (!is_num_valid_) {
    std::cout << "Error: the current number is not valid!" << std::endl;
    return BaseConverterError::INVALID_NUMBER;
  }
  std::cout << "Value: " << conversion_data_.num_str << ", ";
  std::cout << "Numeral system: " << BASE_TO_STRING[static_cast<NUMBASE_SIZE>(conversion_data_.origin_base)] << std::endl;
  return BaseConverterError::OK;
}

bool BaseConverter::isNumValid() {
  is_num_valid_ = true;
  // Itterate through the string and validate if contains only DEC/HEX numeric characters
  for (const char& c : conversion_data_.num_str) {
    if (!isxdigit(c)) {
      is_num_valid_ = false;
      break;
    }
  }
  return is_num_valid_;
}

uint64_t BaseConverter::strToDec() {
  size_t processed_chars;
  int64_t val = 0;
  try {
    val = std::stoll(conversion_data_.num_str.c_str(), &processed_chars, BASE_TO_UINT[static_cast<NUMBASE_SIZE>(conversion_data_.origin_base)]);
  }

  catch (std::invalid_argument const& ex) {
    std::cout << "Invalid argument (std::invalid_argument); Cause: " << ex.what() << std::endl;
  } catch (std::out_of_range const& ex) {
    std::cout << "Out of range (std::out_of_range); Cause: " << ex.what() << std::endl;
  }
  uint64_t dec = static_cast<uint64_t>(val);
  return dec;
}

std::string BaseConverter::toDec() {
  std::string ret = "";
  try {
    ret = std::vformat("{:d}", std::make_format_args(num_decimal_));
  } catch (std::format_error const& ex) {
    std::cout << "Format error (std::format_error); Cause: " << ex.what() << std::endl;
  } catch (std::bad_alloc const& ex) {
    std::cout << "Bad allocation (std::bad_alloc); Cause: " << ex.what() << std::endl;
  }
  return ret;
}

std::string BaseConverter::toHex() {
  std::string ret = "";
  try {
    ret = std::vformat("{:#x}", std::make_format_args(num_decimal_));
  } catch (std::format_error const& ex) {
    std::cout << "Format error (std::format_error); Cause: " << ex.what() << std::endl;
  } catch (std::bad_alloc const& ex) {
    std::cout << "Bad allocation (std::bad_alloc); Cause: " << ex.what() << std::endl;
  }
  return ret;
}

std::string BaseConverter::toOct() {
  std::string ret = "";
  try {
    ret = std::vformat("{:#o}", std::make_format_args(num_decimal_));
  } catch (std::format_error const& ex) {
    std::cout << "Format error (std::format_error); Cause: " << ex.what() << std::endl;
  } catch (std::bad_alloc const& ex) {
    std::cout << "Bad allocation (std::bad_alloc); Cause: " << ex.what() << std::endl;
  }
  return ret;
}

std::string BaseConverter::toBin() {
  std::string ret = "";
  try {
    ret = std::vformat("{:#b}", std::make_format_args(num_decimal_));
  } catch (std::format_error const& ex) {
    std::cout << "Format error (std::format_error); Cause: " << ex.what() << std::endl;
  } catch (std::bad_alloc const& ex) {
    std::cout << "Bad allocation (std::bad_alloc); Cause: " << ex.what() << std::endl;
  }
  return ret;
}