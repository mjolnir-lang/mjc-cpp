#pragma once

#include "mj/ast/MjToken.hpp"


enum class MjAnnotationType : u8 {
    API = 0,        // `@api(MAJOR.MINOR)`
    DEPRECATED = 0, // `@deprecated(MAJOR)`
    INTERNAL = 0,   // `@internal`
    SHARED = 0,     // `@shared`
    DEBUG = 0,      // `@debug`
    IGNORED = 0,    // `@ignored`
};


/// @brief An `MjAnnotation` is a source code annotation attatched to AST objects.
class MjAnnotation {
public:


    virtual ~MjAnnotation() = default;
};
