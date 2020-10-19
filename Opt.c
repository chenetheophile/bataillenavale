#include <stdlib.h>
#include <gtk/gtk.h>
#include "faireMenu.h"
#include "afficherMenu.h"
#include "dors.h"
extern GtkWidget *Menu,*Option;
extern int width,height;
void Opt(){

	//variables
    GtkWidget *layoutoption;
    GtkWidget *retour;
    GtkWidget *radionbouttonIA;
    GtkWidget *radionbouttonJVJ;
    GtkWidget *modeDeJeu;
    GdkRGBA couleur_background;
    couleur_background.red = 0.25;
    couleur_background.green = 0.66;
    couleur_background.blue = 0.78;
    couleur_background.alpha = 1;


    Option = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    layoutoption=gtk_layout_new(NULL,NULL);

    retour= gtk_button_new_with_label("Retour");
    radionbouttonJVJ=gtk_radio_button_new_with_label(NULL,"Joueur Vs Joueur");//crée le radio button

    radionbouttonIA=gtk_radio_button_new_with_label_from_widget(GTK_WIDGET(radionbouttonJVJ),"Joueur Vs IA");
    gtk_window_fullscreen(GTK_WINDOW(Option));
    gtk_widget_override_background_color(Option,GTK_STATE_FLAG_NORMAL,&couleur_background); //couleur du BG

    g_timeout_add_seconds(0.1,G_SOURCE_FUNC(dors),GTK_WIDGET(Menu));//ferme le mmenu en continuant le code qui suit pour eviter que l'user le voit


    gtk_container_add(GTK_CONTAINER(Option),layoutoption);
    modeDeJeu=gtk_label_new("Mode De Jeu");
    gtk_label_set_markup(modeDeJeu,"<span foreground=\'#ffffff\' size='xx-large'>Mode De Jeu</span>");

    g_signal_connect (retour, "clicked", G_CALLBACK(afficherMenu), NULL);

    gtk_container_add(GTK_CONTAINER(layoutoption),modeDeJeu);
    gtk_container_add(GTK_CONTAINER(layoutoption),retour);
    gtk_container_add(GTK_CONTAINER(layoutoption),radionbouttonIA);
    gtk_container_add(GTK_CONTAINER(layoutoption),radionbouttonJVJ);//ajoute au parent les differents widget

    gtk_layout_move(GTK_LAYOUT(layoutoption),radionbouttonIA,width/2-75,height/2+40);
    gtk_layout_move(GTK_LAYOUT(layoutoption),radionbouttonJVJ,width/2-75,height/2);//mise en forme des widgets
    gtk_layout_move(GTK_LAYOUT(layoutoption),modeDeJeu,width/2-90,height/2-70);
    gtk_layout_move(GTK_LAYOUT(layoutoption),retour,width-90,height-50);

    gtk_widget_show_all(Option);
}
