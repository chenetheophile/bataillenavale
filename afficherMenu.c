#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "dors.h"
extern GtkWidget *Option;

void afficherMenu()
{
    faireMenu();
    g_timeout_add_seconds(0.1,G_SOURCE_FUNC(dors),GTK_WIDGET(Option));//affiche le menu depuis le widget et supprime l ancienne fenetre

}
