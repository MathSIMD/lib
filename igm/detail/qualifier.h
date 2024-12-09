#pragma once

#include "setup.h"

namespace igm
{
    enum qualifier
    {
        packed_highp,
        packed_mediump,
        packed_lowp,

#       if IGM_CONFIG_ALIGNED_GENTYPES == IMG_ENABLED
        aligned_highp,
        aligned_mediump,
        aligned_lowp,
        aligned = aligned_highp,
#       endif

        highp = packed_highp,
        mediump = packed_mediump,
        lowp = packed_lowp,
        packed = packed_highp,

#       if IGM_CONFIG_ALIGNED_GENTYPES == IMG_ENABLED && defined(IGM_FORCE_DEFAULT_ALIGNED_GENTYPES)
        defaultp = aligned_highp,
#       else
        defaultp = highp,
#       endif
    };

    typedef qualifier precision;

    template <length_t L, typename T, qualifier Q = defaultp> struct vec;

} // namespace igm