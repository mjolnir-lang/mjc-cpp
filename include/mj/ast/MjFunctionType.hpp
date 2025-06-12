#pragma once

#include <mj/ast/MjType.hpp>
#include <mj/ast/MjFunctionParameterList.hpp>


/// A function type.
class MjFunctionType : public MjType {
private:
    MjFunctionParameterList _function_parameter_list;
    MjType *_return_type;
    u32 is_safe : 1;
    u32 is_method : 1;
    u32 is_pure : 1;
    u32 is_const : 1;
    u32 is_variadic : 1;
    u32 is_inline : 1;
public:


    constexpr
    MjFunctionType(
        MjFunctionParameterList function_parameter_list,
        MjType *return_type
    ) noexcept :
        MjType(MjTypeKind::FUNCTION_TYPE), _function_parameter_list(function_parameter_list), _return_type(return_type)
    {}


    ///
    /// Properties
    ///


    /// @brief Return true if the type is 'const' qualified.
    constexpr
    bool is_const_callable() const noexcept {
        return false;
    }


    constexpr
    const MjFunctionParameterList &parameter_list() const noexcept {
        return _function_parameter_list;
    }


    constexpr
    MjFunctionParameterList &parameter_list() noexcept {
        return _function_parameter_list;
    }


    constexpr
    MjType *return_type() const noexcept {
        return _return_type;
    }


    /// @brief Return the size of the type in bytes.
    constexpr
    u32 size() const noexcept {
        return MjPlatform.pointer_size();
    }


    /// @brief Return the alignment of the type in bytes.
    constexpr
    u32 alignment() const noexcept {
        return MjPlatform.pointer_alignment();
    }


    ///
    /// Methods
    ///


};
