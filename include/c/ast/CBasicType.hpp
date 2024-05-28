#pragma once

#include <c/ast/CType.hpp>


// A 'Basic Type' is a named type which is a terminal unit of type expressions,
// upon which, derived types may be declared.
class CBasicType : public CType {
public:


    virtual ~CBasicType() = default;


    virtual const CTypeName &name() const = 0;


    virtual const CComment &comment() const = 0;


    bool has_comment() const {
        return !comment().text().is_empty();
    }


    bool is_anonymous() const {
        return name().string().is_empty();
    }
};


#include <c/ast/type/CEnumerationType.hpp>
#include <c/ast/type/CStructureType.hpp>
#include <c/ast/type/CUnionType.hpp>
