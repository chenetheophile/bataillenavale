#include <gtk/gtk.h>

#include "../header/fermeFenetre.h"
#include "../header/choisirDiff.h"
#include "../header/afficherMenu.h"
#include "../header/choisirNbPoste.h"

extern GtkWidget *Menu,*Option;
extern int width,height;
int ModeDeJeu=2;

/**< Options 1 options. Multi ou Solo.
Si multi alors demande nb de poste pour jeu reseau local ou non
si solo alors demande difficulté */

void bouttonJVJ()
{
    ModeDeJeu=2;
    choisirNbPoste();
}
void bouttonIA()
{
    ModeDeJeu=1;
    choisirDiff();
}


void Opt()
{

    //variables
    GtkWidget *layoutoption;
    GtkWidget *retour;
    GtkWidget *radiobouttonIA;
    GtkWidget *radiobouttonJVJ;
    GtkWidget *modeDeJeu;


    Option = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    layoutoption=gtk_layout_new(NULL,NULL);

    retour= gtk_button_new_with_label("Retour");
    radiobouttonJVJ=gtk_radio_button_new_with_label(NULL,"Joueur Vs Joueur");//crée le radio button

    g_signal_connect(radiobouttonJVJ,"released",G_CALLBACK(bouttonJVJ),NULL);

    radiobouttonIA=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radiobouttonJVJ),"Joueur Vs IA");
    g_signal_connect(radiobouttonIA,"released",G_CALLBACK(bouttonIA),NULL);

    gtk_window_fullscreen(GTK_WINDOW(Option));


    g_timeout_add_seconds(0.1,G_SOURCE_FUNC(fermeFenetre),GTK_WIDGET(Menu));//ferme le mmenu en continuant le code qui suit pour eviter que l'user le voit


    gtk_container_add(GTK_CONTAINER(Option),layoutoption);
    modeDeJeu=gtk_label_new("Mode De Jeu");
    gtk_label_set_markup(GTK_LABEL(modeDeJeu),"<span foreground=\'#ffffff\' size='xx-large'>Mode De Jeu</span>");

    g_signal_connect (retour, "clicked", G_CALLBACK(afficherMenu), NULL);


    gtk_container_add(GTK_CONTAINER(layoutoption),modeDeJeu);
    gtk_container_add(GTK_CONTAINER(layoutoption),retour);
    gtk_container_add(GTK_CONTAINER(layoutoption),radiobouttonIA);
    gtk_container_add(GTK_CONTAINER(layoutoption),radiobouttonJVJ);//ajoute au parent les differents widget

    gtk_layout_move(GTK_LAYOUT(layoutoption),radiobouttonIA,width/2-75,height/2+40);
    gtk_layout_move(GTK_LAYOUT(layoutoption),radiobouttonJVJ,width/2-75,height/2);//mise en forme des widgets
    gtk_layout_move(GTK_LAYOUT(layoutoption),modeDeJeu,width/2-90,height/2-70);
    gtk_layout_move(GTK_LAYOUT(layoutoption),retour,width-90,height-50);

    gtk_widget_show_all(Option);
}
