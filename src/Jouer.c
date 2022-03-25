#include <gtk/gtk.h>
#include <windows.h>
#include "../header/phaseTir.h"
#include "../header/creerPlateau.h"
#include "../header/creeGrille.h"
#include "../header/creecopieGrille.h"
#include "../header/choisirDiff.h"
#include "../header/fermeFenetre.h"
#include "../header/connecterbouton.h"
#include "../header/message.h"
#include "../header/changementJoueur.h"
#include "../header/connecterOrdi.h"

extern GtkWidget*Joue,*Menu;
extern int plateauBateauJ1[11][11],plateauBateauJ2[11][11],plateauTirJ1[11][11],plateauTirJ2[11][11],longueur[6];
extern int ModeDeJeu,joueur,diff,nbPoste,numJoueur;
extern char*navires[5];
extern GtkWidget*Menu;
int phase=0,phaseDeJeu=1,estAffiche=0;
GtkWidget *grilleJ1Bateau,*copieJ1Bateau,*copieJ2Bateau,*grilleJ1Tir,*grilleJ2Bateau,*grilleJ2Tir;


/**< Fonction jouer: creer toutes les grilles de jeu.
Si solo alors affiche la grille du joueur selon la phase et attends l'appui sur un bouton qui declenchera phaseTir ou phasePlacement
Si multi et 1 poste choisi le joueur qui jouera en premier au hasard et comme solo
Si multi et 2 poste le joueur 1 jouera en premier
 */
void Jouer()
{
    if (phase==0)
    {
        Joue=gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_fullscreen(GTK_WINDOW(Joue));


        grilleJ1Bateau=creeGrille();
        copieJ1Bateau=creecopieGrille();

        grilleJ1Tir=creeGrille();

        grilleJ2Bateau=creeGrille();
        copieJ2Bateau=creecopieGrille();

        grilleJ2Tir=creeGrille();

        creerPlateau(plateauBateauJ1);
        creerPlateau(plateauBateauJ2);
        creerPlateau(plateauTirJ1);
        creerPlateau(plateauTirJ2);

        phase++;
    }
    if(ModeDeJeu == 1)//mode de jeu=1 => solo
    {

        if(phaseDeJeu==1)
        {

            message(g_strdup_printf("Veuillez placer le %s",navires[0]));

            g_timeout_add(0.5,G_SOURCE_FUNC(fermeFenetre),GTK_WIDGET(Menu));

            gtk_container_add(GTK_CONTAINER(Joue),grilleJ1Bateau);
            gtk_widget_show_all(Joue);//affiche le widget joue et connecte les bouton
            connecterbouton();
        }
        if(phaseDeJeu==2)
        {
            grilleJ1Bateau=g_object_ref(grilleJ1Bateau);
            gtk_container_remove(GTK_CONTAINER(Joue),grilleJ1Bateau);
            gtk_container_add(GTK_CONTAINER(Joue),grilleJ1Tir);//affiche la grille de tir et connecte ses boutons

            gtk_widget_show_all(Joue);

        }
    }
    else if(ModeDeJeu == 2)//mode de jeu=2 => multi
    {
        if(nbPoste==1)
        {

            if(phaseDeJeu==1)
            {

                joueur = rand()%2 + 1;
                changementJoueur();

                message(g_strdup_printf("Veuillez placer le %s",navires[0]));

                g_timeout_add_seconds(0.5,G_SOURCE_FUNC(fermeFenetre),GTK_WIDGET(Menu));
                gtk_widget_show_all(Joue);
                connecterbouton();
            }
            if(phaseDeJeu==2)
            {
                gtk_widget_show_all(Joue);
            }
        }
        else if (nbPoste==2)
        {
            if(phaseDeJeu==1)
            {
                connecterOrdi();
            }
            else if(phaseDeJeu==2)
            {
                connecterbouton();
                message(g_strdup_printf("Veuillez placer le %s",navires[0]));

                if(numJoueur==joueur)
                {

                    gtk_container_add(GTK_CONTAINER(Joue),grilleJ1Bateau);
                }
                else
                {
                    gtk_container_add(GTK_CONTAINER(Joue),grilleJ2Bateau);
                }
                g_timeout_add_seconds(0.5,G_SOURCE_FUNC(fermeFenetre),GTK_WIDGET(Menu));

                gtk_widget_show_all(Joue);
                joueur=numJoueur;

            }
            else if(phaseDeJeu==3)
            {
                if(estAffiche!=1)
                {
                    gtk_container_remove(GTK_CONTAINER(Joue),gtk_bin_get_child(GTK_BIN(Joue)));
                    if(numJoueur==1)
                    {
                        gtk_container_add(GTK_CONTAINER(Joue),grilleJ1Tir);
                    }
                    else
                    {
                        gtk_container_add(GTK_CONTAINER(Joue),grilleJ2Tir);
                    }
                    estAffiche=1;
                    gtk_widget_show_all(Joue);
                }

                if(numJoueur!=joueur)
                {
                    phaseTir(NULL,NULL);
                }
            }
        }
    }
}






