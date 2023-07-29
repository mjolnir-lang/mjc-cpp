#pragma once

#include "mj/ast/MjType.hpp"


// A 'Basic Type' is a named type which is a terminal unit of type expressions,
// upon which, derived types may be declared.
class MjBasicType : public MjType {
public:


    virtual ~MjBasicType() = default;


    virtual const MjTypeName &name() const = 0;


    virtual const MjComment &comment() const = 0;


    virtual const Vector<const MjTemplateArgument *> template_arguments() const = 0;


    bool has_comment() const {
        return !comment().text().is_empty();
    }


    bool is_anonymous() const {
        return name().string().is_empty();
    }


    bool is_generic() {
        return !template_parameters().is_empty();
    }


    bool is_generic() const {
        return !template_arguments().is_empty();
    }
};


#include "mj/ast/type/MjBitfieldType.hpp"
#include "mj/ast/type/MjClassType.hpp"
#include "mj/ast/type/MjEnumerationType.hpp"
#include "mj/ast/type/MjInterfaceType.hpp"
#include "mj/ast/type/MjStructureType.hpp"
#include "mj/ast/type/MjUnionType.hpp"
#include "mj/ast/type/MjVariantType.hpp"
