#include <gtk/gtk.h>

/**< permet de fermer une fonction dans un g_signal_connect */

void fermeFenetre(GtkWidget *window)
{
    gtk_window_close(GTK_WINDOW(window));
}
