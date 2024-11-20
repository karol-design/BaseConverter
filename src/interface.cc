#include <interface.h>

#include <cstring>
#include <iostream>
#include <map>

const std::string HEX_PREFIX_LOWER = "0x";
const std::string HEX_PREFIX_UPPER = "0X";
const std::string BIN_PREFIX_LOWER = "b";
const std::string BIN_PREFIX_UPPER = "B";
const std::string OCT_PREFIX = "0";

const std::string BIN_ABBREVIATION = "BIN";
const std::string OCT_ABBREVIATION = "OCT";
const std::string DEC_ABBREVIATION = "DEC";
const std::string HEX_ABBREVIATION = "HEX";

// Mapping of abbreviations to NumBase
const std::map<std::string, NumBase> BASE_ABBREVIATION_MAP = {
    {BIN_ABBREVIATION, NumBase::BIN},
    {OCT_ABBREVIATION, NumBase::OCT},
    {DEC_ABBREVIATION, NumBase::DEC},
    {HEX_ABBREVIATION, NumBase::HEX}};

// Constructor
Interface::Interface(CliData cli_data) {
  if (!cli_data.app_description || !cli_data.app_help_content || !cli_data.app_name || !cli_data.app_version || !cli_data.argv || !cli_data.conv) {
    std::cout << "Error: invalid argument (NULL pointer)!" << std::endl;
  } else {
    cli_data_ = cli_data;
  }
}

void Interface::runInterface() {
  processInput();
  switch (interface_state_) {
    case (InterfaceState::START): {
      showDescription();
      break;
    }
    case (InterfaceState::CONVERT): {
      handleConvert();
      break;
    }
    case (InterfaceState::HELP):
    default: {
      handleHelp();
      break;
    }
  }
}

void Interface::processInput() {
  // If there are no arguments
  if (cli_data_.argc == 1) {
    interface_state_ = InterfaceState::START;
    return;
  }

  if (!strcmp(*(cli_data_.argv + 1), "-h") || !strcmp(*(cli_data_.argv + 1), "--help")) {
    interface_state_ = InterfaceState::HELP;
    return;
  }

  if (cli_data_.argc >= 3) {
    std::string str = *(cli_data_.argv + 1);
    getBase(&str);
    conversion_data_.num_str = str;
    interface_state_ = InterfaceState::CONVERT;

    str = *(cli_data_.argv + 2);
    bool target_base_valid = false;
    for (const auto& [abbreviation, base] : BASE_ABBREVIATION_MAP) {
      if (!str.compare(abbreviation)) {
        target_base_ = base;
        target_base_valid = true;
        break;
      }
    }

    if (!target_base_valid) {
      interface_state_ = InterfaceState::HELP;
    }

    if (cli_data_.argc >= 4 && (!strcmp(*(cli_data_.argv + 3), "-v") || !strcmp(*(cli_data_.argv + 3), "--verbose"))) {
      is_debug_activated_ = true;
    } else {
      is_debug_activated_ = false;
    }
  } else {
    interface_state_ = InterfaceState::HELP;
  }
}

void Interface::getBase(std::string* num) {
  if (num->find(HEX_PREFIX_LOWER) == 0 || num->find(HEX_PREFIX_UPPER) == 0) {
    num->erase(0, HEX_PREFIX_LOWER.length()); // TODO: Add error handling
    conversion_data_.origin_base = NumBase::HEX;
  } else if (num->find(BIN_PREFIX_LOWER) == 0 || num->find(BIN_PREFIX_UPPER) == 0) {
    num->erase(0, BIN_PREFIX_LOWER.length());
    conversion_data_.origin_base = NumBase::BIN;
  } else if (num->find(OCT_PREFIX) == 0) {
    num->erase(0, OCT_PREFIX.length());
    conversion_data_.origin_base = NumBase::OCT;
  } else {
    conversion_data_.origin_base = NumBase::DEC;
  }
}

void Interface::showDescription() {
  std::cout << "### " << *cli_data_.app_name << " ###" << std::endl;
  std::cout << *cli_data_.app_description << std::endl;
  std::cout << "Version: " << *cli_data_.app_version << ", Use -h to invoke the manual." << std::endl;
}

void Interface::handleHelp() {
  std::cout << *cli_data_.app_help_content;
}

void Interface::handleConvert() {
  BaseConverterError ret;
  std::string result;
  ret = cli_data_.conv->setNumber(&conversion_data_);
  if (ret != BaseConverterError::OK) {
    std::cout << "Setting number failed! Error: " << static_cast<BASECONVERTERERROR_SIZE>(ret) << " !" << std::endl;
    return;
  }

  if (is_debug_activated_) {
    ret = cli_data_.conv->printNumber();
    if (ret != BaseConverterError::OK) {
      std::cout << "Printing number failed! Error: " << static_cast<BASECONVERTERERROR_SIZE>(ret) << " !" << std::endl;
      return;
    }
  }

  ret = cli_data_.conv->toBase(target_base_, &result);
  if (ret != BaseConverterError::OK) {
    std::cout << "Converting the number failed! Error: " << static_cast<BASECONVERTERERROR_SIZE>(ret) << " !" << std::endl;
    return;
  }

  if (is_debug_activated_) {
    std::cout << "Conversion output: ";
  }

  std::cout << result << std::endl;
}