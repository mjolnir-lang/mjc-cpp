#pragma once

#include <mj/ast/MjBlockStatement.hpp>


class MjDoStatement : public MjStatement {
private:
    MjBlockStatement *_block;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjDoStatement(Slice<const MjToken> tokens = nullptr) noexcept : MjStatement(tokens) {}


    constexpr
    MjDoStatement(MjBlockStatement *block, Slice<const MjToken> tokens = nullptr) noexcept :
        MjStatement(tokens), _block(block)
    {}


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
        if (false) {
            return _is_deterministic;
        }

        return _block->is_deterministic();
    }


    constexpr
    bool has_block() const noexcept {
        return _block != nullptr;
    }


    constexpr
    const MjStatement *block() const noexcept {
        return _block;
    }


    constexpr
    MjStatement *block() noexcept {
        return _block;
    }


    ///
    /// Methods
    ///


    void set_block(MjBlockStatement *block_statement) {
        _block = block_statement;
    }
};
