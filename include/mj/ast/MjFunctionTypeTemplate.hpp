#pragma once

#include <mj/ast/MjTypeTemplate.hpp>


class MjFunctionTypeTemplate : public MjTypeTemplate {
private:
    MjFunctionParameterList _function_parameter_list;
    MjType *_return_type;
public:


    constexpr
    MjFunctionTypeTemplate() noexcept : MjTypeTemplate() {}


    ///
    /// Properties
    ///


    /// @brief Return true if the type is 'const' qualified.
    constexpr
    bool is_const_callable() const noexcept {
        return false;
    }


    /// \brief Return true if the type is 'volatile' qualified.
    constexpr
    bool is_volatile_callable() const noexcept {
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
    }


    /// @brief Return the alignment of the type in bytes.
    constexpr
    u32 alignment() const noexcept {
    }


    ///
    /// Methods
    ///


};
