#include <gtk/gtk.h>

#include "../header/faireMenu.h"
#include "../header/message.h"

extern GtkWidget*Joue,*Menu,*grilleJ1Bateau,*grilleJ1Tir,*grilleJ2Bateau,*grilleJ2Tir,*copieJ1Bateau,*copieJ2Bateau;
extern int joueur,*plateauBateauJ1[11][11],*plateauBateauJ2[11][11],*plateauTirJ1[11][11],*plateauTirJ2[11][11];
extern int phaseDeJeu,bateauplace,plateaucomplet,phase;
/**< Lorsque la partie est termine declare un vainqueur (en fonction de la phase si abandon) et reinitialise les var pour pouvoir recommencer */
void FinPartie()
{

    if(phaseDeJeu)
    {
        printf("La victoire revient au joueur %d", joueur%2+1);
        message(g_strdup_printf("La victoire revient au joueur %d",joueur%2+1));
    }
    else
    {
        printf("La victoire revient au joueur %d", joueur);
        message(g_strdup_printf("La victoire revient au joueur %d",joueur));
    }
    faireMenu();
    gtk_window_close(GTK_WINDOW(Joue));
    gtk_widget_destroy(grilleJ1Bateau);
    gtk_widget_destroy(grilleJ2Bateau);
    gtk_widget_destroy(grilleJ1Tir);
    gtk_widget_destroy(grilleJ2Tir);
    gtk_widget_destroy(copieJ1Bateau);
    gtk_widget_destroy(copieJ2Bateau);


    phase=0;
    phaseDeJeu=1;
    bateauplace=0;
    plateaucomplet=0;

}
