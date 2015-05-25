#include "callofundefinedfunctionexception.hh"

namespace Algorithm
{
  CallOfUndefinedFunctionException::CallOfUndefinedFunctionException(const std::string& function)
    : std::runtime_error("In " + function + ".")
  {}
}
