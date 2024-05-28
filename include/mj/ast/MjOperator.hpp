#pragma once

#include <mj/ast/MjToken.hpp>


template<class MjOperatorType>
struct MjOperatorTypeValues {
    static constexpr MjOperatorType SET{0}; // _=_
    static constexpr MjOperatorType MUL_SET{0}; // _*=_
    static constexpr MjOperatorType DIV_SET{0}; // _/=_
    static constexpr MjOperatorType MOD_SET{0}; // _%=_
    static constexpr MjOperatorType ADD_SET{0}; // _+=_
    static constexpr MjOperatorType SUB_SET{0}; // _-=_
    static constexpr MjOperatorType LSL_SET{0}; // _>>=_
    static constexpr MjOperatorType ASR_SET{0}; // _<<=_
    static constexpr MjOperatorType LSR_SET{0}; // _>>>=_
    static constexpr MjOperatorType AND_SET{0}; // _&=_
    static constexpr MjOperatorType XOR_SET{0}; // _^=_
    static constexpr MjOperatorType OR_SET{0}; // _|=_



    static constexpr MjOperatorType SCOPE_MEMBER_ACCESS{0};   // T::m
    static constexpr MjOperatorType MEMBER_ACCESS{0};         // a.m
    static constexpr MjOperatorType SUBSCRIPT{0};             // a[b]
    static constexpr MjOperatorType SLICE{0};                 // a[b:c]
    static constexpr MjOperatorType FUNCTION_CALL{0};         // a(...)
    static constexpr MjOperatorType CONSTRUCTOR_CALL{0};      // T(...)
    static constexpr MjOperatorType BITWISE_CAST{0};          // (T: a)
    static constexpr MjOperatorType REFERENCE{0};             // &a
    static constexpr MjOperatorType DEREFERENCE{0};           // *a
    static constexpr MjOperatorType SAFE_DEREFERENCE{0};      // ^a
    static constexpr MjOperatorType NEGATION{0};              // -a
    static constexpr MjOperatorType INVERSION{0};             // ~a
    static constexpr MjOperatorType NOT{0};                   // !a
    static constexpr MjOperatorType POST_INCREMENT{0};        // a++
    static constexpr MjOperatorType POST_DECREMENT{0};        // a--
    static constexpr MjOperatorType SHIFT_LEFT{0};            // a << b
    static constexpr MjOperatorType SHIFT_RIGHT{0};           // a >> b
    static constexpr MjOperatorType SLIDE_LEFT{0};            // a <<< b
    static constexpr MjOperatorType SLIDE_RIGHT{0};           // a >>> b
    static constexpr MjOperatorType MULTIPLICATION{0};        // a * b
    static constexpr MjOperatorType DIVISION{0};              // a / b
    static constexpr MjOperatorType REMAINDER{0};             // a % b
    static constexpr MjOperatorType ADDITION{0};              // a + b
    static constexpr MjOperatorType SUBTRACTION{0};           // a - b
    static constexpr MjOperatorType BITWISE_AND{0};           // a & b
    static constexpr MjOperatorType BITWISE_XOR{0};           // a ^ b
    static constexpr MjOperatorType BITWISE_OR{0};            // a | b
    static constexpr MjOperatorType LOGICAL_AND{0};           // a && b
    static constexpr MjOperatorType LOGICAL_XOR{0};           // a ^^ b
    static constexpr MjOperatorType LOGICAL_OR{0};            // a || b
    static constexpr MjOperatorType EQUAL{0};                 // a == b
    static constexpr MjOperatorType NOT_EQUAL{0};             // a != b
    static constexpr MjOperatorType COMPARISON{0};            // a <=> b
    static constexpr MjOperatorType GREATER_THAN{0};          // a > b
    static constexpr MjOperatorType GREATER_THAN_OR_EQUAL{0}; // a >= b
    static constexpr MjOperatorType LESS_THAN{0};             // a < b
    static constexpr MjOperatorType LESS_THAN_OR_EQUAL{0};    // a <= b
    static constexpr MjOperatorType CONDITIONAL{0};           // a ? b : c
    static constexpr MjOperatorType LAMBDA{0};                // a => b
};


