#pragma once

#include <core/Common.hpp>

#include <type_traits>


#ifdef TYPE_TEMPLATE
template<class T>
struct Type {
    template<class... Args>
    struct List;


    template<class U>
    static constexpr bool is_equal = std::is_same_v<T, U>;

    static constexpr bool is_const = std::is_const_v<T>;
    static constexpr bool is_volatile = std::is_volatile_v<T>;

    static constexpr bool is_void = std::is_void_v<T>;
    static constexpr bool is_null_pointer = std::is_null_pointer_v<T>;
    static constexpr bool is_integral = std::is_integral_v<T>;
    static constexpr bool is_floating_point = std::is_floating_point_v<T>;
    static constexpr bool is_array = std::is_array_v<T>;
    static constexpr bool is_pointer = std::is_pointer_v<T>;
    static constexpr bool is_lvalue_reference = std::is_lvalue_reference_v<T>;
    static constexpr bool is_rvalue_reference = std::is_rvalue_reference_v<T>;
    static constexpr bool is_member_object_pointer = std::is_member_object_pointer_v<T>;
    static constexpr bool is_member_function_pointer = std::is_member_function_pointer_v<T>;
    static constexpr bool is_enum = std::is_enum_v<T>;
    static constexpr bool is_union = std::is_union_v<T>;
    static constexpr bool is_class = std::is_class_v<T>;
    static constexpr bool is_function = std::is_function_v<T>;



    using remove_reference = std::remove_reference_t<T>;
    using Ref = remove_reference &;
    using RvRef = remove_reference &&;


    static
    constexpr
    T &&forward(Ref type) noexcept {
        return std::forward<T>(type);
    }


    static
    constexpr
    T &&forward(RvRef type) noexcept {
        return std::forward<T>(type);
    }


    Type() = delete;
};
#else
namespace Type {
    template<class... Args>
    struct List;


    ///
    /// Type Properties
    ///


    /// Return true if T is const-qualified.
    template<class T> inline constexpr bool is_const = std::is_const_v<T>;


    /// Return true if T is volatile-qualified.
    template<class T> inline constexpr bool is_volatile = std::is_volatile_v<T>;


    /// Return true if T is trivial.
    template<class T> inline constexpr bool is_trivial = std::is_trivial_v<T>;


    /// Return true if T is trivially copyable.
    template<class T> inline constexpr bool is_trivially_copyable = std::is_trivially_copyable_v<T>;


    /// Return true if T is a standard-layout type.
    template<class T> inline constexpr bool is_standard_layout = std::is_standard_layout_v<T>;


    /// Return true if T is a plain-old data (POD) type.
    template<class T> inline constexpr bool is_pod = std::is_pod_v<T>;


    /// Return true if every bit in T's object representation contributes to its value.
    template<class T> inline constexpr bool has_unique_object_representations = std::has_unique_object_representations_v<T>;


    /// Return true if T is a class (but not union) type and has no non-static data members.
    template<class T> inline constexpr bool is_empty = std::is_empty_v<T>;


    /// Return true if T is a polymorphic class type.
    template<class T> inline constexpr bool is_polymorphic = std::is_polymorphic_v<T>;


    /// Return true if T is an abstract class type.
    template<class T> inline constexpr bool is_abstract = std::is_abstract_v<T>;


    /// Return true if T is a final class type.
    template<class T> inline constexpr bool is_final = std::is_final_v<T>;


    /// Return true if T is an aggregate type.
    template<class T> inline constexpr bool is_aggregate = std::is_aggregate_v<T>;


    /// Return true if T is a signed arithmetic type.
    template<class T> inline constexpr bool is_signed = std::is_signed_v<T>;


    /// Return true if T is an unsigned arithmetic type.
    template<class T> inline constexpr bool is_unsigned = std::is_unsigned_v<T>;


    /// Return true if T is an array type of known bound.
    template<class T> inline constexpr bool is_bounded_array = std::is_bounded_array_v<T>;


    /// Return true if T is an array type of unknown bound.
    template<class T> inline constexpr bool is_unbounded_array = std::is_unbounded_array_v<T>;


