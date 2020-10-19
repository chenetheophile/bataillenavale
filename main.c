#include <stdlib.h>
#include <gtk/gtk.h>
#include "faireMenu.h"
int width;
int height;

GtkWidget *Menu=NULL,*Option=NULL,*Joue=NULL;

int main(int argc, char **argv)
{
    /* Initialisation de GTK+ */
    gtk_init(&argc, &argv);

    faireMenu();//declenche le jeu
    gtk_main();//crée la boucle

    /* On quitte.. */
    printf("Oups\n");
    return EXIT_SUCCESS;
}

