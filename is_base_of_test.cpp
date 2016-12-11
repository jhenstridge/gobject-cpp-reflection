/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*- */

#include "is_base_of.h"
#include <cstdio>

using gobj::is_base_of;

struct Foo {};
struct Empty {};
struct Bar { Foo parent; };
struct Baz { Bar parent; };
struct Qux { Foo parent; Empty empty; };
struct NoDefinition;

struct IntStruct { int whatever; };

int main(int argc, char **argv)
{
    printf("is_base_of<Foo, Bar>: %d\n", is_base_of<Foo, Bar>); // true
    printf("is_base_of<Bar, Foo>: %d\n", is_base_of<Bar, Foo>); // false

    printf("is_base_of<Bar, Baz>: %d\n", is_base_of<Bar, Baz>); // true
    printf("is_base_of<Foo, Baz>: %d\n", is_base_of<Foo, Baz>); // true

    printf("is_base_of<Foo, Qux>: %d\n", is_base_of<Foo, Qux>); // true
    printf("is_base_of<Empty, Qux>: %d\n", is_base_of<Empty, Qux>); // false

    printf("is_base_of<Baz, Qux>: %d\n", is_base_of<Baz, Qux>); // false

    printf("is_base_of<Foo, NoDefinition>: %d\n", is_base_of<Foo, NoDefinition>); // false

    printf("is_base_of<int, float>: %d\n", is_base_of<int, float>); // false
    printf("is_base_of<int, IntStruct>: %d\n", is_base_of<int, IntStruct>); // true

    return 0;
}
