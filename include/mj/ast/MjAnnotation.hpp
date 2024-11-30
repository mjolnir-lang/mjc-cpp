#pragma once

#include <mj/ast/MjItem.hpp>


using MjAnnotationArgumentList = Vector<const MjToken *>;


template<class MjAnnotationType>
struct MjAnnotationTypeValues {
    static constexpr MjAnnotationType API{0};        // `@api(MAJOR.MINOR)`
    static constexpr MjAnnotationType DEPRECATED{0}; // `@deprecated(MAJOR)`
    static constexpr MjAnnotationType INTERNAL{0};   // `@internal`
    static constexpr MjAnnotationType SHARED{0};     // `@shared`
    static constexpr MjAnnotationType DEBUG{0};      // `@debug`
    static constexpr MjAnnotationType IGNORED{0};    // `@ignored`
    static constexpr MjAnnotationType PURE{0};       // `@pure`
    static constexpr MjAnnotationType OFFSET{0};     // `@offset()`
    static constexpr MjAnnotationType ADDRESS{0};    // `@address()`
    static constexpr MjAnnotationType SIZE{0};       // `@size()`
};


class MjAnnotationType : public Enum<u8>, public MjAnnotationTypeValues<MjAnnotationType> {
public:


    constexpr
    explicit
    MjAnnotationType(u8 id) noexcept : Enum(id) {}
};


/// @brief An annotation is a semantic element attached to definitions and statements.
class MjAnnotation : public MjItem {
private:
    const MjToken *_name;
    MjAnnotationArgumentList _argument_list;
public:


    static
    constexpr
    MjItemKind item_kind() noexcept {
        return MjItemKind::ANNOTATION;
    }


    ///
    /// Constructors
    ///


    MjAnnotation(const MjToken *name) noexcept : MjItem(item_kind()), _name(name) {}


    MjAnnotation(const MjToken *name, MjAnnotationArgumentList argument_list) noexcept :
        MjItem(item_kind()), _name(name), _argument_list(argument_list)
    {}
};
