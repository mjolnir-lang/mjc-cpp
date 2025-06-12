#pragma once

#include <mj/ast/MjStatement.hpp>


class MjElseStatement : public MjStatement {
private:
    MjStatement *_body;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjElseStatement(
        MjStatement *body,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(MjItemKind::ELSE_STATEMENT, tokens),
        _body(body)
    {}


    constexpr
    MjElseStatement(
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjStatement(MjItemKind::ELSE_STATEMENT, tokens),
        _body(nullptr)
    {}


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
        if (false) {
            return _is_deterministic;
        }

        return _body->is_deterministic();
    }


    constexpr
    bool has_body() const noexcept {
        return _body != nullptr;
    }


    constexpr
    const MjStatement *body() const noexcept {
        return _body;
    }


    constexpr
    MjStatement *body() noexcept {
        return _body;
    }


    ///
    /// Methods
    ///


    void set_body(MjStatement *statement) {
        _body = statement;
    }
};
