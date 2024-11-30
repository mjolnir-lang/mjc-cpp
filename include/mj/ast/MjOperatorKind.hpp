#pragma once

#include <core/Enum.hpp>


template<class MjOperatorKind>
struct MjOperatorKindValues {
    static constexpr MjOperatorKind SET{0}; // _=_
    static constexpr MjOperatorKind MUL_SET{0}; // _*=_
    static constexpr MjOperatorKind DIV_SET{0}; // _/=_
    static constexpr MjOperatorKind MOD_SET{0}; // _%=_
    static constexpr MjOperatorKind ADD_SET{0}; // _+=_
    static constexpr MjOperatorKind SUB_SET{0}; // _-=_
    static constexpr MjOperatorKind LSL_SET{0}; // _>>=_
    static constexpr MjOperatorKind ASR_SET{0}; // _<<=_
    static constexpr MjOperatorKind LSR_SET{0}; // _>>>=_
    static constexpr MjOperatorKind AND_SET{0}; // _&=_
    static constexpr MjOperatorKind XOR_SET{0}; // _^=_
    static constexpr MjOperatorKind OR_SET{0}; // _|=_



    static constexpr MjOperatorKind SCOPE_MEMBER_ACCESS{0};   // T::m
    static constexpr MjOperatorKind MEMBER_ACCESS{0};         // a.m
    static constexpr MjOperatorKind SUBSCRIPT{0};             // a[b]
    static constexpr MjOperatorKind SLICE{0};                 // a[b:c]
    static constexpr MjOperatorKind FUNCTION_CALL{0};         // a(...)
    static constexpr MjOperatorKind CONSTRUCTOR_CALL{0};      // T(...)
    static constexpr MjOperatorKind BITWISE_CAST{0};          // (T: a)
    static constexpr MjOperatorKind REFERENCE{0};             // &a
    static constexpr MjOperatorKind DEREFERENCE{0};           // *a
    static constexpr MjOperatorKind SAFE_DEREFERENCE{0};      // ^a
    static constexpr MjOperatorKind NEGATION{0};              // -a
    static constexpr MjOperatorKind INVERSION{0};             // ~a
    static constexpr MjOperatorKind NOT{0};                   // !a
    static constexpr MjOperatorKind POST_INCREMENT{0};        // a++
    static constexpr MjOperatorKind POST_DECREMENT{0};        // a--
    static constexpr MjOperatorKind SHIFT_LEFT{0};            // a << b
    static constexpr MjOperatorKind SHIFT_RIGHT{0};           // a >> b
    static constexpr MjOperatorKind SLIDE_LEFT{0};            // a <<< b
    static constexpr MjOperatorKind SLIDE_RIGHT{0};           // a >>> b
    static constexpr MjOperatorKind MULTIPLICATION{0};        // a * b
    static constexpr MjOperatorKind DIVISION{0};              // a / b
    static constexpr MjOperatorKind REMAINDER{0};             // a % b
    static constexpr MjOperatorKind ADDITION{0};              // a + b
    static constexpr MjOperatorKind SUBTRACTION{0};           // a - b
    static constexpr MjOperatorKind BITWISE_AND{0};           // a & b
    static constexpr MjOperatorKind BITWISE_XOR{0};           // a ^ b
    static constexpr MjOperatorKind BITWISE_OR{0};            // a | b
    static constexpr MjOperatorKind LOGICAL_AND{0};           // a && b
    static constexpr MjOperatorKind LOGICAL_XOR{0};           // a ^^ b
    static constexpr MjOperatorKind LOGICAL_OR{0};            // a || b
    static constexpr MjOperatorKind EQUAL{0};                 // a == b
    static constexpr MjOperatorKind NOT_EQUAL{0};             // a != b
    static constexpr MjOperatorKind COMPARISON{0};            // a <=> b
    static constexpr MjOperatorKind GREATER_THAN{0};          // a > b
    static constexpr MjOperatorKind GREATER_THAN_OR_EQUAL{0}; // a >= b
    static constexpr MjOperatorKind LESS_THAN{0};             // a < b
    static constexpr MjOperatorKind LESS_THAN_OR_EQUAL{0};    // a <= b
    static constexpr MjOperatorKind CONDITIONAL{0};           // a ? b : c
    static constexpr MjOperatorKind LAMBDA{0};                // a => b
};


class MjOperatorKind : public Enum<u8>, public MjOperatorKindValues<MjOperatorKind> {
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
    MjOperatorKind(u8 id) noexcept : Enum(id) {}


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
        return *this == MjOperatorKind::CONDITIONAL || *this == MjOperatorKind::SLICE;
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
