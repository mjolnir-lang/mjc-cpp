#pragma once

#include <mj/ast/MjStatement.hpp>


// A statement is a structured unit of execution.
class MjBlockStatement : public MjStatement {
private:
    Vector<MjStatement *> _statements;
public:


    static
    constexpr
    MjItemKind item_kind() noexcept {
        return MjItemKind::BLOCK_STATEMENT;
    }


    ///
    /// Constructors
    ///


    constexpr
    MjBlockStatement() noexcept : MjStatement(item_kind()) {}


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
        if (false) {
            return _is_deterministic;
        }

        for (const MjStatement *statement : _statements) {
            if (!statement->is_deterministic()) {
                return false;
            }
        }

        return true;
    }


    constexpr
    const Vector<MjStatement *> &statements() const noexcept {
        return _statements;
    }


    constexpr
    Vector<MjStatement *> &statements() noexcept {
        return _statements;
    }
};
