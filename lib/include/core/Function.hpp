#pragma once

/*
#include <functional>

template<class T>
using Function = std::function<T>;
*/


#include <core/Type.hpp>

template<class Signature>
class Function;


template<class Ret, class... Args>
class Function<Ret(Args...)> {
private:
    using Signature = Ret(Args...) noexcept;


#define ALT_FUNCTION
#ifdef ALT_FUNCTION
    template<auto method>
    struct MethodWrapper;


    // Specialization for member functions
    template<class T, class... MArgs, Ret (T::*method)(MArgs...) noexcept>
    struct MethodWrapper<method> {
        static
        constexpr
        Ret invoke(T *object, MArgs &&... args) noexcept {
            if constexpr (Type::is_void<Ret>) {
                (object->*method)(std::forward<MArgs>(args)...);
            } else {
                return (object->*method)(std::forward<MArgs>(args)...);
            }
        }
    };


    // Specialization for member functions
    template<class T, class... MArgs, Ret (T::*method)(MArgs...) const noexcept>
    struct MethodWrapper<method> {
        static
        constexpr
        Ret invoke(const T *object, MArgs &&... args) noexcept {
            if constexpr (Type::is_void<Ret>) {
                (object->*method)(std::forward<MArgs>(args)...);
            } else {
                return (object->*method)(std::forward<MArgs>(args)...);
            }
        }
    };


    template<auto method, auto object>
    struct BoundMethodWrapper;


    // Specialization for member functions
    template<class T, Ret (T::*method)(Args...) noexcept, T *object>
    struct BoundMethodWrapper<method, object> {
        static
        constexpr
        Ret invoke(Args &&... args) noexcept {
            if constexpr (Type::is_void<Ret>) {
                (object->*method)(std::forward<Args>(args)...);
            } else {
                return (object->*method)(std::forward<Args>(args)...);
            }
        }
    };


    // Specialization for member functions
    template<class T, Ret (T::*method)(Args...) const noexcept, T *object>
    struct BoundMethodWrapper<method, object> {
        static
        constexpr
        Ret invoke(Args &&... args) noexcept {
            if constexpr (Type::is_void<Ret>) {
                (object->*method)(std::forward<Args>(args)...);
            } else {
                return (object->*method)(std::forward<Args>(args)...);
            }
        }
    };
#endif


    Signature *_function;
public:


    ///
    /// Constructors
    ///


    /// Create a function from a null pointer.
    constexpr
    Function() noexcept : _function(nullptr) {}


    /// Create a function from a null pointer.
    constexpr
    Function(nullptr_t) noexcept : _function(nullptr) {}


    /// Create a function from a function pointer.
    ///
    /// @param function The function to capture
    constexpr
    Function(Signature *function) noexcept : _function(function) {}


#ifdef ALT_FUNCTION


    /// @brief Create a function from a method pointer.
    ///
    /// @param method The method to capture
    template<class T, class... MArgs, class = Where::is_equal<Ret(T *, MArgs...), Ret(Args...)>>
    constexpr
    Function(Ret (T::*method)(MArgs...) noexcept) noexcept :
        _function(&MethodWrapper<method>::invoke)
    {}


    /// @brief Create a function from a constant method pointer.
    ///
    /// @param method The method to capture
    template<class T, class... MArgs, class = Where::is_equal<Ret(T *, MArgs...), Ret(Args...)>>
    constexpr
    Function(Ret (T::*method)(MArgs...) const noexcept) noexcept :
        _function(&MethodWrapper<method>::invoke)
    {}


    /// @brief Create a function from a method pointer and an instance.
    ///
    /// @param method The method to capture
    /// @param object The object instance to capture
    template<class T>
    constexpr
    Function(Ret (T::*method)(Args...) noexcept, T *object) noexcept :
        _function(&BoundMethodWrapper<method, object>::invoke)
    {}


