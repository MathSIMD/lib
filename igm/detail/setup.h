#ifndef IGM_SETUP_INCLUDED

#include <cassert>
#include <cstddef>

#define IGM_VERSION_MAJOR 0
#define IGM_VERSION_MINOR 1
#define IGM_VERSION_PATCH 0
#define IGM_VERSION 1000

#define IGM_SETUP_INCLUDED IGM_VERSION


///////////////////////////////////////////////////////////////////////////////////
// Active states

#define IGM_DISABLE 0
#define IGM_ENABLE 1


///////////////////////////////////////////////////////////////////////////////////
// Detect the platform

#include "../simd/platform.h"

///////////////////////////////////////////////////////////////////////////////////
// Build model

#if defined(_M_ARM64) || defined(__LP64__) || defined(_M_X64) || defined(__ppc64__) || defined(__x86_64__)
#	define IGM_MODEL	IGM_MODEL_64
#elif defined(__i386__) || defined(__ppc__) || defined(__ILP32__) || defined(_M_ARM)
#	define IGM_MODEL	IGM_MODEL_32
#else
#	define IGM_MODEL	IGM_MODEL_32
#endif//

#if !defined(IGM_MODEL) && IGM_COMPILER != 0
#	error "IGM_MODEL undefined, your compiler may not be supported by IGM. Add #define IGM_MODEL 0 to ignore this message."
#endif//IGM_MODEL

///////////////////////////////////////////////////////////////////////////////////
// C++ Version

// User defines: IGM_FORCE_CXX98, IGM_FORCE_CXX03, IGM_FORCE_CXX11, IGM_FORCE_CXX14, IGM_FORCE_CXX17, IGM_FORCE_CXX2A

#define IGM_LANG_CXX98_FLAG         (1 << 1)
#define IGM_LANG_CXX03_FLAG         (1 << 2)
#define IGM_LANG_CXX0X_FLAG         (1 << 3)
#define IGM_LANG_CXX11_FLAG         (1 << 4)
#define IGM_LANG_CXX14_FLAG         (1 << 5)
#define IGM_LANG_CXX17_FLAG         (1 << 6)
#define IGM_LANG_CXX20_FLAG         (1 << 7)
#define IGM_LANG_CXXMS_FLAG         (1 << 8)
#define IGM_LANG_CXXGNU_FLAG        (1 << 9)

#define IGM_LANG_CXX98          IGM_LANG_CXX98_FLAG
#define IGM_LANG_CXX03          (IGM_LANG_CXX98 | IGM_LANG_CXX03_FLAG)
#define IGM_LANG_CXX0X          (IGM_LANG_CXX03 | IGM_LANG_CXX0X_FLAG)
#define IGM_LANG_CXX11          (IGM_LANG_CXX0X | IGM_LANG_CXX11_FLAG)
#define IGM_LANG_CXX14          (IGM_LANG_CXX11 | IGM_LANG_CXX14_FLAG)
#define IGM_LANG_CXX17          (IGM_LANG_CXX14 | IGM_LANG_CXX17_FLAG)
#define IGM_LANG_CXX20          (IGM_LANG_CXX17 | IGM_LANG_CXX20_FLAG)
#define IGM_LANG_CXXMS          IGM_LANG_CXXMS_FLAG
#define IGM_LANG_CXXGNU         IGM_LANG_CXXGNU_FLAG

#if (defined(_MSC_EXTENSIONS))
#	define IGM_LANG_EXT IGM_LANG_CXXMS_FLAG
#elif ((IGM_COMPILER & (IGM_COMPILER_CLANG | IGM_COMPILER_GCC)) && (IGM_ARCH & IGM_ARCH_SIMD_BIT))
#	define IGM_LANG_EXT IGM_LANG_CXXMS_FLAG
#else
#	define IGM_LANG_EXT 0
#endif

