#pragma once

#include <mj/ast/MjBlockStatement.hpp>


class MjDoLoop : public MjStatement {
private:
    MjBlockStatement *_block;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjDoLoop(Slice<const MjToken> tokens = nullptr) noexcept : MjStatement(tokens) {}


    constexpr
    MjDoLoop(MjBlockStatement *block, Slice<const MjToken> tokens = nullptr) noexcept :
        MjStatement(tokens), _block(block)
    {}


    ///
    /// Properties
    ///


    constexpr
    bool is_deterministic() const noexcept final {
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
