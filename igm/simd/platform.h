#pragma once

///////////////////////////////////////////////////////////////////////////////////
// Platform

#define IGM_PLATFORM_UNKNOWN 0x00000000
#define IGM_PLATFORM_WINDOWS 0x00010000
#define IGM_PLATFORM_LINUX 0x00020000
#define IGM_PLATFORM_MACOS 0x00040000

#ifdef IGM_FORCE_PLATFORM_UNKNOWN
#define IGM_PLATFORM IGM_PLATFORM_UNKNOWN
#elif defined(_WIN32)
#define IGM_PLATFORM IGM_PLATFORM_WINDOWS
#elif defined(__linux)
#define IGM_PLATFORM IGM_PLATFORM_LINUX
#elif defined(__APPLE__)
#define IGM_PLATFORM IGM_PLATFORM_MACOS
#else
#define IGM_PLATFORM IGM_PLATFORM_UNKNOWN
#endif

///////////////////////////////////////////////////////////////////////////////////
// Compiler

#define IGM_COMPILER_UNKNOWN 0x00000000
#define IGM_COMPILER_MSVC 0x01000000
#define IGM_COMPILER_GCC 0x02000000
#define IGM_COMPILER_CLANG 0x04000000

#ifdef IGM_FORCE_COMPILER_UNKNOWN
#define IGM_COMPILER IGM_COMPILER_UNKNOWN
#elif defined(_MSC_VER)
#define IGM_COMPILER IGM_COMPILER_MSVC
#elif defined(__GNUC__)
#define IGM_COMPILER IGM_COMPILER_GCC
#elif defined(__clang__)
#define IGM_COMPILER IGM_COMPILER_CLANG
#else
#define IGM_COMPILER IGM_COMPILER_UNKNOWN
#endif

