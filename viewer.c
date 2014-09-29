#include <stdint.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "viewer.h"

gboolean key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
  switch (event->keyval) {
    case GDK_KEY_q:
    case GDK_KEY_Escape:
      gtk_main_quit();
  }
  return FALSE;
}

void scale_image(GtkImage *image) {

  GdkPixbuf *data = gtk_image_get_pixbuf(image);

  int iw = gdk_pixbuf_get_width(data),
      ih = gdk_pixbuf_get_height(data);

  GdkScreen *screen = gdk_screen_get_default();

  gint sw = gdk_screen_get_width(screen);
  gint sh = gdk_screen_get_height(screen);

  double ratio = ih / (double) iw;

  if (ratio > 1 && ih > sh) {
    int oh = ih;
    ih = sh;
    iw -= ratio * (oh - ih);
  } else if (iw > sw) {
    int ow = iw;
    iw = sw;
    ih -= ratio * (ow - iw);
  }

  GdkPixbuf *scaled = gdk_pixbuf_scale_simple(data, iw, ih, GDK_INTERP_HYPER);
  gtk_image_set_from_pixbuf(image, scaled);

}

void set_widget_color(GtkWidget *widget, uint32_t hex) {
  GdkRGBA color = {
    ((hex >> 16) & 0xff) / 255.0,
    ((hex >> 8) & 0xff) / 255.0,
    (hex & 0xff) / 255.0,
    1
  };
  gtk_widget_override_background_color(widget, GTK_STATE_NORMAL, &color);
}

void load_image(const char *file_name) {
  GtkWidget *widget = gtk_window_new(GTK_WINDOW_TOPLEVEL),
            *image = gtk_image_new_from_file(file_name);
  if (image == NULL) { return; }

  g_signal_connect(widget, "destroy", G_CALLBACK(gtk_main_quit), image);
  g_signal_connect(widget, "key_press_event", G_CALLBACK(key_press), NULL);

  scale_image(GTK_IMAGE(image));
  set_widget_color(widget, 0x1b1d1e);
  gtk_container_add(GTK_CONTAINER(widget), image);

  gtk_window_fullscreen(GTK_WINDOW(widget));

  gtk_widget_show_all(widget);
  gtk_main();
}

void viewer_init(void) {
  gtk_init(0, NULL);
}
