#pragma once

#include <mj/ast/MjStatement.hpp>
#include <mj/ast/MjTypeTemplate.hpp>


class MjStrucureTypeTemplate : public MjTypeTemplate {
private:
public:


    ///
    /// Constructors
    ///


    constexpr
    MjStrucureTypeTemplate(
        MjToken template_name,
        MjTemplateParameterList *template_parameter_list,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjTypeTemplate(template_name, template_parameter_list, MjItemKind::STRUCTURE_TYPE_TEMPLATE, tokens)
    {}


    ///
    /// Properties
    ///

};
