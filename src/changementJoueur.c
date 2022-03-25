#include <gtk/gtk.h>

extern GtkWidget*Joue,*grilleJ1Bateau,*grilleJ2Bateau,*grilleJ1Tir,*grilleJ2Tir;
extern int joueur,width,height,phaseDeJeu;

/**< Sert à afficher la bonne grille tout au long du jeu et changer de joueur. Cette fonction n'est appelée que lorsque
le jeu est joué sur 1 poste */
void changementJoueur()
{

    GtkWidget *info=NULL;
    if(phaseDeJeu==1)
    {
        if(joueur==1)
        {
            if(gtk_bin_get_child(GTK_BIN(Joue))!=NULL)
            {
                grilleJ1Bateau=g_object_ref(grilleJ1Bateau);
                gtk_container_remove(GTK_CONTAINER(Joue),grilleJ1Bateau);
            }
            gtk_container_add(GTK_CONTAINER(Joue),grilleJ2Bateau);
        }
        else
        {
            if(gtk_bin_get_child(GTK_BIN(Joue))!=NULL)
            {
                grilleJ2Bateau=g_object_ref(grilleJ2Bateau);
                gtk_container_remove(GTK_CONTAINER(Joue),grilleJ2Bateau);
            }
            gtk_container_add(GTK_CONTAINER(Joue),grilleJ1Bateau);
        }
    }
    else if(phaseDeJeu==2)
    {
        if(joueur==1)
        {
            if(gtk_bin_get_child(GTK_BIN(Joue))==grilleJ1Bateau)
            {
                grilleJ1Bateau=g_object_ref(grilleJ1Bateau);
                gtk_container_remove(GTK_CONTAINER(Joue),grilleJ1Bateau);
                gtk_container_add(GTK_CONTAINER(Joue),grilleJ2Tir);
            }
            else
            {
                grilleJ1Tir=g_object_ref(grilleJ1Tir);
                gtk_container_remove(GTK_CONTAINER(Joue),grilleJ1Tir);
                gtk_container_add(GTK_CONTAINER(Joue),grilleJ2Tir);
            }
        }
        else
        {
            if(gtk_bin_get_child(GTK_BIN(Joue))==grilleJ2Bateau)
            {
                grilleJ2Bateau=g_object_ref(grilleJ2Bateau);
                gtk_container_remove(GTK_CONTAINER(Joue),grilleJ2Bateau);
                gtk_container_add(GTK_CONTAINER(Joue),grilleJ1Tir);
            }
            else
            {
                grilleJ2Tir=g_object_ref(grilleJ2Tir);
                gtk_container_remove(GTK_CONTAINER(Joue),grilleJ2Tir);
                gtk_container_add(GTK_CONTAINER(Joue),grilleJ1Tir);
            }
        }
    }
    joueur=joueur%2+1;
    char *motjoueur=g_strdup_printf("Passez au Joueur: %d",joueur);
    info=gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                 motjoueur);
    gtk_window_resize(GTK_WINDOW(info),(int)width/7,(int)height/7);
    gtk_window_move(GTK_WINDOW(info),(int)width/2-width/14,(int)height/2-height/14);
    gtk_dialog_run(GTK_DIALOG(info));
    gtk_widget_destroy(GTK_WIDGET(info));
    gtk_widget_show_all(GTK_WIDGET(Joue));

}
