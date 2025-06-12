#pragma once

#include <mj/ast/MjType.hpp>


/// lifetime
template<class MjStorageClass>
struct MjStorageLifetimeValues {
    static constexpr MjStorageClass LOCAL{0};
    static constexpr MjStorageClass GLOBAL{0};
};


/// linkage
template<class MjStorageClass>
struct MjStorageLinkageValues {
    static constexpr MjStorageClass NONE{0};
    static constexpr MjStorageClass INTERNAL{0};
    static constexpr MjStorageClass EXTERNAL{0};
};


/// lifetime and linkage
template<class MjStorageClass>
struct MjStorageClassValues {
    static constexpr MjStorageClass NONE{0};
    static constexpr MjStorageClass REGISTER{0};
    static constexpr MjStorageClass INTERNAL{0};
    static constexpr MjStorageClass SHARED{0};
};


class MjStorageClass : public Enum<u8>, public MjStorageClassValues<MjStorageClass> {
public:


    constexpr
    explicit
    MjStorageClass(u8 id) noexcept : Enum(id) {}
};





/// @brief An `MjVariable` is an `MjObject` associated with an identifier.
class MjVariable : public MjItem {
private:
    MjToken _name;
    MjType *_type;        // The type that owns the member
    bool _is_mutable;     // The property does not inherit the 'const'-ness of its owner (does not apply to references)
public:


    constexpr
    MjVariable(
        MjToken name,
        MjType *type,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjItem(MjItemKind::VARIABLE, tokens),
        _name(name),
        _type(type)
    {}


    ///
    /// Properties
    ///


    /// The variable is a reference (storage is not needed)
    constexpr
    bool is_alias() const noexcept {
        return false;
    }


    constexpr
    bool is_deterministic() const noexcept {
        return !type()->is_volatile();
    }


    constexpr
    bool has_comment() const {
        return;
    }


    /// The comment associated with the variable
    constexpr
    const MjComment *comment() const noexcept {
        return;
    }


    /// The comment associated with the variable
    constexpr
    MjComment *comment() noexcept {
        return;
    }


    /// The variable name
    constexpr
    const MjToken *name() const noexcept {
        return;
    }


    constexpr
    const MjType *type() const noexcept {
        return;
    }


    constexpr
    MjType *type() noexcept {
        return;
    }


    /// The absolute address of the variable storage
    constexpr
    u64 address() const noexcept {
        return;
    }


    /// The absolute address of the variable storage
    constexpr
    u64 offset() const noexcept {
        return;
    }


    /// The absolute address of the variable storage
    constexpr
    u64 size() const noexcept {
        return;
    }


    ///
    /// Methods
    ///

};
