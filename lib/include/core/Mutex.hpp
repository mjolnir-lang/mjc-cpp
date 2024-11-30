#pragma once

#include <core/Error.hpp>
#include <core/With.hpp>


/// A synchronization primitive for multithreading contexts.
class Mutex {
private:
    mutable u32 _is_locked = 0;
public:


    /// @brief Attempt to lock the mutex and return true if the lock was
    /// acquired.
    /// @return true if the lock was acquired
    Error try_lock() const noexcept {
        u32 failed;

        do {
            u32 value;
            //asm volatile ("LDREX  %0, [%1]" : "=&r"(value) : "r"(&_is_locked) : "cc");
            value = _is_locked;

            if (value != 0) {
                //asm volatile ("CLREX"); // TODO: Unnecessary?
                return Error::FAILURE;
            }

            //asm volatile (
            //    "STREX  %0, %1, [%2] \n"
            //    "DMB                 \n"
            //    : "=&r"(failed)
            //    : "r"(1), "r"(&_is_locked)
            //    : "cc", "memory"
            //);
        } while (failed);

        _is_locked = 1;
        return Error::SUCCESS;
    }


    /// @brief Lock the mutex and block until the lock is acquired.
    void lock() const noexcept {
        while (!try_lock()) {
            //yield();
        }
    }


    /// @brief Lock the mutex and wait until the lock is acquired or the
    /// timeout has expired.
    /// @param timeout The time to wait in milliseconds
    /// @return true if the lock was acquired, false if the timeout expired
    Error lock(u32 timeout) const noexcept;


    /// @brief Unlock the mutex. This may be called even when the mutex is already unlocked.
    void unlock() const noexcept {
        _is_locked = 0;
    }
};


/// @brief A ContextManager<Mutex> object is used to lock a mutex object on
/// initialization and unlock the mutex when it goes out of scope.
template<>
class With<Mutex> {
private:
    const Mutex &_mutex;
public:


    With(const Mutex &mutex) noexcept : _mutex(mutex) {
        _mutex.lock();
    }


    ~With() {
        _mutex.unlock();
    }
};
