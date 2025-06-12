#pragma once

#include <mj/ast/MjItem.hpp>
#include <mj/ast/MjTemplate.hpp>
#include <mj/ast/MjTemplateArgumentList.hpp>


/// A type consists of a type definition.
class MjTemplateSpecialization : public MjItem {
protected:
    MjTemplate *_template;
    MjTemplateArgumentList *_template_argument_list;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjTemplateSpecialization(
        MjTemplate *base_template,
        MjTemplateArgumentList *template_argument_list,
        MjItemKind item_kind
    ) noexcept :
        MjItem(item_kind),
        _template_argument_list(template_argument_list),
        _template(base_template)
    {}


    ///
    /// Properties
    ///


    const MjTemplateArgumentList *template_argument_list() const noexcept {
        return _template_argument_list;
    }


    MjTemplateArgumentList *template_argument_list() noexcept {
        return _template_argument_list;
    }
};
