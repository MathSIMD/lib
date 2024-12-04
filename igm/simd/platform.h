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

#if defined(IGM_FORCE_ARCH_UNKNOWN) || defined(IGM_FORCE_PURE)
#	define IGM_ARCH IGM_ARCH_UNKNOWN
#elif defined(IGM_FORCE_NEON)
#	if __ARM_ARCH >= 8
#		define IGM_ARCH (IGM_ARCH_ARMV8)
#	else
#		define IGM_ARCH (IGM_ARCH_NEON)
#	endif
#	define IGM_FORCE_INTRINSICS
#elif defined(IGM_FORCE_AVX2)
#	define IGM_ARCH (IGM_ARCH_AVX2)
#	define IGM_FORCE_INTRINSICS
#elif defined(IGM_FORCE_AVX)
#	define IGM_ARCH (IGM_ARCH_AVX)
#	define IGM_FORCE_INTRINSICS
#elif defined(IGM_FORCE_SSE42)
#	define IGM_ARCH (IGM_ARCH_SSE42)
#	define IGM_FORCE_INTRINSICS
#elif defined(IGM_FORCE_SSE41)
#	define IGM_ARCH (IGM_ARCH_SSE41)
#	define IGM_FORCE_INTRINSICS
#elif defined(IGM_FORCE_SSSE3)
#	define IGM_ARCH (IGM_ARCH_SSSE3)
#	define IGM_FORCE_INTRINSICS
#elif defined(IGM_FORCE_SSE3)
#	define IGM_ARCH (IGM_ARCH_SSE3)
#	define IGM_FORCE_INTRINSICS
#elif defined(IGM_FORCE_SSE2)
#	define IGM_ARCH (IGM_ARCH_SSE2)
#	define IGM_FORCE_INTRINSICS
#elif defined(IGM_FORCE_SSE)
#	define IGM_ARCH (IGM_ARCH_SSE)
#	define IGM_FORCE_INTRINSICS
#elif defined(IGM_FORCE_INTRINSICS) && !defined(IGM_FORCE_XYZW_ONLY)
#	if defined(__AVX2__)
#		define IGM_ARCH (IGM_ARCH_AVX2)
#	elif defined(__AVX__)
#		define IGM_ARCH (IGM_ARCH_AVX)
#	elif defined(__SSE4_2__)
#		define IGM_ARCH (IGM_ARCH_SSE42)
#	elif defined(__SSE4_1__)
#		define IGM_ARCH (IGM_ARCH_SSE41)
#	elif defined(__SSSE3__)
#		define IGM_ARCH (IGM_ARCH_SSSE3)
#	elif defined(__SSE3__)
#		define IGM_ARCH (IGM_ARCH_SSE3)
#	elif defined(__SSE2__) || defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86_FP)
#		define IGM_ARCH (IGM_ARCH_SSE2)
#	elif defined(__i386__)
#		define IGM_ARCH (IGM_ARCH_X86)
#	elif defined(__ARM_ARCH) && (__ARM_ARCH >= 8)
#		define IGM_ARCH (IGM_ARCH_ARMV8)
#	elif defined(__ARM_NEON)
#		define IGM_ARCH (IGM_ARCH_ARM | IGM_ARCH_NEON)
#	elif defined(__arm__ ) || defined(_M_ARM)
#		define IGM_ARCH (IGM_ARCH_ARM)
#	elif defined(__mips__ )
#		define IGM_ARCH (IGM_ARCH_MIPS)
#	elif defined(__powerpc__ ) || defined(_M_PPC)
#		define IGM_ARCH (IGM_ARCH_PPC)
#	else
#		define IGM_ARCH (IGM_ARCH_UNKNOWN)
#	endif
#else
#	if defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86) || defined(__i386__)
#		define IGM_ARCH (IGM_ARCH_X86)
#	elif defined(__arm__) || defined(_M_ARM)
#		define IGM_ARCH (IGM_ARCH_ARM)
#	elif defined(__powerpc__) || defined(_M_PPC)
#		define IGM_ARCH (IGM_ARCH_PPC)
#	elif defined(__mips__)
#		define IGM_ARCH (IGM_ARCH_MIPS)
#	else
#		define IGM_ARCH (IGM_ARCH_UNKNOWN)
#	endif
#endif

#if IGM_ARCH & IGM_ARCH_AVX2_BIT
#	include <immintrin.h>
#elif IGM_ARCH & IGM_ARCH_AVX_BIT
#	include <immintrin.h>
#elif IGM_ARCH & IGM_ARCH_SSE42_BIT
#	if IGM_COMPILER & IGM_COMPILER_CLANG
#		include <popcntintrin.h>
#	endif
#	include <nmmintrin.h>
#elif IGM_ARCH & IGM_ARCH_SSE41_BIT
#	include <smmintrin.h>
#elif IGM_ARCH & IGM_ARCH_SSSE3_BIT
#	include <tmmintrin.h>
#elif IGM_ARCH & IGM_ARCH_SSE3_BIT
#	include <pmmintrin.h>
#elif IGM_ARCH & IGM_ARCH_SSE2_BIT
#	include <emmintrin.h>
#elif IGM_ARCH & IGM_ARCH_NEON_BIT
#	include "neon.h"
#endif//IGM_ARCH

#if IGM_ARCH & IGM_ARCH_SSE2_BIT
	typedef __m128			igm_f32vec4;
	typedef __m128i			igm_i32vec4;
	typedef __m128i			igm_u32vec4;
	typedef __m128d			igm_f64vec2;
	typedef __m128i			igm_i64vec2;
	typedef __m128i			igm_u64vec2;

	typedef igm_f32vec4		igm_vec4;
	typedef igm_i32vec4		igm_ivec4;
	typedef igm_u32vec4		igm_uvec4;
	typedef igm_f64vec2		igm_dvec2;
#endif

#if IGM_ARCH & IGM_ARCH_AVX_BIT
	typedef __m256d			igm_f64vec4;
	typedef igm_f64vec4		igm_dvec4;
#endif

#if IGM_ARCH & IGM_ARCH_AVX2_BIT
	typedef __m256i			igm_i64vec4;
	typedef __m256i			igm_u64vec4;
#endif

#if IGM_ARCH & IGM_ARCH_NEON_BIT
	typedef float32x4_t			igm_f32vec4;
	typedef int32x4_t			igm_i32vec4;
	typedef uint32x4_t			igm_u32vec4;
#endif
