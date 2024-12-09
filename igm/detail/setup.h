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

#endif // IGM_SETUP_INCLUDED