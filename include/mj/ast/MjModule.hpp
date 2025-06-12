#pragma once

#include <mj/ast/MjType.hpp>
#include <mj/ast/MjTemplate.hpp>
#include <mj/ast/MjFunction.hpp>
#include <mj/ast/MjModuleName.hpp>
#include <mj/MjStringSet.hpp>

#include <filesystem/File.hpp>


/// Modules participate in the module dependency graph for compilation order.
/// They are built from source files and object files.
/// Modules also declare their platform requirements.
class MjModule : public MjDeclaration {
private:
    MjModuleName _name;
public:


    ///
    /// Constructors
    ///


    MjModule(MjModuleName name) noexcept :
        MjDeclaration(),
        _name(name)
    {}


    ///
    /// Properties
    ///


    constexpr
    const FilePath &directory_path() const noexcept {
        return _directory_path;
    }


    constexpr
    bool has_parent() const noexcept {
        return _parent != nullptr;
    }


    constexpr
    const MjModule *parent() const noexcept {
        return _parent;
    }


    constexpr
    MjModule *parent() noexcept {
        return _parent;
    }


    constexpr
    MjModuleName name() const noexcept {
        return _name;
    }


    /// @brief Return the list of member variables defined by the type.
    constexpr
    MjItemIterator<const MjModule> modules() const noexcept {
        return ;
    }


    /// @brief Return the list of member variables defined by the type.
    constexpr
    Vector<MjModule *> &modules() noexcept {
        return ;
    }


    ///
    /// Methods
    ///


};
