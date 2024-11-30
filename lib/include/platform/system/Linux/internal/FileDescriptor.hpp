#pragma once

#include <core/Enum.hpp>


namespace platform::system::Linux::internal {


/// A file descriptor
using FileDescriptor = i32;

/// A Process ID
using ProcessId = i32;

/// A User ID
using UserId = i32;

/// A Group ID
using GroupId = i32;

/// A Thread ID
using ThreadId = i32;

using FileHandle = struct file_handle;


}
