#pragma once

#include <core/Error.hpp>
#include <core/Function.hpp>
#include <core/StringView.hpp>


/// @brief An argument parsing function.
/// @param string The argument value string to parse
/// @param values The address of the value to parse
/// @param index The index of the element within the parse
using ProgramArgumentParser = Function<Error(StringParser &)>;
