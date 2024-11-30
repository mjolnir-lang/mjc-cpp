#include <core/Mutex.hpp>
//#include <system/Time.hpp>


Error Mutex::lock(u32 timeout) const noexcept {
    /*
    u32 start = Time::get_ms();

    while (!try_lock()) {
        if (Time::get_ms() - start > timeout) {
            return false;
        }

        yield();
    }
    */
    return Error::SUCCESS;
}
