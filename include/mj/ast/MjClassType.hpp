#pragma once

#include <mj/ast/MjType.hpp>

class MjClassTypeTemplate;
class MjTemplateArgumentList;
class MjVariable;
class MjMethod;
class MjFunction;


class MjClassType : public MjType {
private:
public:


    ///
    /// Constructors
    ///


    MjClassType() noexcept : MjType(MjTypeKind::CLASS) {}


    ///
    /// Destructor
    ///


    ~MjClassType() {
        for (auto &constructor : constructors()) {
            Object::destroy(constructor);
        }

        if (has_destructor()) {
            Object::destroy(*destructor());
        }
    }


    ///
    /// Methods
    ///


};
