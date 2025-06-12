#pragma once

#include <mj/ast/MjType.hpp>


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
class MjTypeImplementation : public MjType {
private:
    MjInterfaceType *_interface;
    MjType *_target_type;
public:


    constexpr
    MjTypeImplementation(Slice<const MjToken> tokens = nullptr) noexcept :
        MjType(MjItemKind::TYPE_IMPLEMENTATION, tokens)
    {}
};
