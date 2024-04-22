
#ifdef DEBUG
#define LOG(msg, str) (std::cout << msg << str)
#else
#define LOG(msg, str) ((void)0)
#endif
#include <cstdlib>
#include <iostream>
#include <string.h>

char* empty_string = nullptr;

struct StringPtr {
public:
    StringPtr(const char* value)
        : ptr(strdup(value))
    {
    }

    StringPtr() = default;
    StringPtr(StringPtr& other)
        : ptr(other.ptr)
        , shared(true)
    {
        if (other.ptr != empty_string) {
            shared = true;
            other.shared = true;
        }
    }

    // move constructor
    StringPtr(StringPtr&& other)
    {
        *this = std::move(other);
    }

    // copy assignment operators (move assignment)
    StringPtr& operator=(StringPtr&& other)
    {
        freeIfNotShared();
        ptr = other.ptr;
        shared = other.shared;
        other.ptr = empty_string;
        return *this;
    }

    StringPtr& operator=(char* value)
    {
        freeIfNotShared();
        ptr = value;
        shared = false;
        return *this;
    }

    StringPtr& operator=(const char* value)
    {
        freeIfNotShared();
        ptr = strdup(value);
        shared = false;
        return *this;
    }

    void freeIfNotShared()
    {
        if (!shared && ptr != empty_string) {
            LOG("\nFree string: ", ptr);
            free(ptr);
        }
    }
    
    ~StringPtr()
    {
        freeIfNotShared();
    }
    char* ptr = empty_string;
    bool shared = false;
};

/*
 * Print a smart pointer include counter and value
 */
std::ostream& operator<<(std::ostream& os, const StringPtr& sp)
{
    os << "StringPtr of "
       << "\"" << sp.ptr << "\", " << (sp.shared ? "shared" : "not shared");
    return os;
}
