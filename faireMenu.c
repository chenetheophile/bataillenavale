#include <stdlib.h>
#include <gtk/gtk.h>
#include "Opt.h"
#include "afficherMenu.h"
#include "faireMenu.h"
#include "Jouer.h"
#include "dors.h"
//
extern int width,height;
extern GtkWidget *Menu,*Option,*Joue;
void faireMenu()
{

//variables
    GtkWidget * button_box;
    GtkWidget * boutton_quitter;
    GtkWidget * boutton_options;
    GtkWidget * boutton_jouer;
    GtkWidget * layoutmenu;
    GtkWidget * Image;

    GdkScreen * screen;
    GdkRGBA couleur_background;
    couleur_background.red = 0.25;
    couleur_background.green = 0.66;
    couleur_background.blue = 0.78;
    couleur_background.alpha = 1;
    int milieuBoutton;
    int milieuTitre;
//
    Menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//    gtk_window_fullscreen(GTK_WINDOW(Menu));//création du menu et mise en FS de l'appli

    screen=gdk_screen_get_default();//prend les mesures de l'écran

    width=gdk_screen_get_width(screen);//regarde la largeur de l'écran
    height=gdk_screen_get_height(screen);

    milieuBoutton=(int)width/2-width*0.23;//sert a centrer les boutons
    milieuTitre=(int)width*0.3;//sert a centrer le titre

    layoutmenu=gtk_layout_new(NULL,NULL);
    gtk_container_add (GTK_CONTAINER (Menu), layoutmenu);//crée le layout permettant de stocker tous les widgets du menu

    Image=gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(Image),"titre.PNG");
    gtk_container_add (GTK_CONTAINER (layoutmenu), Image);//importe le titre et l'ajoute dans le layout

    button_box = gtk_button_box_new (GTK_ORIENTATION_VERTICAL);//boite à boutons
    gtk_container_add (GTK_CONTAINER (layoutmenu), button_box);//ajout de la boite a boutton dans le layout
    gtk_container_set_border_width(GTK_CONTAINER (button_box),400);//change les parametre de la boite a boutons
    gtk_box_set_spacing(GTK_BOX(button_box),40);



    gtk_layout_move(GTK_LAYOUT(layoutmenu),button_box,milieuBoutton,50);//bouge la boite a bouton au centre
    gtk_layout_move(GTK_LAYOUT(layoutmenu),Image,milieuTitre,100);//bouge l'image d titre au centre


    boutton_jouer = gtk_button_new_with_label("Jouer");
    g_signal_connect (G_OBJECT(boutton_jouer), "clicked", G_CALLBACK(Jouer), NULL);
    gtk_container_add (GTK_CONTAINER (button_box), boutton_jouer);//crée les boutons et quand on appui dessus ca appelle la fct gtk_main_quit

    boutton_options = gtk_button_new_with_label("Options");
    g_signal_connect (boutton_options, "clicked",G_CALLBACK(Opt),NULL);

    gtk_container_add (GTK_CONTAINER (button_box), boutton_options);


    boutton_quitter = gtk_button_new_with_label("Quitter");
    g_signal_connect (boutton_quitter, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_add (GTK_CONTAINER (button_box), boutton_quitter);

    gtk_widget_override_background_color(Menu,GTK_STATE_FLAG_NORMAL,&couleur_background);//fonctionne Cependant on est censé faire une partie en Css pour faire ca propre ce que je ne compte pas faire parce que.

    gtk_widget_show_all(Menu);//affiche le menu.
}
