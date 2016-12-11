/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*- */

#include "gobj_cast.h"
#include <gtk/gtk.h>

using gobj::gobj_cast;

int main(int argc, char **argv)
{
    GtkBox *box = nullptr;
    gobj_cast<GtkContainer>(box);
    gobj_cast<GtkWidget>(box);
    gobj_cast<GObject>(box);
#if 0
    // This fails to compile because GtkBox is not a GtkGrid
    gobj_cast<GtkGrid>(box);
#endif
    return 0;
}
