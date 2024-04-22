
#ifdef DEBUG
#define LOG(msg, str) (std::cout << msg << str)
#else
#define LOG(msg, str) ((void)0)
#endif
#include <cstdlib>
#include <iostream>
#include <string.h>

class StringPtr {
    char* empty_value = (char*)1;
    mutable char* ptr = empty_value;

public:
    StringPtr(const char* value)
        : ptr(strdup(value))
    {
    }

    StringPtr() = default;
    StringPtr(const StringPtr& other)
    {
        other.make_shared();
        ptr = other.ptr;
    }

    // move constructor
    StringPtr(StringPtr&& other)
        : StringPtr()
    {
        swap(*this, other);
    }

    // copy assignment operators (move assignment)
    StringPtr& operator=(StringPtr&& other)
    {
        swap(*this, other);
        return *this;
    }

    StringPtr& operator=(const StringPtr& other)
    {
        if (&other != this) {
            StringPtr tmp = other;
            swap(*this, tmp);
        }
        return *this;
    }

    void freeIfNotShared()
    {
        if (!shared()) {
            LOG("\nFree string: ", ptr);
            free(ptr);
        }
    }

    ~StringPtr()
    {
        freeIfNotShared();
    }

    char* get() const
    {
        return (char*)((size_t)ptr & ~1);
    }
    bool shared() const
    {
        return ((size_t)ptr & 1);
    }
    void make_shared() const
    {
        ptr = (char*)((size_t)ptr | 1);
    }

    friend void swap(StringPtr& a, StringPtr& b)
    {
        std::swap(a.ptr, b.ptr);
    }
};

/*
 * Print a smart pointer include counter and value
 */
std::ostream& operator<<(std::ostream& os, const StringPtr& sp)
{
    os << "StringPtr of "
       << "\"" << sp.get() << "\", " << (sp.shared() ? "shared" : "not shared");
    return os;
}