#if (defined(IGM_FORCE_CXX_UNKNOWN))
#	define IGM_LANG 0
#elif defined(IGM_FORCE_CXX20)
#	define IGM_LANG (IGM_LANG_CXX20 | IGM_LANG_EXT)
#	define IGM_LANG_STL11_FORCED
#elif defined(IGM_FORCE_CXX17)
#	define IGM_LANG (IGM_LANG_CXX17 | IGM_LANG_EXT)
#	define IGM_LANG_STL11_FORCED
#elif defined(IGM_FORCE_CXX14)
#	define IGM_LANG (IGM_LANG_CXX14 | IGM_LANG_EXT)
#	define IGM_LANG_STL11_FORCED
#elif defined(IGM_FORCE_CXX11)
#	define IGM_LANG (IGM_LANG_CXX11 | IGM_LANG_EXT)
#	define IGM_LANG_STL11_FORCED
#elif defined(IGM_FORCE_CXX03)
#	define IGM_LANG (IGM_LANG_CXX03 | IGM_LANG_EXT)
#elif defined(IGM_FORCE_CXX98)
#	define IGM_LANG (IGM_LANG_CXX98 | IGM_LANG_EXT)
#else
#	if IGM_COMPILER & IGM_COMPILER_VC && defined(_MSVC_LANG)
#		if IGM_COMPILER >= IGM_COMPILER_VC15_7
#			define IGM_LANG_PLATFORM _MSVC_LANG
#		elif IGM_COMPILER >= IGM_COMPILER_VC15
#			if _MSVC_LANG > 201402L
#				define IGM_LANG_PLATFORM 201402L
#			else
#				define IGM_LANG_PLATFORM _MSVC_LANG
#			endif
#		else
#			define IGM_LANG_PLATFORM 0
#		endif
#	else
#		define IGM_LANG_PLATFORM 0
#	endif

#	if __cplusplus > 201703L || IGM_LANG_PLATFORM > 201703L
#		define IGM_LANG (IGM_LANG_CXX20 | IGM_LANG_EXT)
#	elif __cplusplus == 201703L || IGM_LANG_PLATFORM == 201703L
#		define IGM_LANG (IGM_LANG_CXX17 | IGM_LANG_EXT)
#	elif __cplusplus == 201402L || __cplusplus == 201406L || __cplusplus == 201500L || IGM_LANG_PLATFORM == 201402L
#		define IGM_LANG (IGM_LANG_CXX14 | IGM_LANG_EXT)
#	elif __cplusplus == 201103L || IGM_LANG_PLATFORM == 201103L
#		define IGM_LANG (IGM_LANG_CXX11 | IGM_LANG_EXT)
#	elif defined(__INTEL_CXX11_MODE__) || defined(_MSC_VER) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#		define IGM_LANG (IGM_LANG_CXX0X | IGM_LANG_EXT)
#	elif __cplusplus == 199711L
#		define IGM_LANG (IGM_LANG_CXX98 | IGM_LANG_EXT)
#	else
#		define IGM_LANG (0 | IGM_LANG_EXT)
#	endif
#endif

///////////////////////////////////////////////////////////////////////////////////
// Has of C++ features

// http://clang.llvm.org/cxx_status.html
// http://gcc.gnu.org/projects/cxx0x.html
// http://msdn.microsoft.com/en-us/library/vstudio/hh567368(v=vs.120).aspx

// Android has multiple STLs but C++11 STL detection doesn't always work #284 #564
#if IGM_PLATFORM == IGM_PLATFORM_ANDROID && !defined(IGM_LANG_STL11_FORCED)
#	define IGM_HAS_CXX11_STL 0
#elif (IGM_COMPILER & IGM_COMPILER_CUDA_RTC) == IGM_COMPILER_CUDA_RTC
#	define IGM_HAS_CXX11_STL 0
#elif (IGM_COMPILER & IGM_COMPILER_HIP)
#	define IGM_HAS_CXX11_STL 0
#elif IGM_COMPILER & IGM_COMPILER_CLANG
#	if (defined(_LIBCPP_VERSION) || (IGM_LANG & IGM_LANG_CXX11_FLAG) || defined(IGM_LANG_STL11_FORCED))
#		define IGM_HAS_CXX11_STL 1
#	else
#		define IGM_HAS_CXX11_STL 0
#	endif
#elif IGM_LANG & IGM_LANG_CXX11_FLAG
#	define IGM_HAS_CXX11_STL 1
#else
#	define IGM_HAS_CXX11_STL ((IGM_LANG & IGM_LANG_CXX0X_FLAG) && (\
		((IGM_COMPILER & IGM_COMPILER_GCC) && (IGM_COMPILER >= IGM_COMPILER_GCC48)) || \
		((IGM_COMPILER & IGM_COMPILER_VC) && (IGM_COMPILER >= IGM_COMPILER_VC12)) || \
		((IGM_PLATFORM != IGM_PLATFORM_WINDOWS) && (IGM_COMPILER & IGM_COMPILER_INTEL) && (IGM_COMPILER >= IGM_COMPILER_INTEL15))))
