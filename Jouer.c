#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <gtk/gtk.h>
#include "Opt.h"
#include "faireMenu.h"
#include "Jouer.h"
#include "dors.h"

//variable générale au fichier ET a tous les fichiers
extern GtkWidget *Joue,*Menu;
extern int width,height;

unsigned left,top;
int i=2;
GtkWidget *grilleJ1Bateau;
GtkWidget *copieJ1Bateau;
GtkWidget *copieJ2Bateau;
GtkWidget *grilleJ1Tir;
GtkWidget *grilleJ2Bateau;
GtkWidget *grilleJ2Tir;
GtkWidget *boite;
GtkWidget* creeGrille();
GtkWidget *GameMenu=NULL;
GtkWidget *creecopieGrille();


void changementJoueur();
void MenuJeu();
void FinPartie();
void montrerGrille();
void repriseJeu();
void modifgrilleCopie();

void Jouer()
{
    //variables





    Joue=gtk_window_new(GTK_WINDOW_TOPLEVEL);

    grilleJ1Bateau=creeGrille();
    copieJ1Bateau=creecopieGrille();
    grilleJ1Tir=creeGrille();
    grilleJ2Bateau=creeGrille();
    copieJ2Bateau=creecopieGrille();
    grilleJ2Tir=creeGrille();



//    gtk_window_fullscreen(GTK_WINDOW(Joue));
    g_timeout_add_seconds(0.1,G_SOURCE_FUNC(dors),GTK_WIDGET(Menu));

    gtk_container_add(GTK_CONTAINER(Joue),grilleJ1Bateau);
    gtk_widget_show_all(Joue);
}

static void callback( GtkWidget *widget, gpointer   data )
{


    gtk_container_child_get(GTK_CONTAINER(data), widget,
                            "left-attach", &left,
                            "top-attach", &top,
                            NULL);

    printf("%d,%d\n",top,left);

}
void modifgrilleCopie()
{
    int joueur=i;

    if(joueur==1)
    {
        if(gtk_grid_get_child_at(GTK_GRID(copieJ2Bateau),left,top)!=NULL)
        {
            gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(copieJ2Bateau),left,top));
        }
    }
    else if(joueur==2)
    {
        if(gtk_grid_get_child_at(GTK_GRID(copieJ1Bateau),left,top)!=NULL)
        {
            gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(copieJ1Bateau),left,top));
        }
    }

}
void changementJoueur()  //affiche un message test pour savoir comment fonctionner les msg dialog
{

    GtkWidget *info=NULL;
    char *joueur=g_strdup_printf("Passez au Joueur: %d",i);
    if(i==1)
    {
        grilleJ2Bateau=g_object_ref(grilleJ2Bateau);
        gtk_container_remove(GTK_CONTAINER(Joue),grilleJ2Bateau);
        gtk_container_add(GTK_CONTAINER(Joue),grilleJ1Bateau);
        i++;
    }
    else
    {
        grilleJ1Bateau=g_object_ref(grilleJ1Bateau);
        gtk_container_remove(GTK_CONTAINER(Joue),grilleJ1Bateau);
        gtk_container_add(GTK_CONTAINER(Joue),grilleJ2Bateau);

        i--;
    }

    info=gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                 joueur);
    gtk_window_resize(GTK_WINDOW(info),(int)width/7,(int)height/7);
    gtk_window_move(GTK_WINDOW(info),(int)width/2-width/14,(int)height/2-height/14);
    gtk_dialog_run(GTK_DIALOG(info));
    gtk_widget_destroy(GTK_WIDGET(info));
    gtk_widget_show_all(GTK_WIDGET(Joue));

}


GtkWidget *creecopieGrille()
{
    GdkRGBA couleur_background;
    couleur_background.red = 0.25;
    couleur_background.green = 0.66;
    couleur_background.blue = 0.78;
    couleur_background.alpha = 1;
    GtkWidget *mot;
    GtkWidget *bouton;
    GtkWidget *Grille;
    Grille=gtk_grid_new();

    for(int i=0; i<10; i++)
    {
        gtk_grid_insert_column(GTK_GRID(Grille),i);
        gtk_grid_insert_row(GTK_GRID(Grille),i);	//crée la grille
    }

    gtk_widget_override_background_color(Joue,GTK_STATE_FLAG_NORMAL,&couleur_background);
    bouton=gtk_button_new_with_label("Retour");
    gtk_grid_attach(GTK_GRID(Grille),GTK_WIDGET(bouton),0,0,1,1);
    g_signal_connect(bouton,"clicked",G_CALLBACK(repriseJeu),NULL);
    for(int i=0; i<10; i++)
    {
        char *ligne=g_strdup_printf("%c",65+i);
        char *colonne=g_strdup_printf("%d",i+1);
        mot=gtk_button_new_with_label(ligne);
        gtk_widget_set_size_request(GTK_WIDGET(mot),(int)width/11,(int)height/11);
        gtk_grid_attach(GTK_GRID(Grille),GTK_WIDGET(mot),i+1,0,1,1);
        mot=gtk_button_new_with_label(colonne);
        gtk_widget_set_size_request(GTK_WIDGET(mot),(int)width/11,(int)height/11);//crée les case du jeu abcdefghij/12345678910
        gtk_grid_attach(GTK_GRID(Grille),GTK_WIDGET(mot),0,i+1,1,1);

        for(int j=0; j<10; j++)
        {
            bouton=gtk_button_new_with_label("");
            gtk_widget_set_size_request(GTK_WIDGET(bouton),(int)width/11,(int)height/11);
            gtk_grid_attach(GTK_GRID(Grille), bouton, j+1, i+1, 1, 1);

        }
    }
    return Grille;
}


