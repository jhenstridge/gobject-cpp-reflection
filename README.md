# Tracking GObject inheritance with C++ Reflection

This repository contains a few utility functions that make use of
the draft [C++ Static Reflection](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0194r1.html)
standard.  Sadly this feature hasn't been included in the C++17 standard, but an implementation for Clang is available as the `reflexpr` branch of the following repository:

https://github.com/matus-chochlik/clang

## is_base_of

The `is_base_of` templated constant can be used to determine whether
one struct type is the "GObject style" base of another struct type.

That is, `is_base_of<Base, Subclass>` is true if either `Base` and
`Subclass` are the same type or if `is_base_of<Base, T>` is true,
where `T` is the type of the first data member of `Subclass`.

`is_base_of` is a constant expression, so it's value is determined at
compile time.

```C++
gobj::is_base_of<GtkBox, GtkBox>    // == true
gobj::is_base_of<GtkWidget, GtkBox> // == true
gobj::is_base_of<GtkObject, GtkBox> // == true
gobj::is_base_of<GObject, GtkBox>   // == true
gobj::is_base_of<GtkGrid, GtkBox>   // == false
```

## gobj_cast

The `gobj_cast` helper function can be used to cast a pointer to a
GObject subclass to a pointer to any of its base classes.  It is built
on top of the `is_base_of` machinery.

For correct casts, the function call will be optimised away:

```C++
using gobj::gobj_cast;
...
GtkBox *box = ...;
auto widget = gobj_cast<GtkWidget>(box);
```

For invalid upcasts, it will produce a compile time error with a
somewhat readable error message:

```
In file included from test.cpp:3:
./gobj_cast.h:19:5: error: static_assert failed "Could not verify that target
      type is a base of source type"
    static_assert(is_base_of<Target, Source>,
    ^             ~~~~~~~~~~~~~~~~~~~~~~~~~~
test.cpp:11:17: note: in instantiation of function template specialization
      'gobj::gobj_cast<_GtkGrid, _GtkBox>' requested here
    auto grid = gobj_cast<GtkGrid>(box);
                ^
1 error generated.
```
