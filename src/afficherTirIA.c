#include <gtk/gtk.h>

extern int width,height,joueur;
extern GtkWidget*Joue;

/**< informe le joueur de l'endroit où l'ia tire et si elle touche ou non. */
void afficherTirIA(int ligne,int colonne,int touche)
{
    GtkWidget *info=NULL;
    char *motviseeIA;
    if(touche==1)
    {
        motviseeIA=g_strdup_printf("L'IA vise %d,%d.\nElle touche.",ligne,colonne);
    }
    else
    {
        motviseeIA=g_strdup_printf("L'IA vise %d,%d.\nElle rate.",ligne,colonne);
    }
    info=gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                 motviseeIA);
    gtk_window_resize(GTK_WINDOW(info),(int)width/7,(int)height/7);
    gtk_window_move(GTK_WINDOW(info),(int)width/2-width/14,(int)height/2-height/14);
    gtk_dialog_run(GTK_DIALOG(info));
    gtk_widget_destroy(GTK_WIDGET(info));
    gtk_widget_show_all(GTK_WIDGET(Joue));
    joueur=joueur%2+1;

}
