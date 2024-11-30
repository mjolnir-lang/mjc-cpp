#pragma once

#include <mj/ast/MjDefinition.hpp>


class MjTypeEnumerationDefinition : public MjDefinition {
private:
    MjType *_index_type;
    MjType *_value_type;
    Vector<MjVariable *> _values;
public:


    MjTypeEnumerationDefinition(
        const MjToken *name,
        MjComment *comment,
        MjType *index_type,
        MjType *value_type,
        MjTemplateArgumentList template_argument_list = nullptr
    ) :
        _index_type(index_type),
        _value_type(value_type)
    {}


    ///
    /// Properties
    ///


    constexpr
    const MjType *value_type() const noexcept {
        return _value_type;
    }


    constexpr
    MjType *value_type() noexcept {
        return _value_type;
    }


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