#endif

// N1720
#if IGM_COMPILER & IGM_COMPILER_CLANG
#	define IGM_HAS_STATIC_ASSERT __has_feature(cxx_static_assert)
#elif IGM_LANG & IGM_LANG_CXX11_FLAG
#	define IGM_HAS_STATIC_ASSERT 1
#else
#	define IGM_HAS_STATIC_ASSERT ((IGM_LANG & IGM_LANG_CXX0X_FLAG) && (\
		((IGM_COMPILER & IGM_COMPILER_CUDA)) || \
		((IGM_COMPILER & IGM_COMPILER_VC)) || \
		((IGM_COMPILER & IGM_COMPILER_HIP))))
#endif

// N1988
#if IGM_LANG & IGM_LANG_CXX11_FLAG
#	define IGM_HAS_EXTENDED_INTEGER_TYPE 1
#else
#	define IGM_HAS_EXTENDED_INTEGER_TYPE (\
		((IGM_LANG & IGM_LANG_CXX0X_FLAG) && (IGM_COMPILER & IGM_COMPILER_VC)) || \
		((IGM_LANG & IGM_LANG_CXX0X_FLAG) && (IGM_COMPILER & IGM_COMPILER_CUDA)) || \
		((IGM_LANG & IGM_LANG_CXX0X_FLAG) && (IGM_COMPILER & IGM_COMPILER_CLANG)) || \
		((IGM_COMPILER & IGM_COMPILER_HIP)))
#endif

// N2672 Initializer lists http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2672.htm
#if IGM_COMPILER & IGM_COMPILER_CLANG
#	define IGM_HAS_INITIALIZER_LISTS __has_feature(cxx_generalized_initializers)
#elif IGM_LANG & IGM_LANG_CXX11_FLAG
#	define IGM_HAS_INITIALIZER_LISTS 1
#else
#	define IGM_HAS_INITIALIZER_LISTS ((IGM_LANG & IGM_LANG_CXX0X_FLAG) && (\
		((IGM_COMPILER & IGM_COMPILER_VC) && (IGM_COMPILER >= IGM_COMPILER_VC15)) || \
		((IGM_COMPILER & IGM_COMPILER_INTEL) && (IGM_COMPILER >= IGM_COMPILER_INTEL14)) || \
		((IGM_COMPILER & IGM_COMPILER_CUDA)) || \
		((IGM_COMPILER & IGM_COMPILER_HIP))))
#endif

// N2544 Unrestricted unions http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2544.pdf
#if IGM_COMPILER & IGM_COMPILER_CLANG
#	define IGM_HAS_UNRESTRICTED_UNIONS __has_feature(cxx_unrestricted_unions)
#elif IGM_LANG & IGM_LANG_CXX11_FLAG
#	define IGM_HAS_UNRESTRICTED_UNIONS 1
#else
#	define IGM_HAS_UNRESTRICTED_UNIONS (IGM_LANG & IGM_LANG_CXX0X_FLAG) && (\
		(IGM_COMPILER & IGM_COMPILER_VC) || \
		((IGM_COMPILER & IGM_COMPILER_CUDA)) || \
		((IGM_COMPILER & IGM_COMPILER_HIP)))
#endif

// N2346
#if IGM_COMPILER & IGM_COMPILER_CLANG
#	define IGM_HAS_DEFAULTED_FUNCTIONS __has_feature(cxx_defaulted_functions)
#elif IGM_LANG & IGM_LANG_CXX11_FLAG
#	define IGM_HAS_DEFAULTED_FUNCTIONS 1
#else
#	define IGM_HAS_DEFAULTED_FUNCTIONS ((IGM_LANG & IGM_LANG_CXX0X_FLAG) && (\
		((IGM_COMPILER & IGM_COMPILER_VC) && (IGM_COMPILER >= IGM_COMPILER_VC12)) || \
		((IGM_COMPILER & IGM_COMPILER_INTEL)) || \
		(IGM_COMPILER & IGM_COMPILER_CUDA)) || \
		((IGM_COMPILER & IGM_COMPILER_HIP)))
