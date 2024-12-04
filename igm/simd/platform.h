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

///////////////////////////////////////////////////////////////////////////////////
// Instruction sets

#define IGM_ARCH_MIPS_BIT   (0x10000000)
#define IGM_ARCH_PPC_BIT    (0x20000000)
#define IGM_ARCH_ARM_BIT    (0x40000000)
#define IGM_ARCH_ARMV8_BIT  (0x01000000)
#define IGM_ARCH_X86_BIT    (0x80000000)

#define IGM_ARCH_SIMD_BIT   (0x00001000)

#define IGM_ARCH_NEON_BIT   (0x00000001)
#define IGM_ARCH_SSE_BIT	(0x00000002)
#define IGM_ARCH_SSE2_BIT	(0x00000004)
#define IGM_ARCH_SSE3_BIT	(0x00000008)
#define IGM_ARCH_SSSE3_BIT	(0x00000010)
#define IGM_ARCH_SSE41_BIT	(0x00000020)
#define IGM_ARCH_SSE42_BIT	(0x00000040)
#define IGM_ARCH_AVX_BIT	(0x00000080)
#define IGM_ARCH_AVX2_BIT	(0x00000100)

#define IGM_ARCH_UNKNOWN	(0)
#define IGM_ARCH_X86		(IGM_ARCH_X86_BIT)
#define IGM_ARCH_SSE		(IGM_ARCH_SSE_BIT | IGM_ARCH_SIMD_BIT | IGM_ARCH_X86)
#define IGM_ARCH_SSE2		(IGM_ARCH_SSE2_BIT | IGM_ARCH_SSE)
#define IGM_ARCH_SSE3		(IGM_ARCH_SSE3_BIT | IGM_ARCH_SSE2)
#define IGM_ARCH_SSSE3		(IGM_ARCH_SSSE3_BIT | IGM_ARCH_SSE3)
#define IGM_ARCH_SSE41		(IGM_ARCH_SSE41_BIT | IGM_ARCH_SSSE3)
#define IGM_ARCH_SSE42		(IGM_ARCH_SSE42_BIT | IGM_ARCH_SSE41)
#define IGM_ARCH_AVX		(IGM_ARCH_AVX_BIT | IGM_ARCH_SSE42)
#define IGM_ARCH_AVX2		(IGM_ARCH_AVX2_BIT | IGM_ARCH_AVX)
#define IGM_ARCH_ARM		(IGM_ARCH_ARM_BIT)
#define IGM_ARCH_ARMV8		(IGM_ARCH_NEON_BIT | IGM_ARCH_SIMD_BIT | IGM_ARCH_ARM | IGM_ARCH_ARMV8_BIT)
#define IGM_ARCH_NEON		(IGM_ARCH_NEON_BIT | IGM_ARCH_SIMD_BIT | IGM_ARCH_ARM)
#define IGM_ARCH_MIPS		(IGM_ARCH_MIPS_BIT)
#define IGM_ARCH_PPC		(IGM_ARCH_PPC_BIT)