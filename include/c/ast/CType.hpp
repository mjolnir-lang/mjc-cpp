#pragma once

#include <c/ast/CComment.hpp>
#include <c/ast/COperator.hpp>
#include <c/ast/CFunction.hpp>
#include <c/ast/CVariable.hpp>


/*

foo is array of array of 8 pointer to pointer to function returning pointer to array of 7 pointer to char

// C/C++ type with name
char *(*(**foo[][8])())[7];

// C/C++ type followed by name
char *(*(**[][8])())[7] foo;

// linear type followed by name
char *[7]*()**[8][] foo;



// C/C++ type with name with multiple return
((int, int *)(*)(), char *(*)[7])(**foo[][8])();

// linear type followed by name with multiple return
((int, int *)()*, char *[7]*)()**[8][] foo;
*/






#include <core/Enum.hpp>


template<class CTypeType>
struct CTypeTypeValues {
    static constexpr CTypeType VOID{0};
    static constexpr CTypeType ARRAY{1};
    static constexpr CTypeType FUNCTION{2};
    static constexpr CTypeType POINTER{3};
    static constexpr CTypeType STRUCTURE{4};
    static constexpr CTypeType UNION{5};
    static constexpr CTypeType ENUMERATION{6};
};


class CTypeType : public Enum<u8>, public CTypeTypeValues<CTypeType> {
public:


    constexpr
    explicit
    CTypeType(u8 id) noexcept : Enum(id) {}


    constexpr
    bool is_basic() noexcept {
        return _id;
    }


    constexpr
    bool is_derived() noexcept {
        return _id;
    }


    constexpr
    bool is_builtin() noexcept {
        return _id;
    }
};







struct CTypeFlags {
    u32 is_const : 1;
    u32 is_volatile : 1;
    u32 is_safe : 1;
};


/// @brief An `CTypeName` consists of a name.
class CTypeName {
private:
    const CToken &identifier_;
public:


    CTypeName(
        const CToken &identifier
    ) :
        identifier_(identifier)
    {}
};


/// @brief An `CType` is defines the properties of an `CObject`.
class CType {
    CTypeType _type;
protected:
    static const Vector<CMember *> MEMBERS;
    static const Vector<COperator *> OPERATORS;
public:


    virtual ~CType() = default;


    /// @brief Return the size of the type in bytes.
    CTypeType type() const noexcept {
        return _type;
    }


    /// @brief Return the size of the type in bytes.
    virtual u32 size() const = 0;


    /// @brief Return the alignment of the type in bytes.
    virtual u32 alignment() const = 0;


    /// @brief Return true if the type is 'const' qualified.
    virtual bool is_const() const = 0;


    /// \brief Return true if the type is 'volatile' qualified.
    virtual bool is_volatile() const = 0;


    /// @brief Return the list of member variables defined by the type.
    virtual const Vector<CMember *> &members() const {
        return MEMBERS;
    }


    /// @brief Return the list of operators defined by the type.
    virtual const Vector<COperator *> &operators() const {
        return OPERATORS;
    }


    virtual const CScope &shared() const = 0;


    /// @brief Return the 'const' qualified derivation of the type.
    virtual const CType &const_qualified_derivation() const = 0;


    /// @brief Return the 'volatile' qualified derivation of the type.
    virtual const CType &volatile_qualified_derivation() const = 0;
};


#include <c/ast/CBasicType.hpp>
#include <c/ast/CDerivedType.hpp>