#endif

// N2118
#if IGM_COMPILER & IGM_COMPILER_CLANG
#	define IGM_HAS_RVALUE_REFERENCES __has_feature(cxx_rvalue_references)
#elif IGM_LANG & IGM_LANG_CXX11_FLAG
#	define IGM_HAS_RVALUE_REFERENCES 1
#else
#	define IGM_HAS_RVALUE_REFERENCES ((IGM_LANG & IGM_LANG_CXX0X_FLAG) && (\
		((IGM_COMPILER & IGM_COMPILER_VC)) || \
		((IGM_COMPILER & IGM_COMPILER_CUDA)) || \
		((IGM_COMPILER & IGM_COMPILER_HIP))))
#endif

// N2437 http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2437.pdf
#if IGM_COMPILER & IGM_COMPILER_CLANG
#	define IGM_HAS_EXPLICIT_CONVERSION_OPERATORS __has_feature(cxx_explicit_conversions)
#elif IGM_LANG & IGM_LANG_CXX11_FLAG
#	define IGM_HAS_EXPLICIT_CONVERSION_OPERATORS 1
#else
#	define IGM_HAS_EXPLICIT_CONVERSION_OPERATORS ((IGM_LANG & IGM_LANG_CXX0X_FLAG) && (\
		((IGM_COMPILER & IGM_COMPILER_INTEL) && (IGM_COMPILER >= IGM_COMPILER_INTEL14)) || \
		((IGM_COMPILER & IGM_COMPILER_VC) && (IGM_COMPILER >= IGM_COMPILER_VC12)) || \
		((IGM_COMPILER & IGM_COMPILER_CUDA)) || \
		((IGM_COMPILER & IGM_COMPILER_HIP))))
#endif

// N2258 http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2258.pdf
#if IGM_COMPILER & IGM_COMPILER_CLANG
#	define IGM_HAS_TEMPLATE_ALIASES __has_feature(cxx_alias_templates)
#elif IGM_LANG & IGM_LANG_CXX11_FLAG
#	define IGM_HAS_TEMPLATE_ALIASES 1
#else
#	define IGM_HAS_TEMPLATE_ALIASES ((IGM_LANG & IGM_LANG_CXX0X_FLAG) && (\
		((IGM_COMPILER & IGM_COMPILER_INTEL)) || \
		((IGM_COMPILER & IGM_COMPILER_VC) && (IGM_COMPILER >= IGM_COMPILER_VC12)) || \
		((IGM_COMPILER & IGM_COMPILER_CUDA)) || \
		((IGM_COMPILER & IGM_COMPILER_HIP))))
#endif

// N2930 http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2009/n2930.html
#if IGM_COMPILER & IGM_COMPILER_CLANG
#	define IGM_HAS_RANGE_FOR __has_feature(cxx_range_for)
#elif IGM_LANG & IGM_LANG_CXX11_FLAG
#	define IGM_HAS_RANGE_FOR 1
#else
#	define IGM_HAS_RANGE_FOR ((IGM_LANG & IGM_LANG_CXX0X_FLAG) && (\
		((IGM_COMPILER & IGM_COMPILER_INTEL)) || \
		((IGM_COMPILER & IGM_COMPILER_VC)) || \
		((IGM_COMPILER & IGM_COMPILER_CUDA)) || \
		((IGM_COMPILER & IGM_COMPILER_HIP))))
#endif

// N2341 http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2341.pdf
#if IGM_COMPILER & IGM_COMPILER_CLANG
#	define IGM_HAS_ALIGNOF __has_feature(cxx_alignas)
#elif IGM_LANG & IGM_LANG_CXX11_FLAG
#	define IGM_HAS_ALIGNOF 1
#else
#	define IGM_HAS_ALIGNOF ((IGM_LANG & IGM_LANG_CXX0X_FLAG) && (\
		((IGM_COMPILER & IGM_COMPILER_INTEL) && (IGM_COMPILER >= IGM_COMPILER_INTEL15)) || \
		((IGM_COMPILER & IGM_COMPILER_VC) && (IGM_COMPILER >= IGM_COMPILER_VC14)) || \
		((IGM_COMPILER & IGM_COMPILER_CUDA)) || \
		((IGM_COMPILER & IGM_COMPILER_HIP))))
#endif

