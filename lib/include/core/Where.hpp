#pragma once

#include <core/Type.hpp>


#ifdef WHERE_TEMPLATE
template<class T>
struct Where {

    template<class U>
    using is_equal = std::is_same<T, U>::type;

    using is_const = std::is_const<T>;
    using is_volatile = std::is_volatile<T>;
};
#else
namespace Where {


    ///
    /// Type Properties
    ///


    /// Return true if T is const-qualified.
    template<class T> using is_const = std::is_const<T>;


    /// Return true if T is volatile-qualified.
    template<class T> using is_volatile = std::is_volatile<T>;


    /// Return true if T is trivial.
    template<class T> using is_trivial = std::is_trivial<T>;


    /// Return true if T is trivially copyable.
    template<class T> using is_trivially_copyable = std::is_trivially_copyable<T>;


    /// Return true if T is a standard-layout type.
    template<class T> using is_standard_layout = std::is_standard_layout<T>;


    /// Return true if every bit in T's object representation contributes to its value.
    template<class T> using has_unique_object_representations = std::has_unique_object_representations<T>;


    /// Return true if T is a class (but not union) type and has no non-static data members.
    template<class T> using is_empty = std::is_empty<T>;


    /// Return true if T is a polymorphic class type.
    template<class T> using is_polymorphic = std::is_polymorphic<T>;


    /// Return true if T is an abstract class type.
    template<class T> using is_abstract = std::is_abstract<T>;


    /// Return true if T is a final class type.
    template<class T> using is_final = std::is_final<T>;


    /// Return true if T is an aggregate type.
    template<class T> using is_aggregate = std::is_aggregate<T>;


    /// Return true if T is a signed arithmetic type.
    template<class T> using is_signed = std::is_signed<T>;


    /// Return true if T is an unsigned arithmetic type.
    template<class T> using is_unsigned = std::is_unsigned<T>;


    /// Return true if T is an array type of known bound.
    template<class T> using is_bounded_array = std::is_bounded_array<T>;


    /// Return true if T is an array type of unknown bound.
    template<class T> using is_unbounded_array = std::is_unbounded_array<T>;


    ///
    /// Primary Type Categories
    ///


    /// Return true if T is void.
    template<class T> using is_void = std::is_void<T>;


    /// Return true if T is nullptr.
    template<class T> using is_null_pointer = std::is_null_pointer<T>;


    /// Return true if T is an integral type.
    template<class T> using is_integral = std::is_integral<T>;

    /// Return true if T is a floating point type.
    template<class T> using is_floating_point = std::is_floating_point<T>;

    /// Return true if T is an array.
    template<class T> using is_array = std::is_array<T>;

    /// Return true if T is a pointer type.
    template<class T> using is_pointer = std::is_pointer<T>;

    /// Return true if T is an lvalue reference.
    template<class T> using is_lvalue_reference = std::is_lvalue_reference<T>;

    /// Return true if T is an rvalue reference.
    template<class T> using is_rvalue_reference = std::is_rvalue_reference<T>;

    /// Return true if T is a member object pointer.
    template<class T> using is_member_object_pointer = std::is_member_object_pointer<T>;

    /// Return true if T is a member function pointer.
    template<class T> using is_member_function_pointer = std::is_member_function_pointer<T>;


    ///
    /// Composite Type Categories
    ///


    /// Return true if T is an enum.
    template<class T> using is_enum = std::is_enum<T>;

    /// Return true if T is a union.
    template<class T> using is_union = std::is_union<T>;

    /// Return true if T is a class.
    template<class T> using is_class = std::is_class<T>;

    /// Return true if T is a function.
    template<class T> using is_function = std::is_function<T>;



    ///
    /// Type Relationships
    ///


    /// Return true if both types are the same.
    template<class T, class U> using is_same = std::is_same<T, U>;
    template<class T, class U> using is_equal = std::is_same<T, U>;


    /// Return true if T is a base of the other type.
    template<class T, class Base> using is_base_of = std::is_base_of<Base, T>;
    template<class T, class Base> using is_derived_from = std::derived_from<T, Base>;


    /// Return true if T can be converted to the other type.
    template<class T, class U> using is_convertible = std::is_convertible<T, U>;


    /// Return true if T can be converted to the other type.
    template<class T, class U> using is_nothrow_convertible = std::is_nothrow_convertible<T, U>;


    /// checks if two types are layout-compatible
    template<class T, class U> using is_layout_compatible = std::is_layout_compatible<T, U>;


    /// Return true if T is a pointer-interconvertible (initial) base of another type.
    template<class T, class U> using is_pointer_interconvertible_base_of = std::is_pointer_interconvertible_base_of<T, U>;


    /// Return true if T can be invoked (as if by std::invoke) with the given argument types .
    //template<class From, class To> inline constexpr bool is_invocable = std::is_invocable<From, To>;
    //template<class From, class To> inline constexpr bool is_invocable_r = std::is_invocable_r<From, To>;
    //template<class From, class To> inline constexpr bool is_nothrow_invocable = std::is_nothrow_invocable<From, To>;
    //template<class From, class To> inline constexpr bool is_nothrow_invocable_r = std::is_nothrow_invocable_r<From, To>;




}
#endif
