#pragma once

#include <mj/ast/MjFunctionType.hpp>
#include <mj/ast/MjFunctionArgumentList.hpp>


class MjFunctionTemplate;
class MjBlockStatement;


/// @brief A function is a named expression accepting arguments and returning a result.
class MjFunction : public MjItem {
private:
    MjFunctionType *_type;
    MjBlockStatement *_block_statement;

    u16 _comment_offset;
    u16 _template_offset;
    u16 _name_offset;
    u16 _template_argument_list_offset;
    u16 _parameter_list_offset;
    u16 _return_type_offset;

    u16 _annotations_offset;
    u8 _annotations_size;
public:


    constexpr
    MjFunction(const MjToken *name, Slice<const MjToken> tokens = nullptr) noexcept :
        MjItem(MjItemKind::FUNCTION_TYPE, tokens)
    {}


    ///
    /// Properties
    ///


    constexpr
    bool has_comment() const noexcept {
        return _comment_offset > 0;
    }


    const MjComment &comment() const noexcept {
        return *reinterpret_cast<const MjComment *>(&_items[_comment_offset]);
    }


    MjComment &comment() noexcept {
        return *reinterpret_cast<MjComment *>(&_items[_comment_offset]);
    }


    constexpr
    bool has_annotations() const noexcept {
        return _annotations_size > 0;
    }


    Slice<MjAnnotation *const> annotations() const noexcept {
        return {reinterpret_cast<MjAnnotation *const *>(&_items[_annotations_offset]), _annotations_size};
    }


    Slice<MjAnnotation *> annotations() noexcept {
        return {reinterpret_cast<MjAnnotation **>(&_items[_annotations_offset]), _annotations_size};
    }


    constexpr
    bool has_name() const noexcept {
        return _name_offset != 0;
    }


    const MjToken *name() const noexcept {
        return *reinterpret_cast<const MjToken *const *>(&_items[_name_offset]);
    }


    constexpr
    bool is_anonymous() const noexcept {
        return !has_name();
    }


    constexpr
    bool is_template_specialization() const noexcept {
        return _template_offset > 0;
    }


    MjFunctionTemplate *function_template() const noexcept {
        return *reinterpret_cast<MjFunctionTemplate *const *>(&_items[_template_offset]);
    }


    MjFunctionTemplate *function_template() noexcept {
        return *reinterpret_cast<MjFunctionTemplate **>(&_items[_template_offset]);
    }



    constexpr
    bool has_template_argument_list() const noexcept {
        return _template_argument_list_offset > 0;
    }


    MjTemplateArgumentList *template_argument_list() const noexcept {
        return *reinterpret_cast<MjTemplateArgumentList *const *>(&_items[_template_argument_list_offset]);
    }


    MjTemplateArgumentList *template_argument_list() noexcept {
        return *reinterpret_cast<MjTemplateArgumentList **>(&_items[_template_argument_list_offset]);
    }


    MjFunctionParameterList *parameter_list() const noexcept {
        return *reinterpret_cast<MjFunctionParameterList *const *>(&_items[_parameter_list_offset]);
    }


    MjFunctionParameterList *parameter_list() noexcept {
        return *reinterpret_cast<MjFunctionParameterList **>(&_items[_parameter_list_offset]);
    }


    constexpr
    bool has_return_type() const noexcept {
        return _return_type_offset > 0;
    }


    constexpr
    MjType *return_type() const noexcept {
        return _type ? _type->return_type() : nullptr;
    }


    constexpr
    MjBlockStatement *body() const noexcept {
        return _block_statement;
    }


    bool is_deterministic(const MjFunctionArgumentList &argument_list) const noexcept;


    bool supports_arguments(const MjFunctionArgumentList &argument_list) const noexcept;
};
