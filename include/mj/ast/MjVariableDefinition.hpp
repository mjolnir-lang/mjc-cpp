#pragma once

#include <mj/ast/MjDefinition.hpp>


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
class MjVariableDefinition : public MjDefinition {
private:
    const MjToken *_name;
    MjType *_type;
    MjComment *_comment;
    MjExpression *_initialization_expression;
    //MjAnnotations *_annotations;
public:


    constexpr
    MjVariableDefinition(
        const MjToken *name,
        MjType *type,
        MjComment *comment,
        Slice<const MjToken> tokens = nullptr
    ) noexcept : MjDefinition(tokens), _name(name), _type(type), _comment(comment) {}


    ///
    /// Properties
    ///


    /// The variable is a reference (storage is not needed)
    constexpr
    bool is_alias() const noexcept {
        return false;
    }


    constexpr
    bool is_anonymous() const noexcept {
        return !has_name();
    }


    constexpr
    bool is_uninitialized() const noexcept {
        return _initialization_expression->tokens()[0].kind == MjTokenKind::UNINITIALIZED;
    }


    constexpr
    bool is_initialized() const noexcept {
        return !is_uninitialized();
    }


    constexpr
    bool is_default_initialized() const noexcept {
        return _initialization_expression != nullptr;
    }


    constexpr
    bool has_comment() const noexcept {
        return _comment != nullptr;
    }


    /// The comment associated with the variable
    constexpr
    const MjComment *comment() const noexcept {
        return _comment;
    }


    /// The comment associated with the variable
    constexpr
    MjComment *comment() noexcept {
        return _comment;
    }


    constexpr
    bool has_name() const noexcept {
        return _name != nullptr;
    }


    /// The variable name
    constexpr
    const MjToken *name() const noexcept {
        return _name;
    }


    constexpr
    bool has_type() const noexcept {
        return _type != nullptr;
    }


    constexpr
    const MjType *type() const noexcept {
        return _type;
    }


    constexpr
    MjType *type() noexcept {
        return _type;
    }


    ///
    /// Methods
    ///


    void set_name(const MjToken *name) noexcept {
        _name = name;
    }


    void set_type(MjType *type) noexcept {
        _type = type;
    }


    /// The comment associated with the variable
    void set_comment(MjComment *comment) noexcept {
        _comment = comment;
    }
};