// N2235 Generalized Constant Expressions http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2235.pdf
// N3652 Extended Constant Expressions http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3652.html
#if (IGM_ARCH & IGM_ARCH_SIMD_BIT) // Compiler SIMD intrinsics don't support constexpr...
#	define IGM_HAS_CONSTEXPR 0
#elif (IGM_COMPILER & IGM_COMPILER_CLANG)
#	define IGM_HAS_CONSTEXPR __has_feature(cxx_relaxed_constexpr)
#elif (IGM_LANG & IGM_LANG_CXX14_FLAG)
#	define IGM_HAS_CONSTEXPR 1
#else
#	define IGM_HAS_CONSTEXPR ((IGM_LANG & IGM_LANG_CXX0X_FLAG) && IGM_HAS_INITIALIZER_LISTS && (\
		((IGM_COMPILER & IGM_COMPILER_INTEL) && (IGM_COMPILER >= IGM_COMPILER_INTEL17)) || \
		((IGM_COMPILER & IGM_COMPILER_VC) && (IGM_COMPILER >= IGM_COMPILER_VC15))))
#endif

#if IGM_HAS_CONSTEXPR
#	define IGM_CONSTEXPR constexpr
#else
#	define IGM_CONSTEXPR
#endif

//
#if IGM_HAS_CONSTEXPR
# if (IGM_COMPILER & IGM_COMPILER_CLANG)
#	if __has_feature(cxx_if_constexpr)
#		define IGM_HAS_IF_CONSTEXPR 1
#	else
# 		define IGM_HAS_IF_CONSTEXPR 0
#	endif
# elif (IGM_LANG & IGM_LANG_CXX17_FLAG)
# 	define IGM_HAS_IF_CONSTEXPR 1
# else
# 	define IGM_HAS_IF_CONSTEXPR 0
# endif
#else
#	define IGM_HAS_IF_CONSTEXPR 0
#endif

#if IGM_HAS_IF_CONSTEXPR
# 	define IGM_IF_CONSTEXPR if constexpr
#else
#	define IGM_IF_CONSTEXPR if
#endif

//
#if IGM_LANG & IGM_LANG_CXX11_FLAG
#	define IGM_HAS_ASSIGNABLE 1
#else
#	define IGM_HAS_ASSIGNABLE ((IGM_LANG & IGM_LANG_CXX0X_FLAG) && (\
		((IGM_COMPILER & IGM_COMPILER_VC) && (IGM_COMPILER >= IGM_COMPILER_VC15)) || \
		((IGM_COMPILER & IGM_COMPILER_GCC) && (IGM_COMPILER >= IGM_COMPILER_GCC49))))
#endif

//
#define IGM_HAS_TRIVIAL_QUERIES 0

//
#if IGM_LANG & IGM_LANG_CXX11_FLAG
#	define IGM_HAS_MAKE_SIGNED 1
#else
#	define IGM_HAS_MAKE_SIGNED ((IGM_LANG & IGM_LANG_CXX0X_FLAG) && (\
		((IGM_COMPILER & IGM_COMPILER_VC) && (IGM_COMPILER >= IGM_COMPILER_VC12)) || \
		((IGM_COMPILER & IGM_COMPILER_CUDA)) || \
		((IGM_COMPILER & IGM_COMPILER_HIP))))
#endif

//
#if defined(IGM_FORCE_INTRINSICS)
#	define IGM_HAS_BITSCAN_WINDOWS ((IGM_PLATFORM & IGM_PLATFORM_WINDOWS) && (\
		((IGM_COMPILER & IGM_COMPILER_INTEL)) || \
		((IGM_COMPILER & IGM_COMPILER_VC) && (IGM_COMPILER >= IGM_COMPILER_VC14) && (IGM_ARCH & IGM_ARCH_X86_BIT))))
#else
#	define IGM_HAS_BITSCAN_WINDOWS 0
#endif

#if IGM_LANG & IGM_LANG_CXX11_FLAG
#	define IGM_HAS_NOEXCEPT 1
#else
#	define IGM_HAS_NOEXCEPT 0
#endif

#if IGM_HAS_NOEXCEPT
#	define IGM_NOEXCEPT noexcept
#else
#	define IGM_NOEXCEPT
#endif

