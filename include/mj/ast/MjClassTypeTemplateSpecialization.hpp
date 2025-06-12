#pragma once

#include <mj/ast/MjClassTypeTemplate.hpp>
#include <mj/ast/MjTemplateSpecialization.hpp>


class MjClassTypeTemplateSpecialization : public MjTemplateSpecialization {
private:
public:


    ///
    /// Constructors
    ///


    constexpr
    MjClassTypeTemplateSpecialization(
        MjClassTypeTemplate *class_type_template,
        MjTemplateArgumentList *template_argument_list
    ) noexcept :
        MjTemplateSpecialization(
            class_type_template,
            template_argument_list,
            MjItemKind::CLASS_TYPE_TEMPLATE_SPECIALIZATION
        )
    {}


    ///
    /// Properties
    ///

};
