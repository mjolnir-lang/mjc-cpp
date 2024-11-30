#pragma once

#include <mj/ast/MjType.hpp>
#include <core/UnmanagedBox.hpp>


class MjStructureTypeTemplate;
class MjTypeTemplate;
class MjTemplateArgumentList;
class MjFunctionArgumentList;
class MjVariable;
class MjMethod;
class MjFunction;


class MjStructureType : public MjType {
private:
    UnmanagedBox<u8> _data;

    u16 _comment_offset;
    u16 _template_offset;
    u16 _name_offset;
    u16 _template_argument_list_offset;

    u16 _annotations_offset;
    u8 _annotations_size;

    u16 _members_offset;
    u16 _members_size;

    u16 _variables_offset;
    u16 _variables_size;

    u16 _methods_offset;
    u16 _methods_size;

    u16 _operators_offset;
    u16 _operators_size;

    u16 _functions_offset;
    u16 _functions_size;

    u16 _constructors_offset;
    u16 _constructors_size;
    u16 _destructor_offset;

    u16 _types_offset;
    u16 _types_size;

    u16 _type_templates_offset;
    u16 _type_templates_size;
public:


    ///
    /// Constructors
    ///


    MjStructureType() noexcept : MjType(MjTypeKind::STRUCTURE) {}


    ///
    /// Properties
    ///


    /// @brief Return true if the type has a comment.
    constexpr
    bool has_comment() const noexcept {
        return _comment_offset > 0;
    }


    const MjComment &comment() const noexcept {
        return *reinterpret_cast<const MjComment *>(&_data[_comment_offset]);
    }


    MjComment &comment() noexcept {
        return *reinterpret_cast<MjComment *>(&_data[_comment_offset]);
    }


    constexpr
    bool has_annotations() const noexcept {
        return _annotations_size > 0;
    }


    Slice<MjAnnotation *const> annotations() const noexcept {
        return {reinterpret_cast<MjAnnotation *const *>(&_data[_annotations_offset]), _annotations_size};
    }


    Slice<MjAnnotation *> annotations() noexcept {
        return {reinterpret_cast<MjAnnotation **>(&_data[_annotations_offset]), _annotations_size};
    }


    constexpr
    bool has_name() const noexcept {
        return _name_offset != 0;
    }


    const MjToken *name() const noexcept {
        return *reinterpret_cast<const MjToken *const *>(&_data[_name_offset]);
    }


    constexpr
    bool is_anonymous() const noexcept {
        return !has_name();
    }


    constexpr
    bool is_template_specialization() const noexcept {
        return has_template_argument_list();
    }


    constexpr
    bool has_template_argument_list() const noexcept {
        return _template_argument_list_offset > 0;
    }


    MjTemplateArgumentList *template_argument_list() const noexcept {
        return *reinterpret_cast<MjTemplateArgumentList *const *>(&_data[_template_argument_list_offset]);
    }


    MjTemplateArgumentList *template_argument_list() noexcept {
        return *reinterpret_cast<MjTemplateArgumentList **>(&_data[_template_argument_list_offset]);
    }


    constexpr
    bool has_constructors() const noexcept {
        return _constructors_size > 0;
    }


    Slice<MjFunction *const> constructors() const noexcept {
        return {reinterpret_cast<MjFunction *const *>(&_data[_constructors_offset]), _constructors_size};
    }


    Slice<MjFunction *> constructors() noexcept {
        return {reinterpret_cast<MjFunction **>(&_data[_constructors_offset]), _constructors_size};
    }


    constexpr
    bool has_destructor() const noexcept {
        return _destructor_offset > 0;
    }


    MjFunction *destructor() const noexcept {
        return *reinterpret_cast<MjFunction *const *>(&_data[_destructor_offset]);
    }


    MjFunction *destructor() noexcept {
        return *reinterpret_cast<MjFunction **>(_data[_destructor_offset]);
    }


    Slice<MjVariable *const> members() const noexcept {
        return {reinterpret_cast<MjVariable *const *>(&_data[_members_offset]), _members_size};
    }


    Slice<MjVariable *> members() noexcept {
        return {reinterpret_cast<MjVariable **>(&_data[_members_offset]), _members_size};
    }


    Slice<MjMethod *const> methods() const noexcept {
        return {reinterpret_cast<MjMethod *const *>(&_data[_methods_offset]), _methods_size};
    }


    Slice<MjMethod *> methods() noexcept {
        return {reinterpret_cast<MjMethod **>(&_data[_methods_offset]), _methods_size};
    }


    Slice<MjVariable *const> variables() const noexcept {
        return {reinterpret_cast<MjVariable *const *>(&_data[_variables_offset]), _variables_size};
    }


    Slice<MjVariable *> variables() noexcept {
        return {reinterpret_cast<MjVariable **>(&_data[_variables_offset]), _variables_size};
    }


    Slice<MjFunction *const> functions() const noexcept {
        return {reinterpret_cast<MjFunction *const *>(&_data[_functions_offset]), _functions_size};
    }


    Slice<MjFunction *> functions() noexcept {
        return {reinterpret_cast<MjFunction **>(&_data[_functions_offset]), _functions_size};
    }


    Slice<MjFunction *const> operators() const noexcept {
        return {reinterpret_cast<MjFunction *const *>(&_data[_operators_offset]), _operators_size};
    }


    Slice<MjFunction *> operators() noexcept {
        return {reinterpret_cast<MjFunction **>(&_data[_operators_offset]), _operators_size};
    }


    constexpr
    bool has_types() const noexcept {
        return _types_offset > 0;
    }


    Slice<MjType *const> types() const noexcept {
        return {reinterpret_cast<MjType *const *>(&_data[_types_offset]), _types_size};
    }


    Slice<MjType *> types() noexcept {
        return {reinterpret_cast<MjType **>(&_data[_types_offset]), _types_size};
    }


    constexpr
    bool has_type_templates() const noexcept {
        return _type_templates_offset > 0;
    }


    Slice<MjTypeTemplate *const> type_templates() const noexcept {
        return {reinterpret_cast<MjTypeTemplate *const *>(&_data[_type_templates_offset]), _type_templates_size};
    }


    Slice<MjTypeTemplate *> type_templates() noexcept {
        return {reinterpret_cast<MjTypeTemplate **>(&_data[_type_templates_offset]), _type_templates_size};
    }



    /// @brief Return the size of the type in bytes.
    u32 size() const noexcept;


    /// @brief Return the alignment of the type in bytes.
    u32 alignment() const noexcept;


    ///
    /// Methods
    ///


    const MjType *find_type(const MjToken *name) const noexcept;


    const MjType *find_type_template(const MjToken *name, const MjTemplateArgumentList &argument_list) const noexcept;


    /// A variable may be a member or a shared member. It may be a constant as well.
    const MjVariable *find_variable(const MjToken *name) const noexcept;


    const MjVariable *find_member(const MjToken *name) const noexcept;


    /// A function may be a method or a shared function.
    const MjFunction *find_function(const MjToken *name, const MjFunctionArgumentList &argument_list) const noexcept;


    const MjMethod *find_method(const MjToken *name, const MjFunctionArgumentList &argument_list) const noexcept;


    /// A method or a function.
    const MjFunction *find_operator(MjOperatorKind kind, const MjFunctionArgumentList &argument_list) const noexcept;
};
