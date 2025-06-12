#pragma once

#include <mj/ast/MjProgram.hpp>
#include <mj/MjSourceManager.hpp>


class MjItemManager {
private:
    MjSourceManager _source_manager;
public:


    ///
    /// Constructors
    ///


    MjItemManager(const MjItemManager &) = delete;


    ///
    /// Destructor
    ///


    ~MjItemManager() {}


    ///
    /// Operators
    ///


    MjItemManager &operator=(const MjItemManager &) = delete;


    ///
    /// Properties
    ///


    constexpr
    const MjSourceManager &source_manager() const noexcept {
        return _source_manager;
    }


    ///
    /// Methods
    ///


    template<IsMjItem T, class... Args>
    T *new_item(Args... args) noexcept {
        return new T(args...);
    }
};
