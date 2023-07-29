#pragma once

#include "mj/ast/MjStatement.hpp"


// The 'implementation' scope is a context for defining types, members,
// methods, and operators declared by an interface the class or interface is
// implementing.

// implements INTERFACE {
//     ...
// }

// Implementation scopes may be further specified by the use of generics.

// implements INTERFACE<...> {
//     ...
// }
class MjImplementation {
};
