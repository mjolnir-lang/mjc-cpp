#pragma once

#include <std/Common.hpp>


/// An `CStorage` object is a memory backing for compile time emulation and execution as well as for storing raw data.
/// It provides methods for detecting overlap and modification or exclusive access to data. This allows assumptions to be
/// made about the data.
class CStorage {
private:
    CStorage *owner; // If non-null, the storage is managed by the other storage object
    void *data_;      // The storage data
public:


    CStorage(
        u32 size
     ) {
        u8 *ptr;
        Memory::allocate<u8>(ptr, size);
        data_ = ptr;
    }


    CStorage(
        CStorage &owner,
        u32 offset
    ) :
        data_(owner.data<u8>() + offset)
    {}


    ~CStorage() {
        if (!owner) {
            Memory::free(data_);
        }
    }


    template<class T>
    T *data() {
        return data_;
    }


    bool is_owned() const {
        return owner;
    }
};
