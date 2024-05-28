#pragma once

#include <mj/ast/MjToken.hpp>


using MjAnnotationArgumentList = Vector<const MjToken *>;


template<class MjAnnotationType>
struct MjAnnotationTypeValues {
    static constexpr MjAnnotationType API{0};        // `@api(MAJOR.MINOR)`
    static constexpr MjAnnotationType DEPRECATED{0}; // `@deprecated(MAJOR)`
    static constexpr MjAnnotationType INTERNAL{0};   // `@internal`
    static constexpr MjAnnotationType SHARED{0};     // `@shared`
    static constexpr MjAnnotationType DEBUG{0};      // `@debug`
    static constexpr MjAnnotationType IGNORED{0};    // `@ignored`
};


class MjAnnotationType : public Enum<MjAnnotationType, u8>, public MjAnnotationTypeValues<MjAnnotationType> {
public:


    constexpr
    explicit
    MjAnnotationType(u8 id) noexcept : Enum(id) {}


    static
    MjAnnotationType
};


/// @brief An `MjAnnotation` is a source code annotation attached to AST objects.
class MjAnnotation {
private:
    const MjToken *_name;
    MjAnnotationArgumentList _argument_list;
public:


    MjAnnotation(const MjToken *name) : _name(name) {}


    MjAnnotation(const MjToken *name, MjAnnotationArgumentList argument_list) :
        _name(name), _argument_list(argument_list)
    {}
};
