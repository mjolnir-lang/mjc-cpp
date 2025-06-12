#pragma once

#include <mj/ast/MjTemplate.hpp>


/// @brief A type template is a template for a type.
class MjTypeTemplate : public MjTemplate {
protected:


    ///
    /// Constructors
    ///


    constexpr
    MjTypeTemplate(
        MjToken template_name,
        MjTemplateParameterList *template_parameter_list,
        MjItemKind item_kind,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjTemplate(template_name, template_parameter_list, item_kind, tokens)
    {}


public:


    ///
    /// Properties
    ///


    ///
    /// Template Properties
    ///

};
