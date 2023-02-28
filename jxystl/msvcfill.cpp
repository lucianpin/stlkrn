//
// Copyright (c) Johnny Shaw. All rights reserved.
// 
// File:     jxystl/memory.hpp
// Author:   Johnny Shaw
// Abstract: MSVC fill functionality 
//
// Some MSVC functionality must be implemented for the STL containers to link
// to. I have consciously decided to implement each with care given to the
// operating environment (kernel). This means that code using the STL directly
// and not through the jxylib wrappers might encounter linker errors.
// This is done intentionally as to not introduce a path which may be unsafe
// for the kernel.
//
#include <fltKernel.h>
#include <stdexcept>
#include <system_error>
#include <intrin.h>

namespace std
{

void __cdecl _Xbad_alloc()
{
    KeBugCheckEx(KMODE_EXCEPTION_NOT_HANDLED, 0, 0, 0, 0);
}

void __cdecl _Xinvalid_argument(_In_z_ const char* What)
{
    UNREFERENCED_PARAMETER(What);
    KeBugCheckEx(KMODE_EXCEPTION_NOT_HANDLED, 0, 0, 0, 0);
}

void __cdecl _Xlength_error(_In_z_ const char* What)
{
    UNREFERENCED_PARAMETER(What);
    KeBugCheckEx(KMODE_EXCEPTION_NOT_HANDLED, 0, 0, 0, 0);
}

void __cdecl _Xout_of_range(_In_z_ const char* What)
{
    UNREFERENCED_PARAMETER(What);
    KeBugCheckEx(KMODE_EXCEPTION_NOT_HANDLED, 0, 0, 0, 0);
}

void __cdecl _Xoverflow_error(_In_z_ const char* What)
{
    UNREFERENCED_PARAMETER(What);
    KeBugCheckEx(KMODE_EXCEPTION_NOT_HANDLED, 0, 0, 0, 0);
}

void __cdecl _Xruntime_error(_In_z_ const char* What)
{
    UNREFERENCED_PARAMETER(What);
    KeBugCheckEx(KMODE_EXCEPTION_NOT_HANDLED, 0, 0, 0, 0);
}

void __cdecl _Throw_Cpp_error(int Code)
{
    //
    // FIXME: This should throw a std::system_error but it comes with global
    // allocator requirements. For now we'll throw a faked "system error" as
    // a runtime error. 
    //
    UNREFERENCED_PARAMETER(Code);
    KeBugCheckEx(KMODE_EXCEPTION_NOT_HANDLED, 0, 0, 0, 0);
}

}


extern "C"
int _fltused = 0;

#pragma warning(push)
#pragma warning(disable: 4510 4512 4610) // This type can never be instantiated
struct __std_type_info_data
{
    char const* _UndecoratedName;
    char const  _DecoratedName[1];
};
#pragma warning(pop)

// std_type_info.cpp
extern "C"
int __cdecl __std_type_info_compare(
    _In_ __std_type_info_data const* Lhs,
    _In_ __std_type_info_data const* Rhs 
    )
{
    if (Lhs == Rhs)
    {
        return 0;
    }

    //
    // Added assurance checks here...
    //
    NT_ASSERT((Lhs != nullptr) && (Rhs != nullptr));
    if ((Lhs == nullptr) && (Rhs != nullptr))
    {
        return -1;
    }
    if ((Lhs != nullptr) && (Rhs == nullptr))
    {
        return 1;
    }

    //
    // Now do the compare.
    //
    return strcmp(Lhs->_DecoratedName + 1, Rhs->_DecoratedName + 1);
}

extern "C"
__declspec(noreturn) 
void __cdecl terminate() throw()
{
    NT_ASSERT(false);
    abort();
}

extern "C"
__declspec(noreturn) 
void __cdecl abort()
{
    NT_ASSERT(false);
    KeBugCheckEx(
        static_cast<ULONG>(STATUS_DRIVER_PROCESS_TERMINATED),
        static_cast<ULONG_PTR>(0ull + reinterpret_cast<ULONG_PTR>(_ReturnAddress())),
        static_cast<ULONG_PTR>(0ull + reinterpret_cast<ULONG_PTR>(_AddressOfReturnAddress())),
        0, 
        0);
}
