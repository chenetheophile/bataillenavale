#include <gtk/gtk.h>

extern int width,height;
extern GtkWidget*Joue;

/**< affiche un pop up avec comme message l'argument passé en parametre */

void message(char *message)
{

    GtkWidget *info=NULL;

    info=gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,message);
    gtk_window_resize(GTK_WINDOW(info),(int)width/7,(int)height/7);
    gtk_window_move(GTK_WINDOW(info),(int)width/2-width/14,(int)height/2-height/14);
    gtk_dialog_run(GTK_DIALOG(info));
    gtk_widget_destroy(GTK_WIDGET(info));
    gtk_widget_show_all(GTK_WIDGET(Joue));

}
