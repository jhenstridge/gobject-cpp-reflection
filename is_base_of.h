/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*- */
#pragma once

#include <reflexpr>

namespace gobj {

namespace detail {

/* non_empty_struct<MO>::value is true if MO is the metaobject for a structure with at least one member */
template <typename MO, bool = std::meta::Class<MO> >
struct non_empty_struct;

template <typename MO>
struct non_empty_struct<MO, false> {
    static constexpr bool value = false;
};
template <typename MO>
struct non_empty_struct<MO, true> {
    static constexpr bool value = std::meta::get_size_v<std::meta::get_data_members_m<MO>> > 0;
};


/* first_member_type<MO> is the metaobject representing the type of
 * the first member of the struct represented by the metaobject MO. */
template <typename MO>
using first_member_type = std::meta::get_type_m<
    std::meta::get_element_m<std::meta::get_data_members_m<MO>, 0>>;

/* is_base_of<Base_MO, Derived_MO>::value is true if struct
 * represented by the metaobject Base_MO is a GObject-style "base
 * class" of the struct represented by the metaobject Derived_MO */
template <typename Base_MO, typename Derived_MO,
          bool = std::meta::reflects_same_v<Base_MO, Derived_MO>,
          bool = non_empty_struct<Derived_MO>::value >
struct is_base_of;

// Special case when Base is Derived
template <typename Base_MO, typename Derived_MO, bool NonEmpty>
struct is_base_of<Base_MO, Derived_MO, true, NonEmpty> {
    static constexpr bool value = true;
};

// If Derived_MO isn't a struct or is empty, then Base can't be a base.
template <typename Base_MO, typename Derived_MO>
struct is_base_of<Base_MO, Derived_MO, false, false> {
    static constexpr bool value = false;
};

// Finally, chain to the first member type of Derived_MO
template <typename Base_MO, typename Derived_MO>
struct is_base_of<Base_MO, Derived_MO, false, true> {
    static constexpr bool value = is_base_of<Base_MO, first_member_type<Derived_MO>>::value;
};

} /* namespace gobj::detail */

template <typename Base, typename Derived>
constexpr bool is_base_of = detail::is_base_of<reflexpr(Base), reflexpr(Derived)>::value;

} /* namespace gobj */
