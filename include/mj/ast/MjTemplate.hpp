#pragma once

#include <mj/ast/MjItem.hpp>
#include <mj/ast/MjTemplateArgumentList.hpp>
#include <mj/ast/MjTemplateParameterList.hpp>


/// A type consists of a type definition.
class MjTemplate : public MjItem {
public:


    ///
    /// Constructors
    ///


    constexpr
    MjTemplate(MjItemKind item_kind) noexcept : MjItem(item_kind) {}


    ///
    /// Properties
    ///


    const MjTemplateParameterList &template_parameter_list() const noexcept {
        return _template_parameter_list;
    }


    MjTemplateParameterList &template_parameter_list() noexcept {
        return _template_parameter_list;
    }
};
