#pragma once

#include <mj/ast/MjDirective.hpp>
#include <mj/ast/MjModule.hpp>


/// A special directive used to declare a dependency on another module.
class MjImportDirective : public MjDirective {
private:
    MjModule *_module;
public:


    static
    constexpr
    MjItemKind item_kind() noexcept {
        return MjItemKind::IMPORT_DIRECTIVE;
    }


    ///
    /// Constructors
    ///


    constexpr
    MjImportDirective(MjModule *module, Slice<const MjToken> tokens = nullptr) noexcept :
        MjDirective(item_kind(), tokens), _module(module)
    {}


    ///
    /// Destructor
    ///


    ~MjImportDirective() = default;


    ///
    /// Properties
    ///


    constexpr
    bool has_module() const noexcept {
        return _module != nullptr;
    }


    constexpr
    const MjModule *module() const noexcept {
        return _module;
    }


    constexpr
    MjModule *module() noexcept {
        return _module;
    }


    ///
    /// Methods
    ///


    constexpr
    void set_module(MjModule *module) {
        _module = module;
    }
};
