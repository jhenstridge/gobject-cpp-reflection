/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*- */
#pragma once

#include "is_base_of.h"

namespace gobj {

template <typename Target, typename Source>
inline const Target* gobj_cast(const Source* v)
{
    static_assert(is_base_of<Target, Source>,
                  "Could not verify that target type is a base of source type");
    return reinterpret_cast<const Target*>(v);
}

template <typename Target, typename Source>
inline Target* gobj_cast(Source* v)
{
    static_assert(is_base_of<Target, Source>,
                  "Could not verify that target type is a base of source type");
    return reinterpret_cast<Target*>(v);
}

} /* namespace gobj */
