#pragma once

#include <core/Enum.hpp>


template<class MjExpressionType>
struct MjExpressionTypeValues {
    static constexpr MjExpressionType UNINITIALIZED{0};
    static constexpr MjExpressionType NUMBER_LITERAL{1};
    static constexpr MjExpressionType STRING_LITERAL{2};
    static constexpr MjExpressionType VARIABLE{3};
    static constexpr MjExpressionType FUNCTION_CALL{4};
    static constexpr MjExpressionType TYPE_EXPRESSION{5};
};


class MjExpressionType : public Enum<u8>, public MjExpressionTypeValues<MjExpressionType> {
private:
public:


    constexpr
    explicit
    MjExpressionType(u8 id) noexcept : Enum(id) {}
};