    ///
    /// Primary Type Categories
    ///


    /// Return true if T is void.
    template<class T> inline constexpr bool is_void = std::is_void_v<T>;


    /// Return true if T is nullptr.
    template<class T> inline constexpr bool is_null_pointer = std::is_null_pointer_v<T>;


    /// Return true if T is an integral type.
    template<class T> inline constexpr bool is_integral = std::is_integral_v<T>;

    /// Return true if T is a floating point type.
    template<class T> inline constexpr bool is_floating_point = std::is_floating_point_v<T>;

    /// Return true if T is an array.
    template<class T> inline constexpr bool is_array = std::is_array_v<T>;

    /// Return true if T is a pointer type.
    template<class T> inline constexpr bool is_pointer = std::is_pointer_v<T>;

    /// Return true if T is an lvalue reference.
    template<class T> inline constexpr bool is_lvalue_reference = std::is_lvalue_reference_v<T>;

    /// Return true if T is an rvalue reference.
    template<class T> inline constexpr bool is_rvalue_reference = std::is_rvalue_reference_v<T>;

    /// Return true if T is a member object pointer.
    template<class T> inline constexpr bool is_member_object_pointer = std::is_member_object_pointer_v<T>;

    /// Return true if T is a member function pointer.
    template<class T> inline constexpr bool is_member_function_pointer = std::is_member_function_pointer_v<T>;


    ///
    /// Composite Type Categories
    ///


    /// Return true if T is an enum.
    template<class T> inline constexpr bool is_enum = std::is_enum_v<T>;

    /// Return true if T is a union.
    template<class T> inline constexpr bool is_union = std::is_union_v<T>;

    /// Return true if T is a class.
    template<class T> inline constexpr bool is_class = std::is_class_v<T>;

    /// Return true if T is a function.
    template<class T> inline constexpr bool is_function = std::is_function_v<T>;



    ///
    /// Type Relationships
    ///


    /// Return true if both types are the same.
    template<class T, class U> inline constexpr bool is_same = std::is_same_v<T, U>;
    template<class T, class U> inline constexpr bool is_equal = std::is_same_v<T, U>;


    /// Return true if T is a base of the other type.
    template<class T, class U> inline constexpr bool is_base_of = std::is_base_of_v<T, U>;


    /// Return true if T can be converted to the other type.
    template<class T, class U> inline constexpr bool is_convertible = std::is_convertible_v<T, U>;


    /// Return true if T can be converted to the other type.
    template<class T, class U> inline constexpr bool is_nothrow_convertible = std::is_nothrow_convertible_v<T, U>;


    /// checks if two types are layout-compatible
    template<class T, class U> inline constexpr bool is_layout_compatible = std::is_layout_compatible_v<T, U>;


    /// Return true if T is a pointer-interconvertible (initial) base of another type.
    template<class T, class U> inline constexpr bool is_pointer_interconvertible_base_of = std::is_pointer_interconvertible_base_of_v<T, U>;


    /// Return true if T can be invoked (as if by std::invoke) with the given argument types .
    //template<class From, class To> inline constexpr bool is_invocable = std::is_invocable<From, To>;
    //template<class From, class To> inline constexpr bool is_invocable_r = std::is_invocable_r<From, To>;
    //template<class From, class To> inline constexpr bool is_nothrow_invocable = std::is_nothrow_invocable<From, To>;
    //template<class From, class To> inline constexpr bool is_nothrow_invocable_r = std::is_nothrow_invocable_r<From, To>;


    ///
    /// Misc
    ///


    template<class T> using remove_reference = std::remove_reference_t<T>;
    template<class T> using Ref = remove_reference<T> &;
    template<class T> using RvRef = remove_reference<T> &&;


    template<class T>
    constexpr
    Type::remove_reference<T> &&forward(Type::remove_reference<T> &type) noexcept {
        return std::forward<T>(type);
    }


    template<class T>
    constexpr
    Type::remove_reference<T> &&forward(Type::remove_reference<T> &&type) noexcept {
        return std::forward<T>(type);
    }
};
#endif


#include <core/Where.hpp>
