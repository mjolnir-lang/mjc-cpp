#pragma once

#include <mj/ast/MjDefinition.hpp>
#include <mj/ast/MjTemplateArgumentList.hpp>
#include <mj/ast/MjTemplateParameterList.hpp>


/// A type consists of a type definition.
class MjTemplateDefinition : public MjDefinition {
protected:
    MjTemplateParameterList _template_parameter_list;

    // Documentation
    //MjComment _comment;     // The type documentation comment

    // Tokenization
    //const MjToken *_name;        // The type identifier sequence (TODO)

    // Parametrization
    //MjTemplate &_generic;     // The generic type or 'None' if not generic
    //generics;    // The generic type parameters of the type or 'None' if not generic
    //generic_contracts; // The required constraints on the generic type parameters derived from the definition
    // generic methods may be explicit or use most specific equivalence for type paramters
    //specializations; // The specializations of this generic type

    // sum<T>(T &a, T &b);
    // sum<u32>(7.4f, 12); // -> <u32>
    // sum(3f32, 10u64);   // -> <f32>

    // Type System Hierarchy
    //base;        // The base type or 'None' if base
    //derived;     // The derived types

    // Members
    // shared;  // static members (variables, functions, types)
    // members; // member variables
    // methods; // member functions (operators)
    // types;   // member types
    // friends; // permissive declarations
    // private;
    // public;
    // permitted; // friends
    // partners; // friends
    // protected;
    // namespace;
    // exposed; // unscoped definitions (inverse of 'friends')

    // First Pass Representation
    // declaration; // The type declaration


    //MjTemplate(const MjToken *name) noexcept : _name(name) {}


    ///
    /// Constructors
    ///


    constexpr
    MjTemplateDefinition(Slice<const MjToken> tokens = nullptr) noexcept : MjDefinition(tokens) {}


    ///
    /// Destructor
    ///


    virtual
    ~MjTemplateDefinition() = default;
public:


    ///
    /// Properties
    ///


    const MjTemplateParameterList &template_parameter_list() const noexcept {
        return _template_parameter_list;
    }


    MjTemplateParameterList &template_parameter_list() noexcept {
        return _template_parameter_list;
    }
};
