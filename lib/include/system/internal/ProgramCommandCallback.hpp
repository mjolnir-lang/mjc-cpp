#pragma once

#include <core/Function.hpp>
#include <core/Error.hpp>


/// @brief A command callback function.
using ProgramCommandCallback = Function<Error()>;
