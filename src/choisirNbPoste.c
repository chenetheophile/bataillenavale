#include <gtk/gtk.h>

extern int width,height;
GtkWidget* choixLocal;
int nbPoste=1;

/**< Sert a savoir si on utilise 2 poste ou 1. */
void fermerChoix()
{
    gtk_widget_destroy(choixLocal);
}
void local()
{
    nbPoste=1;
    fermerChoix();
}
void reseauLocal()
{
    nbPoste=2;
    fermerChoix();
}
void choisirNbPoste()
{
    GtkWidget *unPoste;
    GtkWidget *deuxPoste;
    GtkWidget *Annuler;


    int hauteurbouton=50,largeurbouton=100;

    GtkWidget *gridFenetre;
    gridFenetre=gtk_grid_new();
    for(int i=0; i<3; i++)
    {
        gtk_grid_insert_column(GTK_GRID(gridFenetre),0);
        gtk_grid_insert_row(GTK_GRID(gridFenetre),0);
    }
    gtk_grid_set_row_spacing(GTK_GRID(gridFenetre),20);
    gtk_grid_set_column_spacing(GTK_GRID(gridFenetre),20);

    choixLocal=gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"N");
    gtk_widget_destroy(gtk_bin_get_child(GTK_BIN(choixLocal)));
    gtk_window_resize(GTK_WINDOW(choixLocal),500,500);

    unPoste=gtk_button_new_with_label("Jouer en local");
    gtk_widget_set_size_request(unPoste,largeurbouton,hauteurbouton);
    g_signal_connect(unPoste,"clicked",local,NULL);

    deuxPoste=gtk_button_new_with_label("Jouer en reseau local");
    gtk_widget_set_size_request(deuxPoste,largeurbouton,hauteurbouton);
    g_signal_connect(deuxPoste,"clicked",reseauLocal,NULL);

    Annuler=gtk_button_new_with_label("Annuler");
    gtk_widget_set_size_request(Annuler,largeurbouton,hauteurbouton);
    g_signal_connect(Annuler,"clicked",fermerChoix,NULL);

    gtk_grid_attach(GTK_GRID(gridFenetre),unPoste,0,0,1,1);
    gtk_grid_attach(GTK_GRID(gridFenetre),deuxPoste,2,0,1,1);
    gtk_grid_attach(GTK_GRID(gridFenetre),Annuler,1,1,1,1);

    gtk_container_add(GTK_CONTAINER(choixLocal),gridFenetre);
    gtk_window_move(GTK_WINDOW(choixLocal),(int)width/2-width/14,(int)height/2-height/14);
    gtk_widget_show_all(choixLocal);
    gtk_dialog_run(GTK_DIALOG(choixLocal));
}
