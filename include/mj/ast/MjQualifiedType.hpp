#pragma once

#include <mj/ast/MjType.hpp>


class MjQualifiedType : public MjType {
private:
    MjType *_base_type;
    MjTypeQualifiers _type_qualifiers;
public:


    ///
    /// Constructors
    ///


    MjQualifiedType(MjType *base_type, MjTypeQualifiers type_qualifiers) noexcept :
        MjType(MjTypeKind::QUALIFIED),
        _base_type(base_type),
        _type_qualifiers(type_qualifiers)
    {}


    ///
    /// Properties
    ///


    constexpr
    const MjType *base_type() const noexcept {
        return _base_type;
    }


    constexpr
    MjType *base_type() noexcept {
        return _base_type;
    }


    constexpr
    MjTypeQualifiers type_qualifiers() const noexcept {
        return _type_qualifiers;
    }


    ///
    /// Methods
    ///


};
