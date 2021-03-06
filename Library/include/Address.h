#pragma once

#include <cstdint>

class Address
{
public:
    Address() = default;

    Address(const uintptr_t _ptr) : ptr(_ptr)
    {
    }

    Address(const void* _ptr) : ptr(reinterpret_cast<uintptr_t> (_ptr))
    {
    }

    operator uintptr_t() const //NOT explicit
    {
        return ptr;
    }

    explicit operator void* () const
    {
        return reinterpret_cast<void*>(ptr);
    }

    bool isValid() const
    {
        return reinterpret_cast<void*>(ptr) != nullptr;
    }

    uintptr_t get() const
    {
        return ptr;
    }

    template <typename T>
    T get()
    {
        return reinterpret_cast<T>(ptr);
    }

    Address addOffset(const uint32_t offset)
    {
        ptr += offset;
        return *this;
    }

    //Address operator+(const Address& b) {
    //    Address address = Address(this->ptr+b.get());
    //    return address;
    //}

    //Address operator+(const uintptr_t b) {
    //    Address address = Address(this->ptr + b);
    //    return address;
    //}

protected:
    uintptr_t ptr;
};
