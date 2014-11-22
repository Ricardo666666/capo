/*
    The Capo Library
    Code covered by the MIT License

    Author: mutouyun (http://darkc.at)
*/

#pragma once

#include "capo/alloc.hpp"

#include <set> // std::set

namespace capo
{
    template <typename T, class CompT = std::less<T>
                        , class AllocatorT = CAPO_ALLOCATOR_<T>>
    using set = std::set<T, CompT, AllocatorT>;

    template <typename T, class CompT = std::less<T>
                        , class AllocatorT = CAPO_ALLOCATOR_<T>>
    using multiset = std::multiset<T, CompT, AllocatorT>;
}