class MjOperatorType : public Enum<MjOperatorType, u8>, public MjOperatorTypeValues<MjOperatorType> {
private:
    static
    constexpr
    struct {
        u8 left_bp;            // The left hand operand binding power
        u8 right_bp;           // The right hand operand binding power
    } DATA[] {
        {21, 20}, // T::m

        {14, 13}, // a.m
        {11,  0}, // a[b]
        {11,  0}, // a[b:c]
        {11,  0}, // a(...)
        {11,  0}, // T(...)
        {11,  0}, // T{...}
        { 0,  9}, // a++
        { 0,  9}, // a--

        { 0,  9}, // &a
        { 0,  9}, // *a
        { 0,  9}, // -a
        { 0,  9}, // ~a
        { 0,  9}, // !a
        { 0,  9}, // ++a
        { 0,  9}, // --a

        { 0,  9}, // a.*b

        { 7,  8}, // a * b
        { 7,  8}, // a / b
        { 7,  8}, // a % b

        { 5,  6}, // a + b
        { 5,  6}, // a - b

        { 5,  6}, // a << b
        { 5,  6}, // a >> b
        { 5,  6}, // a <<< b
        { 5,  6}, // a >>> b

        { 5,  6}, // a <=> b

        { 5,  6}, // a < b
        { 5,  6}, // a <= b
        { 5,  6}, // a > b
        { 5,  6}, // a >= b

        { 5,  6}, // a == b
        { 5,  6}, // a != b

        { 4,  3}, // a & b

        { 4,  3}, // a ^ b

        { 4,  3}, // a | b

        { 4,  3}, // a && b

        { 4,  3}, // a || b

        { 4,  3}, // a ? b : c
        { 2,  1}, // a = b
        { 2,  1}, // a += b
        { 2,  1}, // a -= b
        { 2,  1}, // a *= b
        { 2,  1}, // a /= b
        { 2,  1}, // a %= b
        { 2,  1}, // a <<= b
        { 2,  1}, // a >>= b
        { 2,  1}, // a <<<= b
        { 2,  1}, // a >>>= b
        { 2,  1}, // a &= b
        { 2,  1}, // a ^= b
        { 2,  1}, // a |= b
        { 2,  1}, // a &&= b
        { 2,  1}, // a ||= b

        { 1,  1}, // a => b

        {1, 1}, // a
        {1, 1}, // a
        {1, 1}, // a
        {1, 1}, // a
        {1, 1}, // a
        {1, 1}, // a
        {1, 1}, // a
        {1, 1}, // a
        {1, 1}, // a
    };
public:


    constexpr
    explicit
    MjOperatorType(u8 id) noexcept : Enum(id) {}


    ///
    /// Properties
    ///


    constexpr
    bool is_unary() const noexcept {
        return DATA[_id].left_bp == 0 || DATA[_id].right_bp == 0;
    }


    constexpr
    bool is_binary() const noexcept {
        return is_infix() && !is_ternary();
    }


    constexpr
    bool is_ternary() const noexcept {
        return *this == MjOperatorType::CONDITIONAL || *this == MjOperatorType::SLICE;
    }


    /// Return true if the operator is a unary prefix operator.
    constexpr
    bool is_prefix() const noexcept {
        return DATA[_id].left_bp == 0;
    }


    /// Return true if the operator is a unary postfix operator.
    constexpr
    bool is_postfix() const noexcept {
        return DATA[_id].right_bp == 0;
    }


    /// Return true if the operator is a binary infix operator.
    constexpr
    bool is_infix() const noexcept {
        return DATA[_id].left_bp != 0 && DATA[_id].right_bp != 0;
    }


    /// Return the left binding power of the operator.
    constexpr
    u32 left_bp() const noexcept {
        return DATA[_id].left_bp;
    }


    /// Return the right binding power of the operator.
    constexpr
    u32 right_bp() const noexcept {
        return DATA[_id].right_bp;
    }


    /// Return true if the operator is a left associative.
    constexpr
    bool is_left_associative() const noexcept {
        return DATA[_id].left_bp < DATA[_id].right_bp;
    }


    /// Return true if the operator is a right associative.
    constexpr
    bool is_right_associative() const noexcept {
        return DATA[_id].right_bp < DATA[_id].left_bp;
    }
};
