#pragma once

#include <mj/ast/MjType.hpp>
#include <mj/ast/MjTemplate.hpp>
#include <mj/ast/MjFunction.hpp>
#include <mj/MjStringSet.hpp>

#include <filesystem/File.hpp>


/// Modules participate in the module dependency graph for compilation order.
/// They are built from source files and object files.
/// Modules also declare their platform requirements.
class MjModule {
private:
    FilePath _directory_path;
    StringView _name;                // The name
    MjModule *_parent;               // The parent
    Vector<MjModule *> _imports;     // Imported modules
    Vector<MjModule *> _modules;     // Submodules
    Vector<MjType *> _types;         // Defined types
    Vector<MjTemplate *> _templates; // Defined templates (generic types)
    Vector<MjFunction *> _functions; // Defined functions
    MjStringSet strings; // The short strings shared by all files in the module.
public:


    ///
    /// Constructors
    ///


    MjModule(StringView name, MjModule *parent = nullptr) noexcept :
        _name(name), _parent(parent)
    {
        if (_parent == nullptr) {
            _directory_path = FilePath(name);
        } else {
            _directory_path = _parent->directory_path();
            _directory_path.append(name);
        }
    }


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
    StringView name() const noexcept {
        return _name;
    }


    /// @brief Return the list of member variables defined by the type.
    constexpr
    const Vector<MjModule *> &modules() const noexcept {
        return _modules;
    }


    /// @brief Return the list of member variables defined by the type.
    constexpr
    Vector<MjModule *> &modules() noexcept {
        return _modules;
    }


    /// @brief Return the list of member variables defined by the type.
    constexpr
    const Vector<MjType *> &types() const noexcept {
        return _types;
    }


    /// @brief Return the list of member variables defined by the type.
    constexpr
    Vector<MjType *> &types() noexcept {
        return _types;
    }


    /// @brief Return the list of methods defined by the type.
    constexpr
    const Vector<MjFunction *> &functions() const noexcept {
        return _functions;
    }


    /// @brief Return the list of methods defined by the type.
    constexpr
    Vector<MjFunction *> &functions() noexcept {
        return _functions;
    }


    /// @brief Return the list of operators defined by the type.
    constexpr
    const Vector<MjTemplate *> &templates() const noexcept {
        return _templates;
    }


    /// @brief Return the list of operators defined by the type.
    constexpr
    Vector<MjTemplate *> &templates() noexcept {
        return _templates;
    }


    ///
    /// Methods
    ///


};
