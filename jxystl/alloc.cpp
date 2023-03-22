//
// Copyright (c) Johnny Shaw. All rights reserved.
// 
// File:     jxystl/alloc.cpp
// Author:   Johnny Shaw
// Abstract: cpp new/delete functions
//
// Default new/delete is intentionally unimplemented! This forces specifying
// the pool type and tags for all allocations.
//
#include <jxy/alloc.hpp>
#include <stdexcept>

void* __cdecl operator new(size_t Size, POOL_TYPE PoolType, ULONG PoolTag) noexcept(false)
{
    if (Size == 0)
    {
        Size = 1;
    }

#pragma warning(push)
#pragma warning(disable : 4996) // FIXME - deprecated function
    void* memory = ExAllocatePoolZero(PoolType, Size, PoolTag);
#pragma warning(pop)
    if (!memory)
    {
        std::_Xbad_alloc();
    }
    return memory;
}

void __cdecl operator delete(void* Memory, POOL_TYPE, ULONG PoolTag) noexcept
{
    if (Memory)
    {
        ExFreePoolWithTag(Memory, PoolTag);
    }
}

void* __cdecl operator new[](size_t Size, POOL_TYPE PoolType, ULONG PoolTag) noexcept(false)
{
    return operator new(Size, PoolType, PoolTag);
}

void __cdecl operator delete[](void* Memory, POOL_TYPE PoolType, ULONG PoolTag) noexcept
{
    return operator delete(Memory, PoolType, PoolTag);
}


// The following delete operators are needed to avoid link error
// LNK2019: unresolved external symbol "void __cdecl operator delete(void *,unsigned __int64)"
// referenced in function "public: void * __cdecl SomeClass::'scalar deleting destructor'(unsigned int)"
// https://github.com/jxy-s/stlkrn/issues/13

void __cdecl operator delete(void* Memory) noexcept
{
    UNREFERENCED_PARAMETER(Memory);
    std::_Xinvalid_argument(nullptr);
}

void __cdecl operator delete(void* Memory, size_t Size) noexcept
{
    UNREFERENCED_PARAMETER(Memory);
    UNREFERENCED_PARAMETER(Size);
    std::_Xinvalid_argument(nullptr);
}
