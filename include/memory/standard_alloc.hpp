/*
    The Capo Library
    Code covered by the MIT License

    Author: mutouyun (http://darkc.at)
*/

#ifndef CAPO_MEMORY_STANDARD_ALLOC_HPP___
#define CAPO_MEMORY_STANDARD_ALLOC_HPP___

#include "../memory/alloc_concept.hpp"

#include <cstdlib>  // malloc, free, realloc
#include <new>      // placement new
#include <memory>   // std::allocator
#include <cstddef>  // size_t

namespace capo {
namespace use {

struct alloc_malloc
{
    enum { AllocType = alloc_concept::StaticAlloc };

    static size_t remain(void) { return 0; }
    static void clear(void) {}

    static void* alloc(size_t size)
    {
        return (size ? ::malloc(size) : nullptr);
    }
    static void free(void* p, size_t /*size*/)
    {
        if (p != nullptr) ::free(p);
    }
};

struct alloc_new
{
    enum { AllocType = alloc_concept::StaticAlloc };

    static size_t remain(void) { return 0; }
    static void clear(void) {}

    static void* alloc(size_t size)
    {
        return (size ? ::operator new(size, std::nothrow) : nullptr);
    }
    static void free(void* p, size_t /*size*/)
    {
        ::operator delete(p, std::nothrow);
    }
};

struct alloc_std
{
    enum { AllocType = alloc_concept::StaticAlloc };

    static size_t remain(void) { return 0; }
    static void clear(void) {}

    static void* alloc(size_t size)
    {
        if (size)
        {
            std::allocator<char> aa;
            try
            {
                return aa.allocate(size);
            }
            catch(const std::bad_alloc&)
            {
                return nullptr;
            }
        }
        else return nullptr;
    }
    static void free(void* p, size_t size)
    {
        std::allocator<char> aa;
        using ptr_t = std::allocator<char>::pointer;
        aa.deallocate(static_cast<ptr_t>(p), size);
    }
};

} // namespace use
} // namespace capo

#endif // CAPO_MEMORY_STANDARD_ALLOC_HPP___