GtkWidget *creeGrille()
{
    GdkRGBA couleur_background;
    couleur_background.red = 0.25;
    couleur_background.green = 0.66;
    couleur_background.blue = 0.78;
    couleur_background.alpha = 1;
    GtkWidget *mot;
    GtkWidget *bouton;
    GtkWidget *Grille;
    Grille=gtk_grid_new();

    for(int i=0; i<10; i++)
    {
        gtk_grid_insert_column(GTK_GRID(Grille),i);
        gtk_grid_insert_row(GTK_GRID(Grille),i);	//crée la grille
    }

    gtk_widget_override_background_color(Joue,GTK_STATE_FLAG_NORMAL,&couleur_background);//deprecated
    bouton=gtk_button_new_with_label("Menu");
    gtk_grid_attach(GTK_GRID(Grille),GTK_WIDGET(bouton),0,0,1,1);
    g_signal_connect(bouton,"clicked",G_CALLBACK(MenuJeu),NULL);
    for(int i=0; i<10; i++)
    {
        char *ligne=g_strdup_printf("%c",65+i);
        char *colonne=g_strdup_printf("%d",i+1);
        mot=gtk_button_new_with_label(ligne);
        gtk_widget_set_size_request(GTK_WIDGET(mot),(int)width/11,(int)height/11);
        gtk_grid_attach(GTK_GRID(Grille),GTK_WIDGET(mot),i+1,0,1,1);
        mot=gtk_button_new_with_label(colonne);
        gtk_widget_set_size_request(GTK_WIDGET(mot),(int)width/11,(int)height/11);//crée les case du jeu abcdefghij/12345678910
        gtk_grid_attach(GTK_GRID(Grille),GTK_WIDGET(mot),0,i+1,1,1);

        for(int j=0; j<10; j++)
        {
            bouton=gtk_button_new_with_label("");
            gtk_widget_set_size_request(GTK_WIDGET(bouton),(int)width/11,(int)height/11);
            gtk_grid_attach(GTK_GRID(Grille), bouton, j+1, i+1, 1, 1);
            g_signal_connect(bouton,"clicked",G_CALLBACK(callback),Grille);
            g_signal_connect(bouton,"clicked",G_CALLBACK(modifgrilleCopie),NULL);
            g_signal_connect(bouton,"clicked",G_CALLBACK(changementJoueur),NULL);//chaque bouton du plateau est connecter a une fonction
            g_signal_connect(bouton,"clicked",G_CALLBACK(gtk_widget_destroy),bouton);

        }
    }
    return Grille;
}
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
    g_signal_connect(AfficherGrille,"clicked",G_CALLBACK(montrerGrille),&i);


    gtk_window_resize(GTK_WINDOW(GameMenu),(int)width/7,(int)height/7);
    gtk_window_move(GTK_WINDOW(GameMenu),(int)width/2-width/14,(int)height/2-height/14);
    gtk_widget_show_all(GTK_WIDGET(GameMenu));

}
void montrerGrille(GtkWidget *widget, gpointer   data)
{
    int joueur=i;
    gtk_container_remove(GTK_CONTAINER(GameMenu),GTK_WIDGET(gtk_bin_get_child(GTK_BIN(GameMenu))));
    if(joueur==1)
    {
        gtk_container_add(GTK_CONTAINER(GameMenu),copieJ1Bateau);
    }
    else if(joueur==2)
    {
        gtk_container_add(GTK_CONTAINER(GameMenu),copieJ1Bateau);
    }

    gtk_widget_show_all(GTK_WIDGET(GameMenu));
}
void repriseJeu(GtkWidget *widget, gpointer   data)
{


    if(i==1){
		copieJ1Bateau=g_object_ref(copieJ1Bateau);
		gtk_container_remove(GTK_CONTAINER(GameMenu),copieJ1Bateau);
    }
    if(i==2){
		copieJ1Bateau=g_object_ref(copieJ2Bateau);
		gtk_container_remove(GTK_CONTAINER(GameMenu),copieJ2Bateau);
    }
gtk_window_close(GTK_WINDOW(GameMenu));

}




void FinPartie()
{
    printf("Le gagnant est le joueur %d", i);
    gtk_window_close(GTK_WINDOW(Joue));
    faireMenu();
}
