#include <gtk/gtk.h>

#include "../header/Jouer.h"
#include "../header/Opt.h"

extern int width,height;
extern GtkWidget *Menu,*Option,*Joue;

/**< creer le menu avec 3 boutons, jouer options quitter. chaque bouton sont relié a leur fct respective */

void faireMenu()
{

//variables
    GtkWidget * button_box;
    GtkWidget * boutton_quitter;
    GtkWidget * boutton_options;
    GtkWidget * boutton_jouer;
    GtkWidget * layoutmenu;
    GtkWidget * Image;

    int milieuBoutton;
    int milieuTitre;


    Menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(Menu));//création du menu et mise en FS de l'appli
    gtk_window_set_icon_from_file(GTK_WINDOW(Menu),"photo/logo.jpg",NULL);

    GdkRectangle workarea = {0};
    gdk_monitor_get_workarea(gdk_display_get_primary_monitor(gdk_display_get_default()),&workarea);
    width=workarea.width;
    height=workarea.height;//obtient la taille de l'écran

    milieuBoutton=(int)width/2-width*0.23;//sert a centrer les boutons
    milieuTitre=(int)width*0.3;//sert a centrer le titre

    layoutmenu=gtk_layout_new(NULL,NULL);
    gtk_container_add (GTK_CONTAINER (Menu), layoutmenu);//crée le layout permettant de stocker tous les widgets du menu

    Image=gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(Image),"photo/titre.PNG");
    gtk_container_add (GTK_CONTAINER (layoutmenu), Image);//importe le titre et l'ajoute dans le layout

    button_box = gtk_button_box_new (GTK_ORIENTATION_VERTICAL);//boite à boutons
    gtk_container_add (GTK_CONTAINER (layoutmenu), button_box);//ajout de la boite a boutton dans le layout
    gtk_container_set_border_width(GTK_CONTAINER (button_box),400);//change les parametre de la boite a boutons
    gtk_box_set_spacing(GTK_BOX(button_box),40);



    gtk_layout_move(GTK_LAYOUT(layoutmenu),button_box,milieuBoutton,50);//bouge la boite a bouton au centre
    gtk_layout_move(GTK_LAYOUT(layoutmenu),Image,milieuTitre,100);//bouge l'image d titre au centre


    boutton_jouer = gtk_button_new_with_label("Jouer");
    g_signal_connect (G_OBJECT(boutton_jouer), "clicked", G_CALLBACK(Jouer), 0);
    gtk_container_add (GTK_CONTAINER (button_box), boutton_jouer);//crée les boutons et quand on appui dessus ca appelle la fct gtk_main_quit

    boutton_options = gtk_button_new_with_label("Options");
    g_signal_connect (boutton_options, "clicked",G_CALLBACK(Opt),NULL);

    gtk_container_add (GTK_CONTAINER (button_box), boutton_options);


    boutton_quitter = gtk_button_new_with_label("Quitter");
    g_signal_connect (boutton_quitter, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_add (GTK_CONTAINER (button_box), boutton_quitter);

    GtkCssProvider *prov=gtk_css_provider_new();
    gtk_css_provider_load_from_path(prov, "background.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(prov),
            GTK_STYLE_PROVIDER_PRIORITY_USER);


    gtk_widget_show_all(Menu);//affiche le menu.
}
