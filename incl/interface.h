#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <BaseConverter.hpp>
#include <format>

#define INTERFACESTATE_SIZE uint32_t

/// @brief Struct with the initial data for the CLI initialization
typedef struct {
  int argc;
  char** argv;
  const std::string* appName;
  const std::string* appDescription;
  const std::string* appVersion;
  const std::string* appHelpContent;
  BaseConverter* conv;
} tCliData;

/// @brief Command Line Interface state type
enum class InterfaceState : INTERFACESTATE_SIZE {
  STATE_START,
  STATE_CONVERT,
  STATE_HELP
};

/// @brief Command Line Interface Class
class Interface {
 public:
  // [Constructor]
  Interface(tCliData CliData);

  // Usage: BaseConv 0x4f00 BIN / BaseConv -h / BaseConv
  void run();

 protected:
 private:
  tCliData _CliData;
  InterfaceState _state;
  NumBase _targetBase;
  BaseConverterData _convData;

  void processInput();
  void getBase(std::string* num);
  void showWelcomeMessage();
  void handleHelp();
  void handleConvert();
};

#endif /* INTERFACE_HPP */