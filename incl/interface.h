#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <base_converter.h>

#include <format>

#define INTERFACESTATE_SIZE uint32_t

/// @brief Struct with the initial data for the CLI initialization
struct CliData {
  int argc;
  char** argv;
  const std::string* app_name;
  const std::string* app_description;
  const std::string* app_version;
  const std::string* app_help_content;
  BaseConverter* conv;
};

/// @brief Command Line Interface state type
enum class InterfaceState : INTERFACESTATE_SIZE {
  START,
  CONVERT,
  HELP
};

/// @brief Command Line Interface
class Interface {
 public:
  /// @brief [Constructor] Copy cli_data into a private data member
  /// @param cli_data CliData struct with initial interface settings
  Interface(CliData cli_data);

  /// @brief Process input and invoke appropriate functionality
  void runInterface();

 protected:
 private:
  CliData cli_data_;
  InterfaceState interface_state_;
  bool is_debug_activated_;
  NumBase target_base_;
  BaseConverterData conversion_data_;

  void processInput();
  void getBase(std::string* num);
  void showDescription();
  void handleHelp();
  void handleConvert();
};

#endif /* INTERFACE_H_ */