///////////////////////////////////////////////////////////////////////////////////
// OpenMP
#ifdef _OPENMP
#	if IGM_COMPILER & IGM_COMPILER_GCC
#		if IGM_COMPILER >= IGM_COMPILER_GCC61
#			define IGM_HAS_OPENMP 45
#		elif IGM_COMPILER >= IGM_COMPILER_GCC49
#			define IGM_HAS_OPENMP 40
#		elif IGM_COMPILER >= IGM_COMPILER_GCC47
#			define IGM_HAS_OPENMP 31
#		else
#			define IGM_HAS_OPENMP 0
#		endif
#	elif IGM_COMPILER & IGM_COMPILER_CLANG
#		if IGM_COMPILER >= IGM_COMPILER_CLANG38
#			define IGM_HAS_OPENMP 31
#		else
#			define IGM_HAS_OPENMP 0
#		endif
#	elif IGM_COMPILER & IGM_COMPILER_VC
#		define IGM_HAS_OPENMP 20
#	elif IGM_COMPILER & IGM_COMPILER_INTEL
#		if IGM_COMPILER >= IGM_COMPILER_INTEL16
#			define IGM_HAS_OPENMP 40
#		else
#			define IGM_HAS_OPENMP 0
#		endif
#	else
#		define IGM_HAS_OPENMP 0
#	endif
#else
#	define IGM_HAS_OPENMP 0
#endif

///////////////////////////////////////////////////////////////////////////////////
// nullptr

#if IGM_LANG & IGM_LANG_CXX0X_FLAG
#	define IGM_CONFIG_NULLPTR IGM_ENABLE
#else
#	define IGM_CONFIG_NULLPTR IGM_DISABLE
#endif

#if IGM_CONFIG_NULLPTR == IGM_ENABLE
#	define IGM_NULLPTR nullptr
#else
#	define IGM_NULLPTR 0
#endif

///////////////////////////////////////////////////////////////////////////////////
// Static assert

#if IGM_HAS_STATIC_ASSERT
#	define IGM_STATIC_ASSERT(x, message) static_assert(x, message)
#elif IGM_COMPILER & IGM_COMPILER_VC
#	define IGM_STATIC_ASSERT(x, message) typedef char __CASSERT__##__LINE__[(x) ? 1 : -1]
#else
#	define IGM_STATIC_ASSERT(x, message) assert(x)
#endif//IGM_LANG

///////////////////////////////////////////////////////////////////////////////////
// Qualifiers

// User defines: IGM_CUDA_FORCE_DEVICE_FUNC, IGM_CUDA_FORCE_HOST_FUNC

#if (IGM_COMPILER & IGM_COMPILER_CUDA) || (IGM_COMPILER & IGM_COMPILER_HIP)
#	if defined(IGM_CUDA_FORCE_DEVICE_FUNC) && defined(IGM_CUDA_FORCE_HOST_FUNC)
#		error "IGM error: IGM_CUDA_FORCE_DEVICE_FUNC and IGM_CUDA_FORCE_HOST_FUNC should not be defined at the same time, IGM by default generates both device and host code for CUDA compiler."
#	endif//defined(IGM_CUDA_FORCE_DEVICE_FUNC) && defined(IGM_CUDA_FORCE_HOST_FUNC)

#	if defined(IGM_CUDA_FORCE_DEVICE_FUNC)
#		define IGM_CUDA_FUNC_DEF __device__
#		define IGM_CUDA_FUNC_DECL __device__
#	elif defined(IGM_CUDA_FORCE_HOST_FUNC)
#		define IGM_CUDA_FUNC_DEF __host__
#		define IGM_CUDA_FUNC_DECL __host__
#	else
#		define IGM_CUDA_FUNC_DEF __device__ __host__
#		define IGM_CUDA_FUNC_DECL __device__ __host__
#	endif//defined(IGM_CUDA_FORCE_XXXX_FUNC)
#else
#	define IGM_CUDA_FUNC_DEF
#	define IGM_CUDA_FUNC_DECL
#endif

