#pragma once

#include <mj/ast/MjDefinition.hpp>
#include <mj/ast/MjInterfaceType.hpp>


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
class MjTypeImplementationDefinition : public MjDefinition {
private:
    MjInterfaceType *_interface;
    MjType *_target_type;
public:


    constexpr
    MjTypeImplementationDefinition(Slice<const MjToken> tokens = nullptr) noexcept :
        MjDefinition(tokens)
    {}
};
