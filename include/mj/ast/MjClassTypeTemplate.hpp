#pragma once

#include <mj/ast/MjStatement.hpp>
#include <mj/ast/MjTypeTemplate.hpp>


class MjClassTypeTemplate : public MjTypeTemplate {
private:
public:


    ///
    /// Constructors
    ///


    constexpr
    MjClassTypeTemplate(
        MjToken template_name,
        MjTemplateParameterList *template_parameter_list,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjTypeTemplate(template_name, template_parameter_list, MjItemKind::CLASS_TYPE_TEMPLATE, tokens)
    {}


    ///
    /// Properties
    ///

};
