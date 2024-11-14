#include <Interface.hpp>
#include <iostream>

// Constructor
Interface::Interface(tCliData CliData) : _CliData(CliData) {}

void Interface::run() {
  processInput();
  switch (_state) {
    case (InterfaceState::STATE_START): {
      showWelcomeMessage();
      break;
    }
    case (InterfaceState::STATE_CONVERT): {
      handleConvert();
      break;
    }
    case (InterfaceState::STATE_HELP):
    default: {
      handleHelp();
      break;
    }
  }
}

void Interface::processInput() {
  // If there are no arguments
  if (_CliData.argc == 1) {
    _state = InterfaceState::STATE_START;
    return;
  }

  if (*(_CliData.argv + 1) == "-h") {
    _state = InterfaceState::STATE_HELP;
    return;
  }

  if (_CliData.argc == 3) {
    std::string str = *(_CliData.argv + 1);
    getBase(&str);
    _convData.numStr = str;
    _state = InterfaceState::STATE_CONVERT;

    str = *(_CliData.argv + 2);
    if (str.compare("BIN") == 0) {
      _targetBase = NumBase::BASE_BIN;
    } else if (str.compare("OCT") == 0) {
      _targetBase = NumBase::BASE_OCT;
    } else if (str.compare("DEC") == 0) {
      _targetBase = NumBase::BASE_DEC;
    } else if (str.compare("HEX") == 0) {
      _targetBase = NumBase::BASE_HEX;
    } else {
      _state = InterfaceState::STATE_HELP;
    }
  } else {
    _state = InterfaceState::STATE_HELP;
  }
}

void Interface::getBase(std::string* num) {
  if (num->find("0x") == 0 || num->find("0X") == 0) {
    num->erase(0, 2);
    _convData.originBase = NumBase::BASE_HEX;
  } else if (num->find("b") == 0 || num->find("B") == 0) {
    num->erase(0, 1);
    _convData.originBase = NumBase::BASE_BIN;
  } else if (num->find("0") == 0) {
    num->erase(0, 1);
    _convData.originBase = NumBase::BASE_OCT;
  } else {
    _convData.originBase = NumBase::BASE_DEC;
  }
}

void Interface::showWelcomeMessage() {
  std::cout << "### " << *_CliData.appName << " ###" << std::endl;
  std::cout << *_CliData.appDescription << std::endl;
  std::cout << "Version: " << *_CliData.appVersion << ", Use -h to invoke the manual." << std::endl;
}

void Interface::handleHelp() {
  std::cout << _CliData.appHelpContent;
}

void Interface::handleConvert() {
  std::string result;
  _CliData.conv->setNumber(&_convData);
  _CliData.conv->printNumber();
  _CliData.conv->toBase(_targetBase, &result);
  std::cout << "Result: " << result << std::endl;
}