#pragma once

#include <mj/ast/MjTypeTemplate.hpp>


class MjTypeAliasTemplate : public MjTypeTemplate {
private:
    MjType *_target;
public:


    MjTypeAliasTemplate(
        MjType *target,
        Slice<const MjToken> tokens = nullptr
    ) noexcept :
        MjTypeTemplate(MjItemKind::TYPE_ALIAS, tokens),
        _target(target)
    {}


    ///
    /// Properties
    ///


};
