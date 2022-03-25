#include <gtk/gtk.h>

#include "../header/repriseJeu.h"

extern GtkWidget*Joue;
extern int width,height;

/**< Sert a crée une copie des grilles de bateau inerte pour afficher la situation du joueur au niveau de l'état de ses bateaux */

GtkWidget *creecopieGrille()
{
    GtkWidget *mot;
    GtkWidget *bouton;
    GtkWidget *Grille;

    Grille=gtk_grid_new();
    for(int i=0; i<10; i++)
    {
        gtk_grid_insert_column(GTK_GRID(Grille),i);
        gtk_grid_insert_row(GTK_GRID(Grille),i);	//crée la grille
    }

    bouton=gtk_button_new_with_label("Retour");
    gtk_grid_attach(GTK_GRID(Grille),GTK_WIDGET(bouton),0,0,1,1);
    g_signal_connect(bouton,"clicked",G_CALLBACK(repriseJeu),NULL);

    for(int i=0; i<10; i++)
    {
        char *ligne=g_strdup_printf("%c",65+i);
        char *colonne=g_strdup_printf("%d",i+1);

        mot=gtk_button_new_with_label(ligne);
        gtk_widget_set_size_request(GTK_WIDGET(mot),(int)width/22,(int)height/22);
        gtk_grid_attach(GTK_GRID(Grille),GTK_WIDGET(mot),i+1,0,1,1);

        mot=gtk_button_new_with_label(colonne);
        gtk_widget_set_size_request(GTK_WIDGET(mot),(int)width/22,(int)height/22);//crée les case du jeu abcdefghij/12345678910
        gtk_grid_attach(GTK_GRID(Grille),GTK_WIDGET(mot),0,i+1,1,1);

        for(int j=0; j<10; j++)
        {
            bouton=gtk_button_new_with_label("");
            gtk_widget_set_size_request(GTK_WIDGET(bouton),(int)width/22,(int)height/22);
            gtk_grid_attach(GTK_GRID(Grille), bouton, j+1, i+1, 1, 1);

        }
    }
    return Grille;
}

