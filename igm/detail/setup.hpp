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

#endif // IGM_SETUP_INCLUDED