#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <BaseConverter.hpp>
#include <format>

#define INTERFACESTATE_SIZE uint32_t

/// @brief Command Line Interface state type
enum class InterfaceState : INTERFACESTATE_SIZE {
  STATE_MENU,
  STATE_CONVERT,
  STATE_HELP,
  STATE_ERROR
};

/// @brief Command Line Interface Class
class Interface {
 public:
  // [Constructor]
  Interface(BaseConverter* conv_ptr);

  // Usage: BaseConv 0x4f00 BIN / BaseConv -h / BaseConv
  void run();

 protected:
 private:
  BaseConverter* _conv;
  InterfaceState _state;

  void processInput(const std::string* input);
  void showMenu();
  void handleHelp();
  void handleConvert();
  void handleError();
};

#endif /* INTERFACE_HPP */