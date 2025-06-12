#pragma once

#include <mj/ast/MjDeclaration.hpp>
#include <mj/ast/MjTemplateArgumentList.hpp>
#include <mj/ast/MjTemplateParameterList.hpp>


/// A type consists of a type definition.
class MjTemplate : public MjDeclaration {
protected:
    MjToken _template_name;
    MjTemplateParameterList *_template_parameter_list;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjTemplate(
        MjToken template_name,
        MjTemplateParameterList *template_parameter_list,
        MjItemKind item_kind,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjDeclaration(item_kind, tokens),
        _template_parameter_list(template_parameter_list),
        _template_name(template_name)
    {}


    ///
    /// Properties
    ///


    MjToken template_name() const noexcept {
        return _template_name;
    }


    const MjTemplateParameterList *template_parameter_list() const noexcept {
        return _template_parameter_list;
    }


    MjTemplateParameterList *template_parameter_list() noexcept {
        return _template_parameter_list;
    }
};
