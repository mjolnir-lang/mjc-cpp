#pragma once

#include <mj/ast/MjStatement.hpp>
#include <mj/ast/MjTypeTemplate.hpp>
#include <mj/ast/MjTemplateDefinition.hpp>


class MjClassTypeTemplateDefinition : public MjTemplateDefinition {
private:
    Vector<MjStatement *> _statements;
public:


    ///
    /// Constructors
    ///


    constexpr
    MjClassTypeTemplateDefinition(Slice<const MjToken> tokens = nullptr) noexcept : MjTemplateDefinition(tokens) {}


    ///
    /// Properties
    ///


    constexpr
    const Vector<MjStatement *> &statements() const noexcept {
        return _statements;
    }


    constexpr
    Vector<MjStatement *> &statements() noexcept {
        return _statements;
    }
};