#if defined(IGM_FORCE_INLINE)
#	if IGM_COMPILER & IGM_COMPILER_VC
#		define IGM_INLINE __forceinline
#		define IGM_NEVER_INLINE __declspec(noinline)
#	elif IGM_COMPILER & (IGM_COMPILER_GCC | IGM_COMPILER_CLANG)
#		define IGM_INLINE inline __attribute__((__always_inline__))
#		define IGM_NEVER_INLINE __attribute__((__noinline__))
#	elif (IGM_COMPILER & IGM_COMPILER_CUDA) || (IGM_COMPILER & IGM_COMPILER_HIP)
#		define IGM_INLINE __forceinline__
#		define IGM_NEVER_INLINE __noinline__
#	else
#		define IGM_INLINE inline
#		define IGM_NEVER_INLINE
#	endif//IGM_COMPILER
#else
#	define IGM_INLINE inline
#	define IGM_NEVER_INLINE
#endif//defined(IGM_FORCE_INLINE)

#define IGM_FUNC_DECL IGM_CUDA_FUNC_DECL
#define IGM_FUNC_QUALIFIER IGM_CUDA_FUNC_DEF IGM_INLINE

// Do not use CUDA function qualifiers on CUDA compiler when functions are made default
#if IGM_HAS_DEFAULTED_FUNCTIONS
#	define IGM_DEFAULTED_FUNC_DECL
#	define IGM_DEFAULTED_FUNC_QUALIFIER IGM_INLINE
#else
#	define IGM_DEFAULTED_FUNC_DECL IGM_FUNC_DECL
#	define IGM_DEFAULTED_FUNC_QUALIFIER IGM_FUNC_QUALIFIER
#endif//IGM_HAS_DEFAULTED_FUNCTIONS
#if !defined(IGM_FORCE_CTOR_INIT)
#	define IGM_DEFAULTED_DEFAULT_CTOR_DECL IGM_DEFAULTED_FUNC_DECL
#	define IGM_DEFAULTED_DEFAULT_CTOR_QUALIFIER IGM_DEFAULTED_FUNC_QUALIFIER
#else
#	define IGM_DEFAULTED_DEFAULT_CTOR_DECL IGM_FUNC_DECL
#	define IGM_DEFAULTED_DEFAULT_CTOR_QUALIFIER IGM_FUNC_QUALIFIER
#endif//IGM_FORCE_CTOR_INIT

///////////////////////////////////////////////////////////////////////////////////
// Swizzle operators

// User defines: IGM_FORCE_SWIZZLE

#define IGM_SWIZZLE_DISABLED		0
#define IGM_SWIZZLE_OPERATOR		1
#define IGM_SWIZZLE_FUNCTION		2

#if defined(IGM_SWIZZLE)
#	pragma message("IGM: IGM_SWIZZLE is deprecated, use IGM_FORCE_SWIZZLE instead.")
#	define IGM_FORCE_SWIZZLE
#endif

#if defined(IGM_FORCE_SWIZZLE) && (IGM_LANG & IGM_LANG_CXXMS_FLAG) && !defined(IGM_FORCE_XYZW_ONLY)
#	define IGM_CONFIG_SWIZZLE IGM_SWIZZLE_OPERATOR
#elif defined(IGM_FORCE_SWIZZLE)
#	define IGM_CONFIG_SWIZZLE IGM_SWIZZLE_FUNCTION
#else
#	define IGM_CONFIG_SWIZZLE IGM_SWIZZLE_DISABLED
#endif

///////////////////////////////////////////////////////////////////////////////////
// Allows using not basic types as genType

// #define IGM_FORCE_UNRESTRICTED_GENTYPE

#ifdef IGM_FORCE_UNRESTRICTED_GENTYPE
#	define IGM_CONFIG_UNRESTRICTED_GENTYPE IGM_ENABLE
#else
#	define IGM_CONFIG_UNRESTRICTED_GENTYPE IGM_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Allows using any scaler as float

// #define IGM_FORCE_UNRESTRICTED_FLOAT

#ifdef IGM_FORCE_UNRESTRICTED_FLOAT
#	define IGM_CONFIG_UNRESTRICTED_FLOAT IGM_ENABLE
#else
#	define IGM_CONFIG_UNRESTRICTED_FLOAT IGM_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Clip control, define IGM_FORCE_DEPTH_ZERO_TO_ONE before including IGM
// to use a clip space between 0 to 1.
// Coordinate system, define IGM_FORCE_LEFT_HANDED before including IGM
// to use left handed coordinate system by default.

