#include <gtk/gtk.h>

#include "../header/resultatTir.h"

extern int width,height,joueur;
extern GtkWidget*Joue;

/**< Affiche un pop up pour informer le joueur si le tir fait mouche ou non */

void afficherTir(int ligne,int colonne,int touche)
{

    GtkWidget *info=NULL;
    char *motvisee;
    if(touche==1)
    {
        motvisee=g_strdup_printf("Envoi du missile en %d,%d.\nKaboom!.",ligne,colonne);
    }
    else
    {
        motvisee=g_strdup_printf("Envoi du missile en %d,%d.\nSplush.",ligne,colonne);
    }

    resultatTir(ligne,colonne,touche,joueur);
    info=gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                 motvisee);
    gtk_window_resize(GTK_WINDOW(info),(int)width/7,(int)height/7);
    gtk_window_move(GTK_WINDOW(info),(int)width/2-width/14,(int)height/2-height/14);
    gtk_dialog_run(GTK_DIALOG(info));
    gtk_widget_destroy(GTK_WIDGET(info));


    gtk_widget_show_all(GTK_WIDGET(Joue));
}
