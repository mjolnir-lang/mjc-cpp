#pragma once

#include <mj/ast/MjEnumerationDefinition.hpp>
#include <mj/ast/MjType.hpp>


class MjEnumerationType : public MjType {
private:
    MjType *_index_type;
    Vector<MjVariable *> _values;
public:


    MjEnumerationType(
        const MjToken *name,
        MjComment *comment,
        MjType *index_type,
        MjTemplateArgumentList template_argument_list = nullptr
    ) :
        MjType(MjTypeType::ENUMERATION, name, template_argument_list),
        _index_type(index_type)
    {}


    ///
    /// Properties
    ///


    constexpr
    const MjType *index_type() const noexcept {
        return _index_type;
    }


    constexpr
    MjType *index_type() noexcept {
        return _index_type;
    }


    constexpr
    const Vector<MjVariable *> &values() const noexcept {
        return _values;
    }


    constexpr
    Vector<MjVariable *> &values() noexcept {
        return _values;
    }


    ///
    /// Methods
    ///


};
