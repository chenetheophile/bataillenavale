#include <gtk/gtk.h>
#include "../header/FinPartie.h"
#include "../header/montrerGrille.h"

extern int joueur,width,height;
GtkWidget *boite,*GameMenu=NULL;

/**< Le menu du jeu comporte 3 options. Montrer la grille de bateau pour savoir sa situation
l'abandon pour terminer la partie
retour pour revenir au jeu */

void MenuJeu()
{
    GtkWidget *Retour;
    GtkWidget *AfficherGrille;
    GtkWidget *Abandon;
    GameMenu=gtk_window_new(GTK_WINDOW_TOPLEVEL);

    boite=gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    Retour=gtk_button_new_with_label("Retour");
    Abandon=gtk_button_new_with_label("Declarer forfait");
    AfficherGrille=gtk_button_new_with_label("Montrer ma grille de bateau");


    gtk_container_add(GTK_CONTAINER(boite),AfficherGrille);
    gtk_container_add(GTK_CONTAINER(boite),Abandon);
    gtk_container_add(GTK_CONTAINER(boite),Retour);
    g_signal_connect(Retour,"clicked",G_CALLBACK(gtk_window_close),NULL);
    gtk_container_add(GTK_CONTAINER(GameMenu),boite);
    gtk_box_set_homogeneous(GTK_BOX(boite),TRUE);
    gtk_button_box_set_layout (GTK_BUTTON_BOX (boite), GTK_BUTTONBOX_CENTER);
    g_signal_connect(Abandon,"clicked",G_CALLBACK(FinPartie),NULL);
    g_signal_connect(Abandon,"clicked",G_CALLBACK(gtk_window_close),NULL);
    g_signal_connect(AfficherGrille,"clicked",G_CALLBACK(montrerGrille),&joueur);


    gtk_window_resize(GTK_WINDOW(GameMenu),(int)width/7,(int)height/7);
    gtk_window_move(GTK_WINDOW(GameMenu),(int)width/2-width/14,(int)height/2-height/14);
    gtk_widget_show_all(GTK_WIDGET(GameMenu));

}