#define IGM_CLIP_CONTROL_ZO_BIT		(1 << 0) // ZERO_TO_ONE
#define IGM_CLIP_CONTROL_NO_BIT		(1 << 1) // NEGATIVE_ONE_TO_ONE
#define IGM_CLIP_CONTROL_LH_BIT		(1 << 2) // LEFT_HANDED, For DirectX, Metal, Vulkan
#define IGM_CLIP_CONTROL_RH_BIT		(1 << 3) // RIGHT_HANDED, For OpenGL, default in IGM

#define IGM_CLIP_CONTROL_LH_ZO (IGM_CLIP_CONTROL_LH_BIT | IGM_CLIP_CONTROL_ZO_BIT)
#define IGM_CLIP_CONTROL_LH_NO (IGM_CLIP_CONTROL_LH_BIT | IGM_CLIP_CONTROL_NO_BIT)
#define IGM_CLIP_CONTROL_RH_ZO (IGM_CLIP_CONTROL_RH_BIT | IGM_CLIP_CONTROL_ZO_BIT)
#define IGM_CLIP_CONTROL_RH_NO (IGM_CLIP_CONTROL_RH_BIT | IGM_CLIP_CONTROL_NO_BIT)

#ifdef IGM_FORCE_DEPTH_ZERO_TO_ONE
#	ifdef IGM_FORCE_LEFT_HANDED
#		define IGM_CONFIG_CLIP_CONTROL IGM_CLIP_CONTROL_LH_ZO
#	else
#		define IGM_CONFIG_CLIP_CONTROL IGM_CLIP_CONTROL_RH_ZO
#	endif
#else
#	ifdef IGM_FORCE_LEFT_HANDED
#		define IGM_CONFIG_CLIP_CONTROL IGM_CLIP_CONTROL_LH_NO
#	else
#		define IGM_CONFIG_CLIP_CONTROL IGM_CLIP_CONTROL_RH_NO
#	endif
#endif

///////////////////////////////////////////////////////////////////////////////////
// Qualifiers

#if (IGM_COMPILER & IGM_COMPILER_VC) || ((IGM_COMPILER & IGM_COMPILER_INTEL) && (IGM_PLATFORM & IGM_PLATFORM_WINDOWS))
#	define IGM_DEPRECATED __declspec(deprecated)
#	define IGM_ALIGNED_TYPEDEF(type, name, alignment) typedef __declspec(align(alignment)) type name
#elif IGM_COMPILER & (IGM_COMPILER_GCC | IGM_COMPILER_CLANG | IGM_COMPILER_INTEL)
#	define IGM_DEPRECATED __attribute__((__deprecated__))
#	define IGM_ALIGNED_TYPEDEF(type, name, alignment) typedef type name __attribute__((aligned(alignment)))
#elif (IGM_COMPILER & IGM_COMPILER_CUDA) || (IGM_COMPILER & IGM_COMPILER_HIP)
#	define IGM_DEPRECATED
#	define IGM_ALIGNED_TYPEDEF(type, name, alignment) typedef type name __align__(x)
#else
#	define IGM_DEPRECATED
#	define IGM_ALIGNED_TYPEDEF(type, name, alignment) typedef type name
#endif

///////////////////////////////////////////////////////////////////////////////////

#ifdef IGM_FORCE_EXPLICIT_CTOR
#	define IGM_EXPLICIT explicit
#else
#	define IGM_EXPLICIT
#endif

///////////////////////////////////////////////////////////////////////////////////
// Length type: all length functions returns a length_t type.
// When IGM_FORCE_SIZE_T_LENGTH is defined, length_t is a typedef of size_t otherwise
// length_t is a typedef of int like GLSL defines it.

#define IGM_LENGTH_INT		1
#define IGM_LENGTH_SIZE_T	2

#ifdef IGM_FORCE_SIZE_T_LENGTH
#	define IGM_CONFIG_LENGTH_TYPE		IGM_LENGTH_SIZE_T
#	define IGM_ASSERT_LENGTH(l, max) (assert ((l) < (max)))
#else
#	define IGM_CONFIG_LENGTH_TYPE		IGM_LENGTH_INT
#	define IGM_ASSERT_LENGTH(l, max) (assert ((l) >= 0 && (l) < (max)))
#endif

namespace igm
{
	using std::size_t;
#	if IGM_CONFIG_LENGTH_TYPE == IGM_LENGTH_SIZE_T
		typedef size_t length_t;
#	else
		typedef int length_t;
#	endif
}//namespace igm

#endif // IGM_SETUP_INCLUDED