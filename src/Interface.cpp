#include <Interface.hpp>
#include <iostream>

// Constructor
Interface::Interface(BaseConverter* conv_ptr) : _conv(conv_ptr) {}

// Usage: BaseConv 0x4f00 BIN / BaseConv -h / BaseConv
void Interface::run() {
  std::string str = "Test!";
  processInput(&str);  // Process the input, i.e. arguments (incl. flags) and populate adequately the CLI config struct
  switch (_state) {
    case (InterfaceState::STATE_MENU): {
      showMenu();
      break;
    }
    case (InterfaceState::STATE_CONVERT): {
      handleConvert();
      break;
    }
    case (InterfaceState::STATE_HELP): {
      handleHelp();
      break;
    }
    case (InterfaceState::STATE_ERROR):
    default: {
      handleError();
      break;
    }
  }
}

void Interface::processInput(const std::string* input) {
  _state = InterfaceState::STATE_ERROR;
}

void Interface::showMenu() {
  std::cout << "Menu" << std::endl;
}

void Interface::handleHelp() {
  std::cout << "Help" << std::endl;
}

void Interface::handleConvert() {
  std::cout << "Convert" << std::endl;
}

void Interface::handleError() {
  std::cout << "Error" << std::endl;
}