    /// Create a function from a constant method pointer and an instance.
    template<class T>
    constexpr
    Function(Ret (T::*method)(Args...) const noexcept, const T *object) noexcept :
        _function(&BoundMethodWrapper<method, object>::invoke)
    {}
#else


/*
    /// @brief Create a function from a member function pointer.
    ///
    /// @param method The method to capture
    template<class T, class... MArgs>
    requires (Type::is_equal<Ret(T *, MArgs...), Ret(Args...)>)
    constexpr
    Function(Ret (T::*method)(MArgs...) noexcept) noexcept :
        _function(
            []<Ret (T::*method)(MArgs...) noexcept>(T *object, MArgs &&... args) -> Ret {
                if constexpr (Type::is_void<Ret>) {
                    (object->*method)(std::forward<MArgs>(args)...);
                } else {
                    return (object->*method)(std::forward<MArgs>(args)...);
                }
            }.template operator()<method>
        )
    {}


    /// @brief Create a function from a constant member function pointer.
    ///
    /// @param method The method to capture
    template<class T, class... MArgs>
    requires (Type::is_nothrow_convertible<Ret(Args...), Ret(const T *, MArgs...)>)
    constexpr
    Function(Ret (T::*method)(MArgs...) const noexcept) noexcept :
        _function(
            []<Ret (T::*method)(MArgs...) const noexcept>(const T *object, MArgs &&... args) -> Ret {
                if constexpr (Type::is_void<Ret>) {
                    (object->*method)(std::forward<MArgs>(args)...);
                } else {
                    return (object->*method)(std::forward<MArgs>(args)...);
                }
            }.template operator()<method>
        )
    {}

    /// @brief Create a function from a constant member function pointer.
    ///
    /// @param method The method to capture
    template<class T, class... MArgs>
    requires (Type::is_nothrow_convertible<Ret(Args...), Ret(const void *, MArgs...)>)
    constexpr
    Function(Ret (T::*method)(MArgs...) const noexcept) noexcept :
        _function(
            []<Ret (T::*method)(MArgs...) const noexcept>(const void *object, MArgs &&... args) -> Ret {
                if constexpr (Type::is_void<Ret>) {
                    (reinterpret_cast<const T *>(object)->*method)(std::forward<MArgs>(args)...);
                } else {
                    return (reinterpret_cast<const T *>(object)->*method)(std::forward<MArgs>(args)...);
                }
            }.template operator()<method>
        )
    {}

    /// @brief Create a function from a member function pointer and an instance.
    ///
    /// @param method The method to capture
    /// @param object The object instance to capture
    template<class T>
    constexpr
    Function(Ret (T::*method)(Args...) noexcept, T *object) noexcept :
        _function(
            []<Ret (T::*method)(Args...) noexcept, T *object>(Args &&... args) -> Ret {
                if constexpr (Type::is_void<Ret>) {
                    (object->*method)(std::forward<Args>(args)...);
                } else {
                    return (object->*method)(std::forward<Args>(args)...);
                }
            }.template operator()<method, object>
        )
    {}


    /// Create a function from a constant member function pointer and an instance.
    template<class T>
    constexpr
    Function(Ret (T::*method)(Args...) const noexcept, const T *object) noexcept :
        _function(
            []<Ret (T::*method)(Args...) const noexcept, const T *object>(Args &&... args) -> Ret {
                if constexpr (Type::is_void<Ret>) {
                    (object->*method)(std::forward<Args>(args)...);
                } else {
                    return (object->*method)(std::forward<Args>(args)...);
                }
            }.template operator()<method, object>
        )
    {}
*/
#endif

    ///
    /// Type Casts
    ///


    constexpr
    explicit
    operator bool() const noexcept {
        return _function != nullptr;
    }


    constexpr
    operator Signature *() const noexcept {
        return _function;
    }


    ///
    /// Operators
    ///


    constexpr
    Ret operator()(Args... args) const noexcept {
        if constexpr (Type::is_void<Ret>) {
            _function(std::forward<Args>(args)...);
        } else {
            return _function(std::forward<Args>(args)...);
        }
    }
};
