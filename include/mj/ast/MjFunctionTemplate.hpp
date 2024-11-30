#pragma once

#include <mj/ast/MjTemplate.hpp>
#include <mj/ast/template/MjFunctionTypeTemplate.hpp>


/// @brief A function template is a template of a function.
class MjFunctionTemplate : public MjTemplate {
protected:
    MjFunctionTypeTemplate *_type_template;
public:


    ///
    /// Properties
    ///


    /// @brief Return true if the type is 'const' qualified.
    bool is_const() const noexcept {
        return false;
    }


    /// \brief Return true if the type is 'volatile' qualified.
    bool is_volatile() const noexcept {
        return false;
    }


    ///
    /// Derived Properties
    ///


    /// @brief Return the size of the type in bytes.
    u32 size() const noexcept {
        return 0;
    }


    /// @brief Return the alignment of the type in bytes.
    u32 alignment() const noexcept {
        return 0;
    }
};
