#include <gtk/gtk.h>
#include <winsock2.h>

#include "../header/tirer.h"
#include "../header/FinPartie.h"
#include "../header/changementJoueur.h"
#include "../header/modifgrilleCopie.h"
#include "../header/afficherPlateau.h"
#include "../header/tirerSolo.h"
#include "../header/message.h"
#include "../header/Jouer.h"
#include "../header/connecterOrdi.h"
#include "../header/StrToInt.h"

extern unsigned left,top;
extern int joueur,t1,t2,ModeDeJeu,diff,nbPoste,numJoueur;
extern int plateauBateauJ1[11][11],plateauBateauJ2[11][11],plateauTirJ1[11][11],plateauTirJ2[11][11];

/**<  Phase de Tir appelé lorsqu'on clique sur un bouton pendant la phase 2

On definit les coord du bouton cliquer la case où l'on souhaite tirer
a
Si on joue sur 1 poste alors on tire on affiche le resultat et l'autre joueur tir(IA ou joueur. Si IA c'est direct sinon on attent l'appui sur
																				un bouton)

Si on joue sur 2 poste 1 poste attends de recevoir les coord du tir pendant que l'autre envoi les données lors de l'appui sur un bouton.

Enfin on teste si le jeu est terminé ou pas
*/
void phaseTir(GtkWidget*widget,gpointer data)
{

    if(nbPoste==1)
    {
        gtk_container_child_get(GTK_CONTAINER(data), widget,"left-attach", &left,"top-attach", &top,NULL);
        if(ModeDeJeu==1)
        {
            tirerSolo(plateauBateauJ1,plateauBateauJ2,plateauTirJ1,plateauTirJ2,joueur,diff);
            joueur=joueur%2+1;
        }
        else
        {
            tirer(plateauBateauJ1,plateauBateauJ2,plateauTirJ1,plateauTirJ2);

        }
        if(t1 < 17 && t2 < 17&&ModeDeJeu==2)
        {
            changementJoueur();
            modifgrilleCopie(left,top,joueur);
        }
        else if (t1 < 17 && t2 < 17&&ModeDeJeu==1)
        {
            tirerSolo(plateauBateauJ1,plateauBateauJ2,plateauTirJ1,plateauTirJ2,joueur,diff);
        }
        else
        {
            FinPartie();

        }
    }
    else
    {

        if(numJoueur==joueur)
        {
            gtk_container_child_get(GTK_CONTAINER(data), widget,"left-attach", &left,"top-attach", &top,NULL);

            tirer(plateauBateauJ1,plateauBateauJ2,plateauTirJ1,plateauTirJ2);
            char *msg=g_strdup_printf("%d",left-1);
            envoyerCo(msg);
            char *msg2=g_strdup_printf("%d",top-1);
            envoyerCo(msg2);
//            printf("Coord envoyé\n");
        }
        else
        {
            message("En attente du tir de votre adversaire");
            printf("Attente de l'action de l'adv");
            left=StrtoInt(recevoirCo())+1;
            top=StrtoInt(recevoirCo())+1;
            tirer(plateauBateauJ1,plateauBateauJ2,plateauTirJ1,plateauTirJ2);
        }
        if(t1 < 17 && t2 < 17&&ModeDeJeu==2)
        {
            joueur=joueur%2+1;
            modifgrilleCopie(left,top,joueur);
            Jouer();
        }
        else
        {
            FinPartie();

        }

    }
}
