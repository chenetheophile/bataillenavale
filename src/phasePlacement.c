#include <gtk/gtk.h>
#include <winsock2.h>

#include "../header/placer.h"
#include "../header/placementIA.h"
#include "../header/Jouer.h"
#include "../header/changementJoueur.h"
#include "../header/tirerSolo.h"
#include "../header/message.h"
#include "../header/connecterOrdi.h"
#include "../header/StrToInt.h"

unsigned int left,top;
extern int joueur,bateauplace,phaseDeJeu,ModeDeJeu,numJoueur,nbPoste,direction;
extern int plateauBateauJ1[11][11],plateauBateauJ2[11][11],longueur[6];
extern char*navires[5];
int plateaucomplet=0;
int coJ1[5][3]= {{-1}},coJ2[5][3]= {{-1}};


/**<  Phase de placement appelé lorsqu'on clique sur un bouton pendant la phase 1(ou 2 si reseau local)

On definit les coord du bouton cliquer comme l'origine du bateau et on le deploie dans la direction qui sera demandé dans placer.
Si on clique sur un bouton et que le placement est valide on passe au prochain bateau.

Si on joue seul alors une fois qu'on a placé ses 5 bateau on lance la phase de tir

Si on joue a deux sur 1 poste alors une fois qu"on a placé ses 5 bateaux on donne la main a l'adv pour qu'il les place.

Si on joue a deux sur 2 poste alors les deux joueurs place les bateaux en meme temps et ensuite les données sont envoyées à l'autre ordinateur
pour faire avancer le jeu.
*/

void phasePlacement( GtkWidget *widget, gpointer   data )
{
    gtk_container_child_get(GTK_CONTAINER(data), widget,"left-attach", &left,"top-attach", &top, NULL);

    if(ModeDeJeu==1)//solo
    {
        if(joueur==1)
        {
            placer(plateauBateauJ1,navires,longueur,bateauplace);
        }
        if(bateauplace==5)
        {
            placementIA(plateauBateauJ2,navires,longueur);
            phaseDeJeu=2;
            Jouer();
        }
    }

    else if(ModeDeJeu==2)//multi
    {
        if(nbPoste==1)
        {
            if(joueur==1)
            {
                placer(plateauBateauJ1,navires,longueur,bateauplace);
            }
            if(joueur==2)
            {
                placer(plateauBateauJ2,navires,longueur,bateauplace);
            }
            if(bateauplace==5&&plateaucomplet==0)
            {
                bateauplace=0;
                plateaucomplet++;
                changementJoueur();
                printf("Au joueur %d:\n",joueur);
                left=-1;
                top=-1;

            }
            if(bateauplace==5 && plateaucomplet==1)
            {
                phaseDeJeu=2;

                changementJoueur();
                Jouer();

            }
        }
        else if(nbPoste==2)
        {
            joueur=numJoueur;
            if(numJoueur==1)
            {
                placer(plateauBateauJ1,navires,longueur,bateauplace);
                if(direction!=-1)
                {
                    coJ1[bateauplace-1][0]=left-1;
                    coJ1[bateauplace-1][1]=top-1;
                    coJ1[bateauplace-1][2]=direction;
                }



            }
            if(numJoueur==2)
            {
                placer(plateauBateauJ2,navires,longueur,bateauplace);
                if(direction!=-1)
                {
                    coJ2[bateauplace-1][0]=left-1;
                    coJ2[bateauplace-1][1]=top-1;
                    coJ2[bateauplace-1][2]=direction;
                }
            }
            if(bateauplace==5&&plateaucomplet==0)
            {
                left=-1;
                top=-1;
                bateauplace=0;
                plateaucomplet++;
                joueur=joueur%2+1;
                if(numJoueur==1)
                {
                    for(int i=0; i<5; i++)
                    {
                        coJ2[i][0]=StrtoInt(recevoirCo())+1;
                        coJ2[i][1]=StrtoInt(recevoirCo())+1;
                        coJ2[i][2]=StrtoInt(recevoirCo());
//                        printf("\nRecu:\ncoJ2[%d][0]=%d\ncoJ2[%d][1]=%d\ncoJ2[%d][2]=%d\n",i,coJ2[i][0],i,coJ2[i][1],i,coJ2[i][2]);
                    }
                    for(int i=0; i<5; i++)
                    {
                        left=coJ2[i][0];
                        top=coJ2[i][1];
                        direction=coJ2[i][2];
                        placer(plateauBateauJ2,navires,longueur,bateauplace);
                    }
                    for(int i=0; i<5; i++)
                    {
                        char *msg=g_strdup_printf("%d",coJ1[i][0]);
                        envoyerCo(msg);
                        char *msg2=g_strdup_printf("%d",coJ1[i][1]);
                        envoyerCo(msg2);
                        char *msg3=g_strdup_printf("%d",coJ1[i][2]);
                        envoyerCo(msg3);
//                        printf("\nEnvoi:\ncoJ1[%d][0]=%d\ncoJ1[%d][1]=%d\ncoJ1[%d][2]=%d\n",i,coJ1[i][0],i,coJ1[i][1],i,coJ1[i][2]);
                    }
                }
                if(numJoueur==2)
                {
                    for(int i=0; i<5; i++)
                    {
                        char *msg=g_strdup_printf("%d",coJ2[i][0]);
                        envoyerCo(msg);
                        char *msg2=g_strdup_printf("%d",coJ2[i][1]);
                        envoyerCo(msg2);
                        char *msg3=g_strdup_printf("%d",coJ2[i][2]);
                        envoyerCo(msg3);
//                        printf("\nEnvoi:\ncoJ2[%d][0]=%d\ncoJ2[%d][1]=%d\ncoJ2[%d][2]=%d\n",i,coJ2[i][0],i,coJ2[i][1],i,coJ2[i][2]);
                    }
                    for(int i=0; i<5; i++)
                    {

                        coJ1[i][0]=StrtoInt(recevoirCo())+1;
                        coJ1[i][1]=StrtoInt(recevoirCo())+1;
                        coJ1[i][2]=StrtoInt(recevoirCo());
//                        printf("\nRecu:\ncoJ1[%d][0]=%d\ncoJ1[%d][1]=%d\ncoJ1[%d][2]=%d\n",i,coJ1[i][0],i,coJ1[i][1],i,coJ1[i][2]);
                    }
                    for(int i=0; i<5; i++)
                    {
                        left=coJ1[i][0];
                        top=coJ1[i][1];
                        direction=coJ1[i][2];
                        placer(plateauBateauJ1,navires,longueur,bateauplace);
//                        printf("Bateau placé en %d,%d et direction=%d\n",left,top,direction);
                    }
                }
                joueur=1;
                phaseDeJeu=3;
                Jouer();
            }

        }
    }
}
