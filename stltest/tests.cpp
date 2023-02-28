//
// Copyright (c) Johnny Shaw. All rights reserved.
// 
// File:     stltests/tests.cpp
// Author:   Johnny Shaw
//
#include "tests.hpp"
#include "tests_common.hpp"

namespace jxy::Tests
{

extern void ExceptionTests();
extern void MemoryTests();
extern void LocksTests();
extern void VectorTests();
extern void StringTests();
extern void ThreadTests();
extern void ScopeTests();
extern void MapTests();
extern void DequeTests();
extern void QueueTests();
extern void ListTests();
extern void StackTests();
extern void SetTests();

bool RunTests()
{
    ExceptionTests();
    MemoryTests();
    LocksTests();
    VectorTests();
    StringTests();
    ThreadTests();
    ScopeTests();
    MapTests();
    DequeTests();
    QueueTests();
    ListTests();
    StackTests();
    SetTests();

    return true;
}


}