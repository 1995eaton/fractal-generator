#ifndef VIEWER_H
#define VIEWER_H

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

gboolean key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);
void scale_image(GtkImage *image);
void set_widget_color(GtkWidget *widget, uint32_t hex);
void load_image(const char *file_name);
void viewer_init(void);

#endif
